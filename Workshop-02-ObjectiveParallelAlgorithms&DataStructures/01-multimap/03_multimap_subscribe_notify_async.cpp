#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <thread>
#include <mutex>

// Define PacketType as an enum for simplicity
enum class PacketType {
    HTTP,
    FTP,
    SSH,
    // ... other packet types
};

// Packet structure
struct Packet {
    PacketType type;
    std::string content; // Simplified content representation
};

// SubscriberId type
using SubscriberId = int;

// Define a simple Subscriber class
class Subscriber {
public:
    SubscriberId id;
    // ... other subscriber details

    Subscriber(SubscriberId id) : id(id) {}

    void notify(const Packet& packet) {
        // Placeholder for the notification logic
        std::cout << "Subscriber " << id << " received packet: " << packet.content << std::endl;
    }
};

// Forward declaration for Subscriber
class Subscriber;

class PacketAnalyzer {
    std::map<SubscriberId, std::set<PacketType>> subscriberPreferences;
    std::multimap<PacketType, SubscriberId> packetTypeSubscribers;
    std::mutex notifyMutex; // Mutex for thread-safe subscriber notification

public:
    void subscribe(SubscriberId subscriberId, PacketType packetType) {
        subscriberPreferences[subscriberId].insert(packetType);
        packetTypeSubscribers.insert({packetType, subscriberId});
    }

    void unsubscribe(SubscriberId subscriberId, PacketType packetType) {
        subscriberPreferences[subscriberId].erase(packetType);
        auto range = packetTypeSubscribers.equal_range(packetType);
        for (auto it = range.first; it != range.second;) {
            if (it->second == subscriberId) {
                it = packetTypeSubscribers.erase(it);
            } else {
                ++it;
            }
        }
    }

    void processPackets(const std::vector<Packet>& packets) {
        // Divide packets by type
        std::map<PacketType, std::vector<Packet>> packetsByType;
        for (const auto& packet : packets) {
            packetsByType[packet.type].push_back(packet);
        }

        // Vector to hold the threads
        std::vector<std::thread> threads;

        // Create a thread for each packet type
        for (const auto& [packetType, packetsOfType] : packetsByType) {
            threads.emplace_back([this, packetType, packetsOfType]() {
                // Notify subscribers interested in this packet type
                auto subscribers = packetTypeSubscribers.equal_range(packetType);
                for (const auto& packet : packetsOfType) {
                    for (auto it = subscribers.first; it != subscribers.second; ++it) {
                        notifySubscriber(it->second, packet);
                    }
                }
            });
        }

        // Join all threads to ensure completion of packet processing
        for (std::thread& thread : threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
    }

    void notifySubscriber(SubscriberId subscriberId, const Packet& packet) {
        std::lock_guard<std::mutex> guard(notifyMutex); // Ensure thread safety
        // Notify the subscriber about the packet
        // In a real-world scenario, you'd have more sophisticated notification logic here.
        // For this example, simply print the notification to the console.
        std::cout << "Subscriber " << subscriberId << " notified about packet of type "
                  << static_cast<int>(packet.type) << std::endl;
    }
};

int main() {
    PacketAnalyzer analyzer;

    // Create some subscribers and subscribe them to different packet types
    SubscriberId alice = 1;
    SubscriberId bob = 2;
    analyzer.subscribe(alice, PacketType::HTTP);
    analyzer.subscribe(bob, PacketType::FTP);

    // Create a list of packets to be processed
    std::vector<Packet> packets = {
        {PacketType::HTTP, "HTTP Packet 1"},
        {PacketType::FTP, "FTP Packet 1"},
        {PacketType::SSH, "SSH Packet 1"},
        {PacketType::HTTP, "HTTP Packet 2"},
        {PacketType::FTP, "FTP Packet 2"}
    };

    // Process the packets
    analyzer.processPackets(packets);

    return 0;
}