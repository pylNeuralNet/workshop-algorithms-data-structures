/*
    pylNeuralNet
    2024

    RVO - return value optimization
    NRVO - named return value optimization

    Here, we demonstrate Return Value Optimization (RVO) and Named Return Value Optimization (NRVO), two compiler optimizations that eliminate the need for costly deep copies when objects are returned by value from functions.

    We'll create a Packet class that represents a network packet and tracks the number of copies made:
*/

#include <iostream>
#include <cstring>

class Packet {
public:
    static int copy_count;  // count of the number of copies

    Packet(size_t size) : size(size), data(new char[size]) {
        std::cout << "Packet created\n";
    }

    Packet(const Packet& other) : size(other.size), data(new char[size]) {
        std::memcpy(data, other.data, size);
        ++copy_count;
        std::cout << "Packet copied\n";
    }

    ~Packet() {
        delete[] data;
    }

    // Other packet methods...

private:
    size_t size;
    char* data;
};

int Packet::copy_count = 0;

Packet createPacket(size_t size) {
    Packet packet(size);
    // Fill packet data...
    return packet;  // NRVO applies here, otherwise it would've created another copy
}

int main() {
    /**
    Here's what happens without any optimizations:
    - Inside createPacket, a Packet object is created.
    - When createPacket returns, a copy of this Packet object is made (this invokes the copy constructor).
    - This copy is used to initialize packet in main.
    */
    Packet packet = createPacket(1024);  // RVO applies here
    std::cout << "Number of copies: " << Packet::copy_count << '\n';
    return 0;
}

/*
    When you run this program, you will see that "Packet copied" is not printed and Packet::copy_count is 0, indicating that no copies were made. This is due to RVO and NRVO.

    RVO and NRVO are compiler optimizations that eliminate the need for copy operations when an object is returned by value from a function. RVO applies when the returned object is a nameless temporary. NRVO applies when the returned object is a named object in the function (like packet in createPacket).

    These optimizations can significantly improve performance by avoiding unnecessary copies, but they are not guaranteed by the C++ language standard. However, most modern compilers apply them in release builds where the code allows.
*/