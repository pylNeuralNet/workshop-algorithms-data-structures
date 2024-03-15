In C++, Run-Time Type Identification (RTTI) provides a way to discover type information at runtime. It involves concepts such as typeid operator, type_info class and dynamic casting.

typeid is an operator which is used to identify the class type of an expression. If the type is a polymorphic class and the argument is a pointer or reference to a base class, typeid returns the type of the pointed or referred object. If the argument is anything else, typeid returns the static type of the argument.
```C++
double d = 3.14;
std::cout << typeid(d).name() << std::endl;  // Output: "d" for double
```

type_info is a class that holds the type information. It is used by typeid operator to represent types. It provides member functions to compare two types for equality or collating order, and to access the null-terminated multibyte C string representing the human-readable name of the type.
```C++
const std::type_info& info = typeid(d);
std::cout << info.name() << std::endl;  // Output: "d" for double
```

Dynamic casting (dynamic_cast) is used for handling polymorphic types. It's a way to safely convert from a pointer (or reference) to a base class to a pointer (or reference) to a derived class. This cast checks if the conversion is safe and returns nullptr (or throws an exception for references) if it's not.

```C++
class Base { virtual void dummy() {} };
class Derived: public Base { int a; };

int main() {
    Base* b1 = new Derived;
    if(auto d1 = dynamic_cast<Derived*>(b1)) {
        std::cout << "safe to cast" << std::endl;
    }
    delete b1;
    return 0;
}
```

std::variant, on the other hand, is a type-safe union, an instance of which can hold an instance of any of its alternative types (it was introduced in C++17). It keeps track of what type it currently holds. This type information can be queried with std::holds_alternative and std::get.

Here is an example:

```C++
std::variant<int, float> v;
v = 12; // v contains int
std::cout << std::get<int>(v) << std::endl; // prints 12
v = 12.0f; // v contains float
std::cout << std::get<float>(v) << std::endl; // prints 12.0
```

std::variant can be seen as a way to use static, compile-time polymorphism to achieve some of the same results as dynamic polymorphism with RTTI, but with different trade-offs. It is a relatively new addition to the language and is not yet as widely used as dynamic polymorphism and RTTI.