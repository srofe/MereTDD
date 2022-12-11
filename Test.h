#ifndef MERETDD_TEST_H
#define MERETDD_TEST_H

#include "TestBase.h"

namespace MereTDD {
    class Test;

    inline std::map<std::string, std::vector<Test *>>& getTests() {
        static std::map<std::string, std::vector<Test *>> tests;
        return tests;
    }

    inline void addTest(std::string_view suiteName, Test* test) {
        std::string name(suiteName);
        if (not getTests().contains(name)) {
            getTests().try_emplace(name, std::vector<Test *>());
        }
        getTests()[name].push_back(test);
    }

    class Test : public TestBase {
    public:
        Test(std::string_view name, std::string_view suiteName) : TestBase(name, suiteName) {
            addTest(suiteName, this);
        }

        virtual void runEx() {
            run();
        }

        virtual void run() = 0;

        std::string_view expectedReason() const { return mExpectedReason; }

        void setExpectedFailureReason(std::string_view reason) {
            mExpectedReason = reason;
        }

    private:
        std::string mExpectedReason;
    };
}

#endif //MERETDD_TEST_H
