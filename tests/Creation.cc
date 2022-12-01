#include "../Test.h"
#include <iostream>

TEST("Test can be created") {
};

TEST_EX("Test with throw can be created", int) {
    throw 1;
}
