/*
    Some SEI CERT C++ rules related to alignment and padding:
    - https://wiki.sei.cmu.edu/confluence/display/cplusplus/MEM57-CPP.+Avoid+using+default+operator+new+for+over-aligned+types
    - https://wiki.sei.cmu.edu/confluence/display/cplusplus/MEM54-CPP.+Provide+placement+new+with+properly+aligned+pointers+to+sufficient+storage+capacity
    - https://wiki.sei.cmu.edu/confluence/display/cplusplus/DCL55-CPP.+Avoid+information+leakage+when+passing+a+class+object+across+a+trust+boundary
    - https://wiki.sei.cmu.edu/confluence/display/cplusplus/MEM53-CPP.+Explicitly+construct+and+destruct+objects+when+manually+managing+object+lifetime
    - https://wiki.sei.cmu.edu/confluence/display/cplusplus/DCL60-CPP.+Obey+the+one-definition+rule
    - https://wiki.sei.cmu.edu/confluence/display/cplusplus/EXP62-CPP.+Do+not+access+the+bits+of+an+object+representation+that+are+not+part+of+the+object%27s+value+representation

    Alignment is about how data is positioned in memory. Specifically, it's about the "evenness" of the address where a data object is stored. Some types of data perform better when they are located on addresses that are multiples of a particular value (like 4, 8, or 16). This multiple is called the "alignment" of the data.

    For example, on many systems, an int is 4 bytes and should be aligned on a 4-byte boundary for optimal performance. This means that the memory address where the int is stored is a multiple of 4.

    Padding is extra space that is added between data objects to ensure that they are properly aligned. Padding can occur at the end of a struct to align the size of the struct to the alignment requirement of some of its members.
*/

#include <iostream>
#include <new>
#include <cstdint>
#include <cstddef>
#include <cstring>

constexpr size_t alignment = 16; // Forcing 16 bytes alignment as an example
constexpr size_t bufSize = 1024; // For example purposes

// A type that requires 16 bytes alignment
struct alignas(alignment) PacketHeader {
    uint64_t timestamp; // 8 bytes
    uint32_t packetId;  // 4 bytes
    uint16_t checksum;  // 2 bytes
    // 2 bytes padding here to align to 16 bytes
};

static_assert(sizeof(PacketHeader) == 16, "PacketHeader size should be 16 bytes");

// Buffer to hold PacketHeaders
alignas(alignment) char buffer[bufSize];

void processPacket(PacketHeader* header) {
    // process the packet here...
    std::cout << "Processing packet with ID: " << header->packetId << '\n';
}

int main() {
    // Ensure the buffer is properly aligned
    if (reinterpret_cast<uintptr_t>(buffer) % alignment != 0) {
        std::cerr << "Buffer not correctly aligned!\n";
        return 1;
    }

    // Construct a PacketHeader in the buffer
    auto* header = new (buffer) PacketHeader{123456789, 42, 5555};

    // Process the packet
    processPacket(header);

    // Destruct the packet manually
    header->~PacketHeader();

    return 0;
}