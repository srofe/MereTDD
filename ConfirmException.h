#ifndef MERETDD_CONFIRMEXCEPTION_H
#define MERETDD_CONFIRMEXCEPTION_H

#include <string>

namespace MereTDD {
    class ConfirmException {
    public:
        ConfirmException(int line) : mLine(line) {}
        virtual ~ConfirmException() = default;
        std::string_view reason() const {
            return mReason;
        }
        int line() const { return mLine; }

    protected:
        std::string mReason;
        int mLine;
    };
}

#endif //MERETDD_CONFIRMEXCEPTION_H
