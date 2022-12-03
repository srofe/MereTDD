#include "../Test.h"

bool isNegative(int value) {
    return value < 0;
}

TEST("Test will pass without any confirms") {
}

TEST("Testing passing grades") {
    bool result = isNegative(0);
    CONFIRM_FALSE(result);

    result = isNegative(-1);
    CONFIRM_TRUE(result);
}
