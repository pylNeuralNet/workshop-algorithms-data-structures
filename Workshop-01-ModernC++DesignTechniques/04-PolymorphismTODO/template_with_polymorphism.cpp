#include <iostream>

/** A common base class that defines a virtual function. */
class Animal {
public:
    virtual void makeNoise() = 0; // pure virtual function
};

/** A class template that inherits from Animal and implements the virtual function. */
template <typename T>
class AnimalType : public Animal {
public:
    /** Implement the pure virtual function. */
    void makeNoise() override {
        std::cout << "AnimalType<" << typeid(T).name() << "> noise\n";
    }
};

int main() {
    /** Create instances of our classes. */
    AnimalType<int> animalInt;
    AnimalType<double> animalDouble;

    /** Animal pointer pointing to an AnimalType<int> object. */
    Animal* animalPtr = &animalInt;
    animalPtr->makeNoise(); // Outputs: "AnimalType<int> noise"

    /** Animal pointer pointing to an AnimalType<double> object. */
    animalPtr = &animalDouble;
    animalPtr->makeNoise(); // Outputs: "AnimalType<double> noise"

    return 0;
}