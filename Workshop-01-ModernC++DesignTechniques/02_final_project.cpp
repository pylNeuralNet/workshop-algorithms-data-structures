/**
    Problem Statement:

    You are developing a network security application that processes network packets. You need to create a Packet class that represents a network packet. Each packet has an integer ID, a string payload, and a string timestamp.

    Your Packet class should support the following operations:

        SetPayload(payload): Sets the payload of the packet. This operation is expensive and should avoid unnecessary copies.
        GetPayload(): Returns the payload of the packet.
        PrintPacket(): Prints all the information of the packet.
    
    Now, suppose you also maintain a PacketLog class that keeps a log of all packets processed. The PacketLog class should support the following operations:

        AddPacket(packet): Adds a packet to the log.
        UpdatePacket(id, payload): Updates the payload of a packet in the log. If the packet doesn't exist in the log, it should do nothing.
        PrintLog(): Prints all packets in the log.
    Implement these classes and their methods efficiently.
*/

#include <unordered_map>
#include <iostream>
#include <string>

class Packet {
private:
    int id;
    std::string payload;
    std::string timestamp;
public:
    Packet(int id, std::string&& payload, const std::string& timestamp)
        : id(id), payload(std::move(payload)), timestamp(timestamp) {}

    void SetPayload(std::string&& payload) {
        this->payload = std::move(payload);  // std::move allows us to avoid copying the payload string
    }

    const std::string& GetPayload() const {  // return by const reference to avoid copying the string
        return payload;
    }

    void PrintPacket() const {
        std::cout << "Packet ID: " << id << ", Payload: " << payload << ", Timestamp: " << timestamp << "\n";
    }
    // Other methods...
};

class PacketLog {
private:
    std::unordered_map<int, Packet> packet_log;

public:
    void AddPacket(Packet&& packet) {
        // Use the packet's ID as the key in the map
        packet_log.emplace(packet.GetID(), std::move(packet));
        // std::move allows us to avoid copying the Packet object
    }

    void UpdatePacket(int id, std::string&& payload) {
        auto it = packet_log.find(id);
        if (it != packet_log.end()) {
            it->second.SetPayload(std::move(payload));  // std::move allows us to avoid copying the payload string
        }
    }

    void PrintLog() const {
        for (const auto& [id, packet] : packet_log) {  // structured bindings to decompose the map entries
            packet.PrintPacket();
        }
    }
    // Other methods...
};