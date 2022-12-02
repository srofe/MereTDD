#include "../Test.h"
#include <iostream>

TEST("Test can be created") {
}

// This test should fail because it throws an unexpected exception.
TEST("Test that throws unexpectedly can be created") {
    setExpectedFailureReason("Unexpected exception thrown.");
    throw "Unexpected";
}

TEST_EX("Test with throw can be created", int) {
    throw 1;
}

// This test should fail because it does not throw an exception that it is
// expecting to be thrown.
TEST_EX("Test that never thows can be created", int) {
    setExpectedFailureReason("Expected exception type int was not thrown.");
}

// This test should fail because it throws an exception that does not match the
// expected type.
TEST_EX("Test that never throws wrong type can be created", int) {
    setExpectedFailureReason("Unexpected exception thrown.");
    throw "Wrong type";
}
