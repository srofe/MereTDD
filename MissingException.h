#ifndef MERETDD_MISSINGEXCEPTION_H
#define MERETDD_MISSINGEXCEPTION_H

namespace MereTDD {
    class MissingException {
    public:
        MissingException(std::string_view exType) : mExType(exType) {}

        std::string_view exType() const { return mExType; }

    private:
        std::string mExType;
    };
}

#endif //MERETDD_MISSINGEXCEPTION_H
