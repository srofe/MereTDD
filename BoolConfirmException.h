#ifndef MERETDD_BOOLCONFIRMEXCEPTION_H
#define MERETDD_BOOLCONFIRMEXCEPTION_H

#include "ConfirmException.h"

namespace MereTDD {
    class BoolConfirmException : public ConfirmException {
    public:
        BoolConfirmException(bool expected, int line) : ConfirmException(line) {
            mReason += "    Expected: ";
            mReason += expected ? "true" : "false";
        }
    };
}

#endif //MERETDD_BOOLCONFIRMEXCEPTION_H
