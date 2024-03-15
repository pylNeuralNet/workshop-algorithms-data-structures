/*
    https://learn.microsoft.com/en-us/cpp/cpp/exceptions-and-stack-unwinding-in-cpp?view=msvc-170

    - Destructors and Stack Unwinding: During stack unwinding, destructors for local objects are called in reverse order of their construction. This is crucial for releasing resources such as memory and file handles.
    - Noexcept Guarantees: Functions can be marked with noexcept to indicate that they do not throw exceptions. This helps in optimizing code, as the compiler can make certain assumptions about the behavior of these functions during stack unwinding.
    - Exception Propagation: When an exception is thrown, it propagates up the call stack until it is caught by a matching catch block. If no catch block is found, std::terminate is called, which usually results in program termination1.
    - Uncaught Exceptions: The function std::uncaught_exceptions can be used to detect if exceptions are currently being processed, which can be useful in destructor logic to avoid throwing exceptions during stack unwinding.
    - Nested Exceptions: C++ allows exceptions to be nested, meaning that during the handling of one exception, another exception can be thrown. This can complicate stack unwinding and requires careful management to avoid calls to std::terminate.
    - Copy Elision and Exceptions: Modern C++ standards have improved copy elision, which can reduce the chances of exceptions during object construction and assignment, thus affecting the behavior during stack unwinding.
    - Transaction-based Exception Handling: Some designs use a transaction-based model, where operations are performed in a way that can be rolled back if an exception occurs, ensuring a consistent state.
*/