#ifndef MERETDD_MERETDD_H
#define MERETDD_MERETDD_H

#include <map>
#include <ostream>
#include <string_view>
#include <vector>
#include "ConfirmException.h"
#include "BoolConfirmException.h"
#include "ActualConfirmException.h"
#include "MissingException.h"
#include "TestBase.h"
#include "Test.h"
#include "TestEx.h"
#include "TestSuite.h"
#include "SetupAndTeardown.h"
#include "TestSuiteSetupAndTeardown.h"
#include "confirm.h"

namespace MereTDD {
    inline void runTest(std::ostream& output, Test* test, int& numPassed, int& numFailed, int& numMissedFailed) {
        output << "------- Test: " << test->name() << std::endl;
        try {
            test->runEx();
        } catch (ConfirmException const& exception) {
            test->setFailed(exception.reason(), exception.line());
        } catch (MissingException const& exception) {
            std::string message = "Expected exception type ";
            message += exception.exType();
            message += " was not thrown.";
            test->setFailed(message);
        } catch (...) {
            test->setFailed("Unexpected exception thrown.");
        }

        if (test->passed()) {
            if (not test->expectedReason().empty()) {
                // This test passed, but it was supposed to have failed.
                ++numMissedFailed;
                output << "Missed expected failure\n" << "Test passed, but was expected to fail." << std::endl;
            } else {
                ++numPassed;
                output << "Passed" << std::endl;
            }
        } else if (not test->expectedReason().empty() && test->expectedReason() == test->reason()) {
            ++numPassed;
            output << "Expected failure\n" << test->reason() << std::endl;
        } else {
            ++numFailed;
            if (test->confirmLocation() != -1) {
                output << "Failed confirm on line " << test->confirmLocation() << std::endl;
            } else {
                output << "Failed\n";
            }
            output << test->reason() << std::endl;
        }
    }

    inline bool runSuite(std::ostream& output, bool setup, std::string const& name, int& numPassed, int& numFailed) {
        for (auto &suite: getTestSuites()[name]) {
            if (setup) {
                output << "------- Setup:";
            } else {
                output << "------- Teardown:";
            }
            output << suite->name() << std::endl;

            try {
                if (setup) {
                    suite->suiteSetup();
                } else {
                    suite->suiteTeardown();
                }
            } catch (ConfirmException const &exception) {
                suite->setFailed(exception.reason(), exception.line());
            } catch (...) {
                suite->setFailed("Unexpected exception thrown.");
            }

            if (suite->passed()) {
                ++numPassed;
                output << "Passed" << std::endl;
            } else {
                ++numFailed;
                if (suite->confirmLocation() != -1) {
                    output << "Failed confirm on line " << suite->confirmLocation() << std::endl;
                } else {
                    output << "Failed\n";
                }
                output << suite->reason() << std::endl;
                return false;
            }
        }
        return true;
    }

    inline int runTests(std::ostream &output) {
        output << "Running " << getTests().size() << " tests.\n";
        int numPassed = 0;
        int numMissedFailed = 0;
        int numFailed = 0;

        for (auto const &[key, value]: getTests()) {
            std::string suiteDisplayName = "Suite: ";
            if (key.empty()) {
                suiteDisplayName += "Single Tests";
            } else {
                suiteDisplayName += key;
            }
            output << "--------------- " << suiteDisplayName << std::endl;
            if (not key.empty()) {
                if (not getTestSuites().contains(key)) {
                    output << "Test suite is not found." << " Exiting test application." << std::endl;
                    return ++numFailed;
                }
                if (not runSuite(output, true, key, numPassed, numFailed)) {
                    output << "Test suite setup failed." << " Skipping test in suite." << std::endl;
                    continue;
                }
            }
            for (auto *test: value) {
                runTest(output, test, numPassed, numFailed, numMissedFailed);
            }
            if (not key.empty()) {
                if (not runSuite(output, false, key, numPassed, numFailed)) {
                    output << "Test suite teardown failed." << std::endl;
                }
            }
        }
        output << "----------------------------------- \n";
        output << "Tests passed: " << numPassed << "\nTests failed: " << numFailed;
        if (numMissedFailed != 0) {
            output << "\nTest failures missed: " << numMissedFailed;
        }
        output << std::endl;
        return numFailed;
    }
} // namespace MereTDD

#define MERETDD_CLASS_FINAL(line) Test ## line
#define MERETDD_CLASS_RELAY(line) MERETDD_CLASS_FINAL(line)
#define MERETDD_CLASS MERETDD_CLASS_RELAY(__LINE__)

#define MERETDD_INSTANCE_FINAL(line) test ## line
#define MERETDD_INSTANCE_RELAY(line) MERETDD_INSTANCE_FINAL(line)
#define MERETDD_INSTANCE MERETDD_INSTANCE_RELAY(__LINE__)

#define TEST_SUITE(testName, suiteName) \
namespace { \
class MERETDD_CLASS : public MereTDD::Test { \
public: \
    MERETDD_CLASS(std::string_view name, std::string_view suite) : Test(name, suite) {} \
    void run() override; \
}; \
} /* end of namespace */ \
MERETDD_CLASS MERETDD_INSTANCE(testName, suiteName); \
void MERETDD_CLASS::run()

#define TEST_SUITE_EX(testName, suiteName, exceptionType) \
namespace { \
class MERETDD_CLASS : public MereTDD::TestEx<exceptionType> { \
public: \
    MERETDD_CLASS(std::string_view name, std::string_view suite, std::string_view exceptionName) : TestEx(name, suite, exceptionName) {} \
    void run() override; \
}; \
} /* end of namespace */ \
MERETDD_CLASS MERETDD_INSTANCE(testName, suiteName, #exceptionType); \
void MERETDD_CLASS::run()

#define TEST(testName) \
namespace { \
class MERETDD_CLASS : public MereTDD::Test { \
public: \
    MERETDD_CLASS(std::string_view name) : Test(name, "") {} \
    void run() override; \
}; \
} /* end of namespace */ \
MERETDD_CLASS MERETDD_INSTANCE(testName); \
void MERETDD_CLASS::run()

#define TEST_EX(testName, exceptionType) \
namespace { \
class MERETDD_CLASS : public MereTDD::TestEx<exceptionType> { \
public: \
MERETDD_CLASS(std::string_view name, std::string_view exceptionName) : TestEx(name, "", exceptionName) {} \
    void run() override; \
}; \
} /* end of namespace */ \
MERETDD_CLASS MERETDD_INSTANCE(testName, #exceptionType); \
void MERETDD_CLASS::run()

#define CONFIRM_FALSE(actual) MereTDD::confirm(false, actual, __LINE__)

#define CONFIRM_TRUE(actual) MereTDD::confirm(true, actual, __LINE__)

#define CONFIRM(expected, actual) MereTDD::confirm(expected, actual, __LINE__)

#endif // MERETDD_MERETDD_H
