/*
    RTTI stands for Run-Time Type Information. It's a feature of the C++ language that provides a way to identify an object's type during program execution. RTTI is useful when you need to determine the type of an object at runtime or when you need to use dynamic casting.

    In modern C++, RTTI is often used in conjunction with dynamic_cast and typeid operators.

        - dynamic_cast is used for downcasting, which means converting a pointer or reference from a base type to a derived type. It checks if the object of base type is an instance of the derived type.

        - typeid returns a type_info object representing the type of the object. This can be used to compare if two objects are of the same type or to get the name of the object's type.

    However, RTTI can cause performance overhead and code size increase, so it is sometimes avoided in performance-critical or memory-constrained systems. In such cases, alternatives such as virtual functions or variant types might be used.

    It's worth noting that not all contemporary C++ codebases use RTTI. Some projects disable it for the reasons mentioned above.
*/

#include <iostream>
#include <typeinfo> // for typeid() and std::bad_cast

class Base {
public:
    virtual ~Base() {} // Important to have a virtual destructor in polymorphic base class
};

class Derived : public Base {
public:
    void specificFunction() {
        std::cout << "Specific function for Derived class\n";
    }
};

int main() {
    Base* basePtr = new Derived(); // base class pointer pointing to derived class object

    /**
     * We want to check if 'basePtr' actually points to a 'Derived' object.
     * For this, we use dynamic_cast to safely attempt the down-cast. If basePtr is
     * pointing to a Derived object, the cast will succeed. Otherwise, it will return nullptr.
     */
    Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);

    if (derivedPtr != nullptr) { // If the dynamic_cast was successful
        derivedPtr->specificFunction(); // We can safely call Derived's specific functions
    } else {
        std::cout << "Cast failed\n";
    }

    /**
     * The 'typeid' operator can be used to find the type of an object at runtime.
     * Note: It returns the type of the object being pointed to, not the type of the pointer,
     * because Base has a virtual function.
     */
    std::cout << "Type of object pointed by basePtr: " << typeid(*basePtr).name() << '\n';

    delete basePtr; // Clean up
    return 0;
}

/**
    In this example:

        - Base is a polymorphic base class because it has at least one virtual function.
        - Derived is a class derived from Base. It has a method specificFunction that doesn't exist in Base.
        - dynamic_cast is used to safely attempt to down-cast a Base* to Derived*. If the Base* actually points to a Derived object, the cast will succeed and we can safely call Derived-specific functions. Otherwise, dynamic_cast will return nullptr.
        - The typeid operator is used to get the type of the object being pointed to by basePtr. Because Base has a virtual function (making it polymorphic), typeid will give the actual type of the object, not just Base. The name() member function returns a human-readable string representing the type. The exact output is compiler-dependent.
        - The delete statement is used to clean up the dynamically allocated Derived object.
*/