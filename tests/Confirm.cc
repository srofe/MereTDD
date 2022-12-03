#include "../Test.h"

bool isPassingGrade(int value) {
    return true;
}

TEST("Test will pass without any confirms") {
}

TEST("Testing passing grades") {
    bool result = isPassingGrade(0);
    if (result) {
        throw MereTDD::BoolConfirmException(false, 13);
    }

    result = isPassingGrade(100);
    if (not result) {
        throw MereTDD::BoolConfirmException(true, 18);
    }
}
