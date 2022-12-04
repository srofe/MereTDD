#include "../Test.h"

bool isNegative(int value) {
    return value < 0;
}

int multiplyBy2(int value) {
    return value * 2;
}

long multiplyBy2(long value) {
    return value * 2L;
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

TEST("Test long confirms") {
    long result = multiplyBy2(0L);
    CONFIRM(0L, result);
    result = multiplyBy2(1L);
    CONFIRM(2L, result);
    result = multiplyBy2(-1);
    CONFIRM(-2L, result);
}

TEST("Test bool confirm failure") {
    std::string reason = "    Expected: true";
    setExpectedFailureReason(reason);
    bool result = isNegative(0);
    CONFIRM_TRUE(result);
}

TEST("Test int confirm failure") {
    std::string reason = "    Expected: 0\n";
    reason += "    Actual  : 2";
    setExpectedFailureReason(reason);
    int result = multiplyBy2(1);
    CONFIRM(0, result);
}

TEST("Test long confirm failure") {
    std::string reason = "    Expected: 0\n";
    reason += "    Actual  : 2";
    setExpectedFailureReason(reason);
    long result = multiplyBy2(1L);
    CONFIRM(0L, result);
}
