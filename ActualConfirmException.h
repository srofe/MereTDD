#ifndef MERETDD_ACTUALCONFIRMEXCEPTION_H
#define MERETDD_ACTUALCONFIRMEXCEPTION_H

#include "ConfirmException.h"

namespace MereTDD {
    class ActualConfirmException : public ConfirmException {
    public:
        ActualConfirmException(std::string_view expected, std::string_view actual, int line) : ConfirmException(line),
                                                                                               mExpected(expected),
                                                                                               mActual(actual) {
            formatReason();
        }

    private:
        void formatReason() {
            mReason += "    Expected: " + mExpected + "\n";
            mReason += "    Actual  : " + mActual;
        }

        std::string mExpected;
        std::string mActual;
    };
}

#endif //MERETDD_ACTUALCONFIRMEXCEPTION_H
