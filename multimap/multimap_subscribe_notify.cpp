class PacketAnalyzer {
    std::map<SubscriberId, std::set<PacketType>> subscriberPreferences;
    std::multimap<PacketType, SubscriberId> packetTypeSubscribers;

public:
    void subscribe(SubscriberId subscriberId, PacketType packetType) {
        subscriberPreferences[subscriberId].insert(packetType);
        packetTypeSubscribers.insert({packetType, subscriberId});
    }

    void unsubscribe(SubscriberId subscriberId, PacketType packetType) {
        subscriberPreferences[subscriberId].erase(packetType);
        auto range = packetTypeSubscribers.equal_range(packetType);
        for (auto it = range.first; it != range.second; ) {
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
        
        // Conquer: process each packet type in parallel
        // (This could be done with threads, async tasks, etc.)
        for (const auto& [packetType, packets] : packetsByType) {
            // Notify subscribers interested in this packet type
            auto subscribers = packetTypeSubscribers.equal_range(packetType);
            for (const auto& packet : packets) {
                for (auto it = subscribers.first; it != subscribers.second; ++it) {
                    notifySubscriber(it->second, packet);
                }
            }
        }
    }

    void notifySubscriber(SubscriberId subscriberId, const Packet& packet) {
        // Notify the subscriber about the packet
        // (This would be an actual implementation to send the notification)
    }
};