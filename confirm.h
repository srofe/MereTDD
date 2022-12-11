#ifndef MERETDD_CONFIRM_H
#define MERETDD_CONFIRM_H

namespace MereTDD {
    inline void confirm(bool expected, bool actual, int line) {
        if (actual != expected) {
            throw BoolConfirmException(expected, line);
        }
    }

    inline void confirm(std::string_view expected, std::string_view actual, int line) {
        if (actual != expected) {
            throw ActualConfirmException(expected, actual, line);
        }
    }

    inline void confirm(std::string const & expected, std::string const & actual, int line) {
        confirm(std::string_view(expected), std::string_view(actual), line);
    }

    inline void confirm(float expected, float actual, int line) {
        if (actual < (expected - 0.0001f) || actual > (expected + 0.0001f)) {
            throw ActualConfirmException(std::to_string(expected), std::to_string(actual), line);
        }
    }

    inline void confirm(double expected, double actual, int line) {
        if (actual < (expected - 0.000001) || actual > (expected + 0.000001)) {
            throw ActualConfirmException(std::to_string(expected), std::to_string(actual), line);
        }
    }

    inline void confirm(long double expected, long double actual, int line) {
        if (actual < (expected - 0.000001) || actual > (expected + 0.000001)) {
            throw ActualConfirmException(std::to_string(expected), std::to_string(actual), line);
        }
    }

    template <typename T>
    void confirm(T const & expected, T const & actual, int line) {
        if (actual != expected) {
            throw ActualConfirmException(std::to_string(expected), std::to_string(actual), line);
        }
    }
}

#endif //MERETDD_CONFIRM_H
