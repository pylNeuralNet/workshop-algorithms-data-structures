#include <iostream>
#include <array>
#include <utility> // for std::pair

// A simple compile-time function to map error codes to error messages
consteval const char* getErrorMessage(int code) {
    switch (code) {
        case 404: return "Not Found";
        case 500: return "Internal Server Error";
        case 503: return "Service Unavailable";
        default: return "Unknown Error";
    }
}

// A class that represents a compile-time error code lookup table
class ErrorCodeLookup {
private:
    // Using std::array to store error code and message pairs
    std::array<std::pair<int, const char*>, 3> errorTable;

public:
    // A constexpr constructor to initialize the lookup table
    constexpr ErrorCodeLookup() : errorTable{{
        {404, getErrorMessage(404)},
        {500, getErrorMessage(500)},
        {503, getErrorMessage(503)},
    }} {}

    // A constexpr function to get the error message for a given code
    constexpr const char* operator[](int code) const {
        for (const auto& [errCode, errMsg] : errorTable) {
            if (errCode == code) return errMsg;
        }
        return getErrorMessage(-1); // Default case for unknown errors
    }
};

int main() {
    constexpr ErrorCodeLookup lookupTable;

    // Using decltype to deduce the type returned by the [] operator
    decltype(lookupTable[404]) message = lookupTable[404];

    // Verify at compile time that the message is correctly retrieved
    static_assert(lookupTable[404] == getErrorMessage(404));

    std::cout << "Error 404: " << message << std::endl;

    return 0;
}