#ifndef MERETDD_SETUPANDTEARDOWN_H
#define MERETDD_SETUPANDTEARDOWN_H

namespace MereTDD {
    template <typename T>
    class SetupAndTeardown : public T {
    public:
        SetupAndTeardown() {
            T::setup();
        }
        ~SetupAndTeardown() {
            T::teardown();
        }
    };
}

#endif //MERETDD_SETUPANDTEARDOWN_H
