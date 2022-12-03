#include "../Test.h"

bool isNegative(int value) {
    return value < 0;
}

int multiplyBy2(int value) {
    return value * 2;
}

TEST("Test will pass without any confirms") {
}

TEST("Test bool confirms") {
    bool result = isNegative(0);
    CONFIRM_FALSE(result);

    result = isNegative(-1);
    CONFIRM_TRUE(result);
}

TEST("Test int confirms") {
    int result = multiplyBy2(0);
    CONFIRM(0, result);
    result = multiplyBy2(1);
    CONFIRM(2, result);
    result = multiplyBy2(-1);
    CONFIRM(-2, result);
}

TEST("Test bool confirm failure") {
    bool result = isNegative(0);
    CONFIRM_TRUE(result);
}

TEST("Test int confirm failure") {
    int result = multiplyBy2(1);
    CONFIRM(0, result);
}
