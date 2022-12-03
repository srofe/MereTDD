#include "../Test.h"

bool isPassingGrade(int value) {
    return true;
}

TEST("Test will pass without any confirms") {
}

TEST("Testing passing grades") {
    bool result = isPassingGrade(0);
    CONFIRM_FALSE(result);

    result = isPassingGrade(100);
    CONFIRM_TRUE(result);
}
