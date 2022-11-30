#include "Test.h"
#include <iostream>

TEST {
        std::cout << mName << std::endl;
}

int main() {
    for (auto *test : MereTDD::getTests()) {
        test->run();
    }
    return 0;
}
