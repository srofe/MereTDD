#include <iostream>
#include <string_view>

class Test {
public:
    Test(std::string_view name) : mName(name), mResult(true) {}
    void operator() ();

private:
    std::string mName;
    bool mResult;
};

void Test::operator() () {
        std::cout << mName << std::endl;
}

Test test("testCanBeCreated");

int main() {
    test();
    return 0;
}
