#ifndef MERETDD_TESTSUITE_H
#define MERETDD_TESTSUITE_H

namespace MereTDD {
    class TestSuite;

    inline std::map<std::string, std::vector<TestSuite *>>& getTestSuites() {
        static std::map<std::string, std::vector<TestSuite *>> suites;
        return suites;
    }

    inline void addTestSuite(std::string_view suiteName, TestSuite* suite) {
        std::string name(suiteName);
        if (not getTestSuites().contains(name)) {
            getTestSuites().try_emplace(name, std::vector<TestSuite*>());
        }
        getTestSuites()[name].push_back(suite);
    }

    class TestSuite : public TestBase {
    public:
        TestSuite(std::string_view name, std::string_view suiteName) : TestBase(name, suiteName) {
            addTestSuite(suiteName, this);
        }

        virtual void suiteSetup() = 0;
        virtual void suiteTeardown() = 0;
    };
}

#endif //MERETDD_TESTSUITE_H
