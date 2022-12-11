#ifndef MERETDD_RUNTESTS_H
#define MERETDD_RUNTESTS_H

namespace MereTDD {
    inline int runTests(std::ostream &output) {
        output << "Running " << getTests().size() << " tests.\n";
        int numPassed = 0;
        int numMissedFailed = 0;
        int numFailed = 0;

        for (auto const &[key, value]: getTests()) {
            std::string suiteDisplayName = "Suite: ";
            if (key.empty()) {
                suiteDisplayName += "Single Tests";
            } else {
                suiteDisplayName += key;
            }
            output << "--------------- " << suiteDisplayName << std::endl;
            if (not key.empty()) {
                if (not getTestSuites().contains(key)) {
                    output << "Test suite is not found." << " Exiting test application." << std::endl;
                    return ++numFailed;
                }
                if (not runSuite(output, true, key, numPassed, numFailed)) {
                    output << "Test suite setup failed." << " Skipping test in suite." << std::endl;
                    continue;
                }
            }
            for (auto *test: value) {
                runTest(output, test, numPassed, numFailed, numMissedFailed);
            }
            if (not key.empty()) {
                if (not runSuite(output, false, key, numPassed, numFailed)) {
                    output << "Test suite teardown failed." << std::endl;
                }
            }
        }
        output << "----------------------------------- \n";
        output << "Tests passed: " << numPassed << "\nTests failed: " << numFailed;
        if (numMissedFailed != 0) {
            output << "\nTest failures missed: " << numMissedFailed;
        }
        output << std::endl;
        return numFailed;
    }
}

#endif //MERETDD_RUNTESTS_H
