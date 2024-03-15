/**
 * In C++17 and later, we can use `constexpr` in member functions to allow them to be evaluated at compile time under certain conditions.
 * This can result in performance improvements as computations are done at compile time rather than runtime.
 * Here's an example of a simple `Point` class with `constexpr`:
 */

class Point {
    int x;
    int y;

public:
    constexpr Point(int x, int y) : x(x), y(y) {}

    constexpr int getX() const { return x; }
    constexpr int getY() const { return y; }

    /** 
     * Computes the squared distance between this point and another point.
     * Since the computation is simple and can be done at compile time, we mark it as `constexpr`.
     */
    constexpr int distanceSquared(const Point& other) const {
        int dx = x - other.x;
        int dy = y - other.y;
        return dx * dx + dy * dy;
    }
};

/**
 * Here's how we can use this class and benefit from computations being done at compile time:
 */

constexpr Point p1(3, 4);
constexpr Point p2(6, 8);

// This computation is done at compile time.
constexpr int distSquared = p1.distanceSquared(p2);

/**
 * `consteval` is a keyword introduced in C++20 and it ensures that a function is always evaluated at compile time.
 * Here's an example of how we can use it with the `Point` class:
 */

class Point2 {
    int x;
    int y;

public:
    consteval Point2(int x, int y) : x(x), y(y) {}

    consteval int getX() const { return x; }
    consteval int getY() const { return y; }

    /** 
     * Computes the squared distance between this point and another point.
     * Since the computation is simple and can be done at compile time, we mark it as `consteval`.
     */
    consteval int distanceSquared(const Point2& other) const {
        int dx = x - other.x;
        int dy = y - other.y;
        return dx * dx + dy * dy;
    }
};

/**
 * The usage of `Point2` is similar to `Point`, but all computations are guaranteed to be done at compile time.
 * This can potentially improve runtime performance, but it also means that all values need to be known at compile time.
 */

consteval Point2 p3(3, 4);
consteval Point2 p4(6, 8);

// This computation is done at compile time.
consteval int distSquared2 = p3.distanceSquared(p4);

int main() {
    constexpr Point p1(3, 4);
    constexpr Point p2(6, 8);
    constexpr int distSquared = p1.distanceSquared(p2);

    std::cout << "Squared distance between p1 and p2: " << distSquared << std::endl;

    consteval Point2 p3(3, 4);
    consteval Point2 p4(6, 8);
    consteval int distSquared2 = p3.distanceSquared(p4);

    std::cout << "Squared distance between p3 and p4: " << distSquared2 << std::endl;

    return 0;
}