#ifndef MERETDD_TEST_H
#define MERETDD_TEST_H

#include <iostream>
#include <string_view>
#include <vector>

namespace MereTDD {
    class TestBase {
    public:
        TestBase(std::string_view name) : mName(name), mPassed(true) {}
        virtual ~TestBase() = default;
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

        void setFailed(std::string_view reason) {
            mPassed = false;
            mReason = reason;
        }

    private:
        std::string mName;
        bool mPassed;
        std::string mReason;
    };

    inline std::vector<TestBase*>& getTests() {
        static std::vector<TestBase*> tests;

        return tests;
    }

    inline void runTests() {
        for (auto *test: getTests()) {
            try {
                test->run();
            } catch (...) {
                test->setFailed("Unexpected exception thrown.");
            }
        }
    }
} // namespace MereTDD

#define TEST \
class Test : public MereTDD::TestBase { \
public: \
    Test(std::string_view name) : TestBase(name) { \
        MereTDD::getTests().push_back(this); \
    } \
    void run() override; \
}; \
Test test("testCanBeCreated"); \
void Test::run()

#endif // MERETDD_TEST_H
