#include <iostream>
#include <variant>

class Derived1 {
public:
    void specificFunction() const {
        std::cout << "Specific function for Derived1 class\n";
    }
};

class Derived2 {
public:
    void specificFunction() const {
        std::cout << "Specific function for Derived2 class\n";
    }
};

using Base = std::variant<Derived1, Derived2>;

// Visitor class for Base
struct BaseVisitor {
    void operator()(const Derived1& d1) const {
        d1.specificFunction();
    }
    
    void operator()(const Derived2& d2) const {
        d2.specificFunction();
    }
};

int main() {
    Base base = Derived1(); // Now base holds a Derived1 object

    // We can visit the object using std::visit and our visitor
    std::visit(BaseVisitor(), base);

    base = Derived2(); // base now holds a Derived2 object

    // std::visit still works and calls the right function
    std::visit(BaseVisitor(), base);

    return 0;
}

/*
    - Derived1 and Derived2 are unrelated types with a similar interface.
    - Base is defined as a std::variant of Derived1 and Derived2. It can hold either a Derived1 object or a Derived2 object.
    - BaseVisitor is a visitor struct that can be used with std::visit to call member functions of Derived1 or Derived2.
    - In main, we create a Base object, which initially holds a Derived1 object. We use std::visit to call the Derived1's specificFunction.
    - We then assign a Derived2 object to base and use std::visit again to call the Derived2's specificFunction.
*/