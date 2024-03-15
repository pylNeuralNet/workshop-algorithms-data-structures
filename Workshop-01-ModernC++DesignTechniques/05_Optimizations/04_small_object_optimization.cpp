#include <cstring> // for std::strlen, std::strcpy
#include <algorithm> // for std::copy

class Packet {
public:
    /**
     * Constructor
     * Initializes the packet with the given data.
     * If the data is small enough, it is stored directly in the Packet object.
     * Otherwise, memory is allocated dynamically to store the data.
     */
    Packet(const char* data) {
        size_t len = std::strlen(data);
        if (len <= short_max) {
            std::strcpy(short_data, data);
            is_large = false;
        } else {
            large_data = new char[len + 1];
            std::strcpy(large_data, data);
            is_large = true;
        }
    }

    /**
     * Destructor
     * If the packet is large and memory was allocated dynamically,
     * it needs to be deallocated here to prevent a memory leak.
     */
    ~Packet() {
        if (is_large) {
            delete[] large_data;
        }
    }

    /**
     * Copy Constructor
     * Follows the Rule of Three - since we have a custom destructor and are managing
     * memory, we need to also provide a custom copy constructor to correctly duplicate
     * the Packet object. If we didn't, the compiler would generate a default copy
     * constructor that performs a shallow copy, which could lead to problems such as
     * double deletion.
     */
    Packet(const Packet& other) : is_large(other.is_large) {
        if (is_large) {
            size_t len = std::strlen(other.large_data);
            large_data = new char[len + 1];
            std::strcpy(large_data, other.large_data);
        } else {
            std::strcpy(short_data, other.short_data);
        }
    }

    /**
     * Copy Assignment Operator
     * Also part of the Rule of Three. Ensures that the copy assignment is done correctly.
     * If we didn't provide this, the compiler would generate a default copy assignment
     * operator that performs a shallow copy.
     */
    Packet& operator=(const Packet& other) {
        if (&other == this) {
            return *this;
        }

        if (is_large) {
            delete[] large_data;
        }

        is_large = other.is_large;

        if (is_large) {
            size_t len = std::strlen(other.large_data);
            large_data = new char[len + 1];
            std::strcpy(large_data, other.large_data);
        } else {
            std::strcpy(short_data, other.short_data);
        }

        return *this;
    }

    const char* getData() const {
        return is_large ? large_data : short_data;
    }

private:
    static constexpr size_t short_max = 15;
    union {
        char* large_data;
        char short_data[short_max + 1];
    };
    bool is_large;
};

Packet createPacket() {
    Packet packet("short");
    return packet;
}

int main() {
    Packet packet = createPacket();
    std::cout << "Packet data: " << packet.getData() << std::endl;

    return 0;
}