#ifndef MERETDD_TESTEX_H
#define MERETDD_TESTEX_H

namespace MereTDD {
    template <typename ExceptionT>
    class TestEx : public Test {
    public:
        TestEx(std::string_view name, std::string_view suiteName, std::string_view exceptionName) : Test(name, suiteName), mExceptionName(exceptionName) {}

        void runEx() override {
            try {
                run();
            } catch (ExceptionT const &) {
                return;
            }
            throw MissingException(mExceptionName);
        }

    private:
        std::string mExceptionName;
    };
}

#endif //MERETDD_TESTEX_H
