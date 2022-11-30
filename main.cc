#include <iostream>
#include <string_view>

class Test {
public:
    Test(std::string_view name) : mName(name), mResult(true) {}
    void operator() () {
        std::cout << mName << std::endl;
    }

private:
    std::string mName;
    bool mResult;
};

Test test("testCanBeCreated");

int main() {
    test();
    return 0;
}
