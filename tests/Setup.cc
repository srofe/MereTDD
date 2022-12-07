#include "../Test.h"
#include <string_view>

int createTestEntry() {
    // If this was real code, it might open a connection to a database, insert
    // a row of data, and return the row identifier.
    return 100;
}

void updateTestEntry(int /* id */, std::string_view name) {
    if (name.empty()) {
        throw 1;
    }
    // Real code would proceed to update the data with a new name.
}

void deleteTestEntry(int /* id */) {
    // Real code would use the id to delete the temporary row of data.
}

TEST_EX("Test will run setup and teardown code", int) {
    int id = createTestEntry();
    updateTestEntry(id, "");
    deleteTestEntry(id);
}
