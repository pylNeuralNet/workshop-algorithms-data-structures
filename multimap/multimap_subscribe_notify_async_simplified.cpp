#include <thread>
#include <vector>
#include <map>
#include <set>
#include <mutex>

class PacketAnalyzer {
    std::map<SubscriberId, std::set<PacketType>> subscriberPreferences;
    std::multimap<PacketType, SubscriberId> packetTypeSubscribers;
    std::mutex notifyMutex; // Mutex for thread-safe subscriber notification

public:
    // ... (subscribe and unsubscribe methods unchanged)

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
        // (This would be an actual implementation to send the notification)
    }
};