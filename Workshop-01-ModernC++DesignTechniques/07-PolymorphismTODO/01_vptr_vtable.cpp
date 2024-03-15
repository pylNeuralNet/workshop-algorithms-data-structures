#include <iostream>

/** The base class. */
class Animal {
public:
    /**
    * A virtual function. When we declare a virtual function in the class,
    * the compiler adds a hidden pointer to each object of the class.
    * This is the vptr (virtual pointer). The vptr is set (points to the vtable)
    * when an object is created.
    */
    virtual void makeNoise() {
        std::cout << "Generic animal noise\n";
    }
};

/** A derived class. */
class Dog: public Animal {
public:
    /**
     * We override the virtual function in the base class.
     * When this class is defined, the compiler creates a vtable for the Dog class.
     * The vtable is a table that contains function pointers to the virtual functions
     * implemented by this class. The vptr in each Dog object will point to this vtable.
     */
    void makeNoise() override {
        std::cout << "Woof!\n";
    }
};

/** Another derived class. */
class Cat: public Animal {
public:
    /**
     * We override the virtual function in the base class.
     * When this class is defined, the compiler creates a vtable for the Cat class.
     * The vtable is a table that contains function pointers to the virtual functions
     * implemented by this class. The vptr in each Cat object will point to this vtable.
     */
    void makeNoise() override {
        std::cout << "Meow!\n";
    }
};

int main() {
    /** Create instances of our classes. */
    Dog d; // The Dog constructor is called, and the vptr is set to point to the Dog vtable.
    Cat c; // The Cat constructor is called, and the vptr is set to point to the Cat vtable.

    /**
    * Animal pointer pointing to a Dog object.
    * When we call makeNoise() through animalPtr, the compiler doesn't know which makeNoise() to call at compile time.
    * Instead, it uses the vptr to lookup the vtable for the object (which is the Dog vtable because animalPtr points to a Dog)
    * and calls the makeNoise() function found in the Dog vtable.
    */
    Animal* animalPtr = &d;
    animalPtr->makeNoise(); // Outputs: "Woof!"

    /**
    * Animal pointer pointing to a Cat object.
    * Similarly, when we call makeNoise() through animalPtr, the compiler uses the vptr to lookup the vtable for the object
    * (which is the Cat vtable because animalPtr now points to a Cat) and calls the makeNoise() function found in the Cat vtable.
    */
    animalPtr = &c;
    animalPtr->makeNoise(); // Outputs: "Meow!"

    return 0;
}