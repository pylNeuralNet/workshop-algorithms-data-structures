/**
 * function inlining,
 * inlining barrier,
 * code bloat, hidden dependencies
 *
 * In C++, 'inline' is a keyword that is used as a request to the compiler to replace a function call with the body of the function.
 * This can potentially improve execution speed by saving the overhead of a function call. However, it can also increase binary size.
 * The decision to inline a function is ultimately up to the compiler.
 *
 * In modern C++, the trend is towards more use of constexpr and consteval functions, which are evaluated at compile time.
 * This can achieve similar benefits to inlining but with more guaranteed results.
 *
 * Here is an example of using inline, constexpr, and consteval:
 */

inline int inlineFunc(int x, int y) { return x + y; }

constexpr int constexprFunc(int x, int y) { return x * y; }

consteval int constevalFunc(int x, int y) { return x - y; }

#include <iostream>
#include <chrono>

/** 
 * We will create a simple function that adds two integers together.
 * It's a simple operation that is representative of a function small enough to be a good candidate for inlining.
 */
int add(int x, int y) {
    return x + y;
}

/**
 * Now, let's create an inline version of the same function.
 */
inline int add_inline(int x, int y) {
    return x + y;
}

int main() {
    /**
     * We will perform a large number of additions using the non-inline function and measure the time it takes.
     */
    auto start = std::chrono::high_resolution_clock::now();

    volatile int result;  // volatile to prevent compiler optimizations
    for (int i = 0; i < 10000000; ++i) {
        result = add(i, i);
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Time taken by non-inline function: " << duration.count() << " microseconds" << std::endl;

    /**
     * Now, let's do the same with the inline function and compare the times.
     */
    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 10000000; ++i) {
        result = add_inline(i, i);
    }

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Time taken by inline function: " << duration.count() << " microseconds" << std::endl;

    return 0;
}

/**
 * When you run this code, you may or may not see a significant difference in execution time.
 * This is because modern compilers are very sophisticated and will often inline functions automatically if it determines that there is a benefit.
 * Compilers generally do a better job at determining when a function should be inlined than a human developer.
 * Therefore, the 'inline' keyword is more of a hint or suggestion to the compiler, rather than a command.
 * In many scenarios, the compiler will ignore the 'inline' keyword, if it determines that inlining the function does not provide any benefits.
 */