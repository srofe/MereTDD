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
#include "runtest.h"
#include "runsuite.h"
#include "runtests.h"
#include "confirm.h"

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
