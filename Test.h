#ifndef MERETDD_TEST_H
#define MERETDD_TEST_H

#include <ostream>
#include <string_view>
#include <vector>

namespace MereTDD {
    class MissingException {
    public:
        MissingException(std::string_view exType) : mExType(exType) {}
        std::string_view exType() const {
            return mExType;
        }

    private:
        std::string_view mExType;
    };

    class ConfirmException {
    public:
        ConfirmException() = default;
        virtual ~ConfirmException() = default;
        std::string_view reason() const {
            return mReason;
        }

    protected:
        std::string mReason;
    };

    class BoolConfirmException : public ConfirmException {
    public:
        BoolConfirmException(bool expected, int line) {
            mReason = "Confirm failed on line ";
            mReason += std::to_string(line) + "\n";
            mReason += "    Expected: ";
            mReason += expected ? "true" : "false";
        }
    };

    class  ActualConfirmException : public ConfirmException {
    public:
        ActualConfirmException(int expected, int actual, int line) : mExpected(std::to_string(expected)), mActual(std::to_string(actual)), mLine(line) {
            formatReason();
        }
        private:
            void formatReason() {
                mReason = "Confirm failed on line ";
                mReason += std::to_string(mLine) + "\n";
                mReason += "    Expected: " + mExpected + "\n";
                mReason += "    Actual  : " + mActual;
            }
            std::string mExpected;
            std::string mActual;
            int mLine;
    };

    inline void confirm(bool expected, bool actual, int line) {
        if (actual != expected) {
            throw BoolConfirmException(expected, line);
        }
    }

    inline void confirm(int expected, int actual, int line) {
        if (actual != expected) {
            throw ActualConfirmException(expected, actual, line);
        }
    }

    class TestBase {
    public:
        TestBase(std::string_view name) : mName(name), mPassed(true) {}
        virtual ~TestBase() = default;
        virtual void runEx() {
            run();
        }
        virtual void run() = 0;

        std::string_view name() const {
            return mName;
        }

        bool passed() const {
            return mPassed;
        }

        std::string_view reason() const {
            return mReason;
        }

        std::string_view expectedReason() const {
            return mExpectedReason;
        }

        void setFailed(std::string_view reason) {
            mPassed = false;
            mReason = reason;
        }

        void setExpectedFailureReason(std::string_view reason) {
            mExpectedReason = reason;
        }

    private:
        std::string mName;
        bool mPassed;
        std::string mReason;
        std::string_view mExpectedReason;
    };

    inline std::vector<TestBase*>& getTests() {
        static std::vector<TestBase*> tests;

        return tests;
    }

    inline int runTests(std::ostream& output) {
        output << "Running " << getTests().size() << " tests.\n";
        int numPassed = 0;
        int numMissedFailed = 0;
        int numFailed = 0;

        for (auto *test: getTests()) {
            output << "---------------\n" << test->name() << std::endl;
            try {
                test->runEx();
            } catch (ConfirmException const& ex) {
                test->setFailed(ex.reason());
            } catch (MissingException const& ex) {
                std::string message = "Expected exception type ";
                message += ex.exType();
                message += " was not thrown.";
                test->setFailed(message);
            } catch (...) {
                test->setFailed("Unexpected exception thrown.");
            }
            if (test->passed()) {
                if (not test->expectedReason().empty()) {
                    ++numMissedFailed;
                    output << "Missed expected failure\n"
                        << "Test passed but was expected to fail"
                        << std::endl;
                } else {
                    ++numPassed;
                    output << "Passed" << std::endl;
                }
            } else if (not test->expectedReason().empty() && test->expectedReason() == test->reason()) {
                ++numPassed;
                output << "Expected failure\n" << test->reason() << std::endl;
            } else {
                ++numFailed;
                output << "Failed\n" << test->reason() << std::endl;
            }
        }
        output << "---------------\n";
        output << "Tests passed: " << numPassed << std::endl;
        output << "Tests failed: " << numFailed;
        if (numMissedFailed != 0) {
            output << std::endl;
            output << "Test failures missed: " << numMissedFailed;
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

#define TEST(testName) \
namespace { \
class MERETDD_CLASS : public MereTDD::TestBase { \
public: \
    MERETDD_CLASS(std::string_view name) : TestBase(name) { \
        MereTDD::getTests().push_back(this); \
    } \
    void run() override; \
}; \
} /* end of namespace */ \
MERETDD_CLASS MERETDD_INSTANCE(testName); \
void MERETDD_CLASS::run()

#define TEST_EX(testName, exceptionType) \
namespace { \
class MERETDD_CLASS : public MereTDD::TestBase { \
public: \
    MERETDD_CLASS(std::string_view name) : TestBase(name) { \
        MereTDD::getTests().push_back(this);     \
    } \
    void runEx() override { \
        try { \
            run(); \
        } catch (exceptionType const &) {\
            return; \
        } \
        throw MereTDD::MissingException(#exceptionType); \
    } \
    void run() override; \
}; \
} /* end of namespace */ \
MERETDD_CLASS MERETDD_INSTANCE(testName); \
void MERETDD_CLASS::run()

#define CONFIRM_FALSE(actual) MereTDD::confirm(false, actual, __LINE__)

#define CONFIRM_TRUE(actual) MereTDD::confirm(true, actual, __LINE__)

#define CONFIRM(expected, actual) MereTDD::confirm(expected, actual, __LINE__)

#endif // MERETDD_TEST_H
