// Copy-and-Swap Idiom: This is a technique that can provide a clean and efficient assignment operator by using a copy constructor, destructor, and std::swap.
#include <algorithm> // std::swap
#include <vector>
#include <iostream>

class Widget {
public:
    // Constructor
    Widget(int size) : data(size) {}

    // Copy Constructor
    Widget(const Widget& other) : data(other.data) {}

    // Destructor
    ~Widget() {}

    // Copy-and-Swap Idiom: Assignment Operator
    Widget& operator=(Widget other) { // Note: 'other' is passed by value
        /** 
         * Swap the current object's resources with the 'other' object's resources.
         * This effectively reuses the copy-constructor and destructor to manage resources,
         * providing a strong exception guarantee. If an exception is thrown during the
         * copy construction of 'other', the current object remains unaffected.
         */
        swap(*this, other);
        return *this;
    }

    // Swap function
    friend void swap(Widget& first, Widget& second) noexcept {
        /** 
         * Swap all the resources of 'first' and 'second'.
         * This operation is noexcept as it should not throw any exceptions.
         * Using std::swap to swap individual members is an efficient way to ensure
         * that all resources are swapped correctly.
         */
        using std::swap;
        swap(first.data, second.data);
    }

private:
    std::vector<int> data;
};

int main() {
    // Create two Widget objects
    Widget widgetA(10); // A Widget with 10 integers
    Widget widgetB(20); // A Widget with 20 integers

    std::cout << "Assigning widgetB to widgetA" << std::endl;
    widgetA = widgetB; // Use the copy-and-swap idiom for assignment

    // The resources of widgetA and widgetB are swapped,
    // and the old resources of widgetA are safely destroyed
    // when the temporary object is destructed at the end of this scope.

    std::cout << "Assignment complete" << std::endl;

    // Normally, you would have some mechanism to observe the state
    // of the widgets to confirm the assignment, such as a member function
    // to print the contents or sizes of the internal data.

    return 0;
}
