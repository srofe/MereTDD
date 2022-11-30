#include <iostream>
#include <string_view>

#define TEST class Test { \
public: \
    Test(std::string_view name) : mName(name), mResult(true) {} \
    void operator() (); \
private: \
    std::string mName; \
    bool mResult; \
}; \
Test test("testCanBeCreated"); \
void Test::operator() ()
TEST {
        std::cout << mName << std::endl;
}


int main() {
    test();
    return 0;
}
