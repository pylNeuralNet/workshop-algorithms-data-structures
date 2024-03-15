/*
    pylNeuralNet
    2024

    Object pooling is a software design pattern that uses a set of initialized objects kept ready to use, rather than allocating and deallocating them on the fly. When an object is taken from the pool, it is not available in the pool until it is returned. Objects in the pool have a lifecycle: creation, validation, and destruction.

    In C++, object pooling can be extremely useful for performance-critical applications, such as real-time systems, embedded systems, game programming, or large-scale cloud services, where the cost of object creation/destruction is significant.

    Things to Consider:
    - Object Initialization: Objects should be initialized to a safe state before being added to the pool.

    - Concurrency: If your application is multi-threaded, you'll need to ensure that your object pool is thread-safe. This could be done by adding locks to getObject and returnObject methods.

    - Resource Management: Object pools can be a source of resource leaks if not carefully managed. Be sure that objects are always returned to the pool when no longer in use.

    - Object Validation: When an object is retrieved from the pool, it should be in a valid state. If there is any chance that an object in the pool could be in an invalid state, you should validate it before returning it.

    - Sizing: The size of the pool is typically fixed at creation time. However, some object pool implementations support dynamic resizing, either by creating new objects when the pool is empty or by removing objects from the pool when it is full.

    - Lifetime Management: Object pools manage the lifetime of their objects. This means the pool will decide when to create and destroy objects. You should be careful not to retain references to objects after they have been returned to the pool, as they may be destroyed or reused.

    - Remember, object pooling is not always the best solution. It adds complexity to your code and can lead to subtle bugs if not implemented correctly. Object pooling is best used when the performance benefits are well understood and significant.
*/

#include <queue>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <mutex>
#include <condition_variable>

class Packet {
public:
    Packet() : data(new char[1024]) {}
    ~Packet() { delete[] data; }

    // Other packet related methods (setters/getters, etc.)

private:
    char* data;
};

class PacketPool {
public:
    PacketPool(size_t size) {
        for (size_t i = 0; i < size; ++i) {
            pool.push(new Packet());
        }
    }

    ~PacketPool() {
        while (!pool.empty()) {
            delete pool.front();
            pool.pop();
        }
    }

    Packet* getPacket() {
        std::unique_lock<std::mutex> lock(m);
        while (pool.empty()) {
            cv.wait(lock); // Wait until a packet is returned
        }
        Packet* packet = pool.front();
        pool.pop();
        return packet;
    }

    void returnPacket(Packet* packet) {
        std::unique_lock<std::mutex> lock(m);
        pool.push(packet);
        cv.notify_one(); // Notify a waiting thread that a packet is available
    }

private:
    std::queue<Packet*> pool;
    std::mutex m;
    std::condition_variable cv;
};
class Packet {
public:
    Packet() : data(new char[1024]) {}
    ~Packet() { delete[] data; }

    // Other packet related methods (setters/getters, etc.)

private:
    char* data;
};

class PacketPool {
public:
    PacketPool(size_t size) {
        for (size_t i = 0; i < size; ++i) {
            pool.push(new Packet());
        }
    }

    ~PacketPool() {
        while (!pool.empty()) {
            delete pool.front();
            pool.pop();
        }
    }

    Packet* getPacket() {
        std::unique_lock<std::mutex> lock(m);
        while (pool.empty()) {
            cv.wait(lock); // Wait until a packet is returned
        }
        Packet* packet = pool.front();
        pool.pop();
        return packet;
    }

    void returnPacket(Packet* packet) {
        std::unique_lock<std::mutex> lock(m);
        pool.push(packet);
        cv.notify_one(); // Notify a waiting thread that a packet is available
    }

private:
    std::queue<Packet*> pool;
    std::mutex m;
    std::condition_variable cv;
};

void processPacket(PacketPool& pool, int id) {
    // Get a packet from the pool
    Packet* packet = pool.getPacket();
    std::cout << "Thread " << id << " processing packet" << std::endl;

    // Simulate packet processing delay
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Return the packet to the pool
    pool.returnPacket(packet);
    std::cout << "Thread " << id << " returned packet" << std::endl;
}

int main() {
    PacketPool pool(10); // Create a pool with 10 packets

    std::vector<std::thread> threads;
    for (int i = 0; i < 20; ++i) {
        threads.push_back(std::thread(processPacket, std::ref(pool), i));
    }

    // Wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}

/**
    In this example, 20 threads are created, each of which simulates processing a packet. Since the PacketPool only contains 10 packets, some threads will need to wait until a packet becomes available. The output will show the sequence of packet processing and returning events.

    Please note that the output sequence might be different every time you run this program because the OS scheduler determines the order in which the threads are run.

    Also, please note that this example omits error checking and exception handling for brevity. In real-world code, you'd want to add appropriate error checking and handle exceptions where necessary. For example, you might want to handle the case where new fails to allocate memory for a Packet.
*/