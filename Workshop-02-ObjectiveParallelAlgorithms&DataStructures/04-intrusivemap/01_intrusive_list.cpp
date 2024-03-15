#include <boost/intrusive/list.hpp>

using namespace boost::intrusive;

// Define a class that can be inserted into an intrusive list
class MyClass : public list_base_hook<> {
public:
    int value;

    MyClass(int value) : value(value) {}
};

int main() {
    // Create a list object
    list<MyClass> myList;

    // Create objects. They MUST stay valid as long as they are in the list
    MyClass obj1(1), obj2(2);

    // Insert the objects into the list
    myList.push_back(obj1);
    myList.push_back(obj2);

    // Iterate over the list and print the values
    for (const MyClass &obj : myList) {
        std::cout << obj.value << '\n';
    }

    return 0;
}