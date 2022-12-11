#ifndef MERETDD_TESTSUITESETUPANDTEARDOWN_H
#define MERETDD_TESTSUITESETUPANDTEARDOWN_H

namespace MereTDD {
    template <typename T>
    class TestSuiteSetupAndTeardown : public T, public TestSuite {
    public:
        TestSuiteSetupAndTeardown(std::string_view name, std::string_view suite) : TestSuite(name, suite) {}

        void suiteSetup() override {
            T::setup();
        }

        void suiteTeardown() override {
            T::teardown();
        }
    };
}

#endif //MERETDD_TESTSUITESETUPANDTEARDOWN_H
