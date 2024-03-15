/*
    Templates and virtual functions serve different roles in C++. A template function is a compile-time construct that generates a set of functions or classes based on types given to it. A virtual function, on the other hand, is a run-time construct that allows you to achieve polymorphism.

    In C++, a template function cannot be virtual because the compiler needs to know the exact implementation of a virtual function at compile time to construct the vtable. However, a class template can contain virtual functions, and these functions can be overridden in classes that specialize the template.
*/

#include <iostream>

/** A class template with a virtual function. */
template <typename T>
class Animal {
public:
    /** A virtual function. */
    virtual void makeNoise() {
        std::cout << "Generic animal noise\n";
    }
};

/** A class that specializes the Animal template for int. */
template <>
class Animal<int> {
public:
    /** We can override the virtual function in the base class. */
    void makeNoise() {
        std::cout << "Animal<int> noise\n";
    }
};

/** A class that specializes the Animal template for double. */
template <>
class Animal<double> {
public:
    /** We can override the virtual function in the base class. */
    void makeNoise() {
        std::cout << "Animal<double> noise\n";
    }
};

int main() {
    /** Create instances of our classes. */
    Animal<int> animalInt;
    Animal<double> animalDouble;

    animalInt.makeNoise();     // Outputs: "Animal<int> noise"
    animalDouble.makeNoise();  // Outputs: "Animal<double> noise"

    return 0;
}