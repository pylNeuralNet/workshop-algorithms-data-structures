#include <iostream>
#include <vector>
#include <tuple>

template<typename T>
class VectorWrapper {
private:
    std::vector<T> data;

public:
    // Constructor that initializes the vector with an initializer list.
    VectorWrapper(std::initializer_list<T> il) : data(il) {}

    // Overloaded subscript operator for accessing elements by index.
    T& operator[](size_t index) {
        return data.at(index); // at() checks for bounds and throws std::out_of_range if index is out of bounds
    }

    // Overloaded subscript operator for const access to elements by index.
    const T& operator[](size_t index) const {
        return data.at(index);
    }

    // Function for structured bindings usage by returning a tuple.
    auto getElements() const -> const std::vector<T>& {
        return data;
    }

    // Member function to demonstrate passing by rvalue reference.
    void addElement(T&& newElement) {
        data.push_back(std::move(newElement)); // std::move casts newElement to an rvalue to use vector's move semantics
    }
};

int main() {
    VectorWrapper<int> myVector{1, 2, 3, 4};

    // Demonstrate the subscript operator.
    std::cout << "Element at index 2: " << myVector[2] << std::endl;

    // Demonstrate structured bindings (C++17 feature).
    const auto& [first, second, third, fourth] = myVector.getElements();
    std::cout << "Structured bindings: " << first << ", " << second << ", " << third << ", " << fourth << std::endl;

    // Demonstrate passing by rvalue reference.
    myVector.addElement(5);
    std::cout << "After adding 5: ";
    for (const auto& elem : myVector.getElements()) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}