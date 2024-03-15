/**
    In this example, MyClass is the interface that users interact with, and MyClassImpl is the hidden implementation. The implementation details (data members and private methods) are all in MyClassImpl. The public methods of MyClass delegate to methods in MyClassImpl.

    Key benefits of the PImpl idiom:

        - Encapsulation: The implementation details are hidden from users of the class.
        - Reduced compilation dependencies: Changes to the implementation don't require recompiling code that uses the class.
        - Improved compile times: The header file doesn't include the headers for the implementation details.
        - Binary compatibility: Changes to the implementation class do not affect the layout of the interface class, so the binary interface remains stable.
        - Without the PImpl idiom, all the private data members and methods would be part of MyClass, making them visible to users of the class and increasing compilation dependencies. If any of the private implementation details were to change (like adding a new private method or data member), all code that includes the MyClass header would need to be recompiled, even if it only uses the public API.

    The PImpl idiom is not without its drawbacks. It can make the code more complex and harder to follow, and it adds an extra layer of indirection which can impact performance. It also requires dynamic memory allocation, which may be undesirable in some contexts. However, in many cases, the benefits of encapsulation, reduced compilation dependencies, and binary compatibility outweigh these drawbacks.
*/

#include <iostream>
#include <memory>

// Forward declare the implementation class
class MyClassImpl;

class MyClass {
public:
    /** 
     * The constructor creates an instance of the hidden implementation class.
     * This is where the actual data members and private methods would be.
     */
    MyClass();

    /**
     * Destructor needs to be defined where the complete definition of MyClassImpl is known.
     * This is because the automatically generated destructor would be inlined where it's declared.
     * If it's declared in the header file, where MyClassImpl is incomplete type, it would lead to a compiler error.
     * Hence, we need to provide the definition in the .cpp file where MyClassImpl is a complete type.
     */
    ~MyClass();

    /**
     * Public method that delegates to a method in the implementation class.
     * This is how the public API of the class is separated from the implementation details.
     */
    void publicMethod() const;

private:
    /**
     * Pointer to an instance of the implementation class.
     * The implementation class is hidden from users of MyClass, providing a form of encapsulation.
     * This reduces the compilation dependencies, as changes to the implementation don't require recompiling code that uses MyClass.
     */
    std::unique_ptr<MyClassImpl> pimpl;
};

/**
 * The implementation class contains the actual data members and private methods of MyClass.
 * This class is not visible to users of MyClass.
 */
class MyClassImpl {
public:
    void privateMethod() const {
        std::cout << "This is a private method of MyClass\n";
    }
    // Other data members and private methods...
};

// Definitions of MyClass's constructor and destructor
MyClass::MyClass() : pimpl(new MyClassImpl) {}
MyClass::~MyClass() = default;

// Definition of MyClass's public method
void MyClass::publicMethod() const {
    pimpl->privateMethod();
}

// Usage
int main() {
    MyClass obj;
    obj.publicMethod();
    return 0;
}

