#ifndef MERETDD_RUNSUITE_H
#define MERETDD_RUNSUITE_H

namespace MereTDD {
    inline bool runSuite(std::ostream& output, bool setup, std::string const& name, int& numPassed, int& numFailed) {
        for (auto &suite: getTestSuites()[name]) {
            if (setup) {
                output << "------- Setup:";
            } else {
                output << "------- Teardown:";
            }
            output << suite->name() << std::endl;

            try {
                if (setup) {
                    suite->suiteSetup();
                } else {
                    suite->suiteTeardown();
                }
            } catch (ConfirmException const &exception) {
                suite->setFailed(exception.reason(), exception.line());
            } catch (...) {
                suite->setFailed("Unexpected exception thrown.");
            }

            if (suite->passed()) {
                ++numPassed;
                output << "Passed" << std::endl;
            } else {
                ++numFailed;
                if (suite->confirmLocation() != -1) {
                    output << "Failed confirm on line " << suite->confirmLocation() << std::endl;
                } else {
                    output << "Failed\n";
                }
                output << suite->reason() << std::endl;
                return false;
            }
        }
        return true;
    }
}

#endif //MERETDD_RUNSUITE_H
