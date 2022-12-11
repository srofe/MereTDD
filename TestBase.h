#ifndef MERETDD_TESTBASE_H
#define MERETDD_TESTBASE_H

#include <string_view>

namespace MereTDD {
    class TestBase {
    public:
        TestBase(std::string_view name, std::string_view suiteName) :
                mName(name),
                mSuiteName(suiteName),
                mPassed(true),
                mConfirmLocation(-1) {}
        virtual ~TestBase() = default;

        std::string_view name() const { return mName; }
        std::string_view suiteName() const { return mSuiteName; }
        bool passed() const { return mPassed; }
        std::string_view reason() const { return mReason; }
        int confirmLocation() const { return mConfirmLocation; }

        void setFailed(std::string_view reason, int confirmLocation = -1) {
            mPassed = false;
            mReason = reason;
            mConfirmLocation = confirmLocation;
        }

    private:
        std::string mName;
        std::string mSuiteName;
        bool mPassed;
        std::string mReason;
        int mConfirmLocation;
    };
}

#endif //MERETDD_TESTBASE_H
