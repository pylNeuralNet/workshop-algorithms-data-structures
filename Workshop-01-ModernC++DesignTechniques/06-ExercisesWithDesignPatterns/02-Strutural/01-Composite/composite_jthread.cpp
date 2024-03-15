#include <iostream>
#include <vector>
#include <memory>
#include <thread>

// Component interface declaring common operations for both simple and composite objects
class PacketComponent {
public:
    virtual ~PacketComponent() = default;
    virtual void processPacket() = 0;
};

// Leaf class representing individual packets
class IndividualPacket : public PacketComponent {
public:
    void processPacket() override {
        // Process the individual packet (e.g., parsing headers, modifying payload)
        std::cout << "Processing individual packet" << std::endl;
    }
};

// Composite class representing a collection of packets
class CompositePacket : public PacketComponent {
private:
    std::vector<std::shared_ptr<PacketComponent>> children;

public:
    void addPacket(std::shared_ptr<PacketComponent> packetComponent) {
        children.push_back(packetComponent);
    }

    void processPacket() override {
        // Process each packet in the collection
        for (auto& child : children) {
            child->processPacket();
        }
    }
};

// Multithreading and RAII with jthread
class PacketProcessor {
private:
    std::shared_ptr<PacketComponent> packetTreeRoot;

public:
    PacketProcessor(std::shared_ptr<PacketComponent> root) : packetTreeRoot(root) {}

    void processPacketsConcurrently() {
        std::jthread worker([&] {
            packetTreeRoot->processPacket();
        });
    }
};

int main() {
    // Construct a packet tree
    auto root = std::make_shared<CompositePacket>();
    auto branch1 = std::make_shared<CompositePacket>();
    auto branch2 = std::make_shared<CompositePacket>();

    root->addPacket(branch1);
    root->addPacket(branch2);

    branch1->addPacket(std::make_shared<IndividualPacket>());
    branch1->addPacket(std::make_shared<IndividualPacket>());

    branch2->addPacket(std::make_shared<IndividualPacket>());
    branch2->addPacket(std::make_shared<IndividualPacket>());

    // Process the packet tree
    PacketProcessor processor(root);
    processor.processPacketsConcurrently();

    // Main thread can continue doing other tasks
    // ...
    
    return 0;
}