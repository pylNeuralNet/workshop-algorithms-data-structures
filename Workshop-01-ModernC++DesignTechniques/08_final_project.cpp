/**
    Challenge: Compile-Time Error Code Lookup Table

    Create a class ErrorCodeLookup that provides a compile-time lookup table mapping error codes (integer values) to their corresponding error messages (string literals). The class should allow the retrieval of error messages based on error codes at compile time, where possible.

    Requirements:

    Use a constexpr constructor to initialize the lookup table.
    Use a consteval function to guarantee compile-time evaluation for retrieving error messages.
    Use decltype to ensure type consistency in template functions or auto type deduction.
    Implement a static_assert test to verify that the error message retrieval is indeed happening at compile time.
    Here's a simplified implementation of the ErrorCodeLookup class with comments explaining each requirement:
*/

#include <iostream>
#include <array>
#include <utility> // for std::pair
#include <string_view>

// A helper constexpr function to retrieve error messages.
consteval std::string_view getErrorMessage(int code) {
    switch (code) {
        case 404: return "Not Found";
        case 500: return "Internal Server Error";
        case 503: return "Service Unavailable";
        default: return "Unknown Error";
    }
}

// Error code and message pair type for structured bindings
struct ErrorCodeMessage {
    int code;
    std::string_view message;
};

// Class representing a compile-time error code lookup table
class ErrorCodeLookup {
private:
    std::array<ErrorCodeMessage, 3> errorTable;

public:
    // A constexpr constructor to initialize the lookup table
    constexpr ErrorCodeLookup() : errorTable{{
        {404, getErrorMessage(404)},
        {500, getErrorMessage(500)},
        {503, getErrorMessage(503)}
    }} {}

    // Overloaded subscript operator for accessing error messages by code.
    constexpr std::string_view operator[](int code) const {
        for (const auto& [errCode, errMsg] : errorTable) {
            if (errCode == code) return errMsg;
        }
        return getErrorMessage(-1);
    }

    // Function to add a new error message using rvalue references
    void addErrorMessage(int code, std::string_view&& message) {
        // Note that this operation cannot be constexpr because it modifies
        // the state of the object and therefore requires runtime evaluation.
        errorTable.push_back({code, std::move(message)});
    }
};

int main() {
    constexpr ErrorCodeLookup lookupTable; // Initialize at compile time

    // Use decltype to deduce the type returned by the subscript operator
    constexpr decltype(lookupTable[404]) message = lookupTable[404];

    // Compile-time assertion to check that the message is correct
    static_assert(lookupTable[404] == getErrorMessage(404));

    std::cout << "Error 404: " << message << '\n';

    // Structured bindings to access elements of the array
    for (const auto& [code, errMsg] : lookupTable.errorTable) {
        std::cout << "Error " << code << ": " << errMsg << '\n';
    }

    // Note: The addErrorMessage function cannot be used in this example
    // because modification of the errorTable at runtime would make it
    // incompatible with constexpr and consteval requirements.

    return 0;
}