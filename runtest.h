#ifndef MERETDD_RUNTEST_H
#define MERETDD_RUNTEST_H

namespace MereTDD {
    inline void runTest(std::ostream& output, Test* test, int& numPassed, int& numFailed, int& numMissedFailed) {
        output << "------- Test: " << test->name() << std::endl;
        try {
            test->runEx();
        } catch (ConfirmException const& exception) {
            test->setFailed(exception.reason(), exception.line());
        } catch (MissingException const& exception) {
            std::string message = "Expected exception type ";
            message += exception.exType();
            message += " was not thrown.";
            test->setFailed(message);
        } catch (...) {
            test->setFailed("Unexpected exception thrown.");
        }

        if (test->passed()) {
            if (not test->expectedReason().empty()) {
                // This test passed, but it was supposed to have failed.
                ++numMissedFailed;
                output << "Missed expected failure\n" << "Test passed, but was expected to fail." << std::endl;
            } else {
                ++numPassed;
                output << "Passed" << std::endl;
            }
        } else if (not test->expectedReason().empty() && test->expectedReason() == test->reason()) {
            ++numPassed;
            output << "Expected failure\n" << test->reason() << std::endl;
        } else {
            ++numFailed;
            if (test->confirmLocation() != -1) {
                output << "Failed confirm on line " << test->confirmLocation() << std::endl;
            } else {
                output << "Failed\n";
            }
            output << test->reason() << std::endl;
        }
    }
}

#endif //MERETDD_RUNTEST_H
