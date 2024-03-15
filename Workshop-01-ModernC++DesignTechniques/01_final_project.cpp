/**
    Problem Statement:

    You are required to implement a Thread-Safe Object Pool for a Message class. The Message class represents a network packet that can be small or large. The class should use Small Object Optimization to avoid dynamic memory allocation for small messages. The Object Pool should utilize RAII principles, provide thread-safe operations, and use Return Value Optimization where possible.
*/

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>

class Message {
public:
    static constexpr size_t short_max = 15;

    Message(const char* str = "") : id(++last_id) {
        size_t len = std::strlen(str);
        if (len <= short_max) {
            std::strcpy(short_data, str);
            is_large = false;
        } else {
            large_data = new char[len + 1];
            std::strcpy(large_data, str);
            is_large = true;
        }
        std::cout << "Message " << id << " created\n";
    }

    ~Message() {
        if (is_large) {
            delete[] large_data;
        }
        std::cout << "Message " << id << " destroyed\n";
    }

    Message(const Message& other) : is_large(other.is_large), id(++last_id) {
        if (is_large) {
            size_t len = std::strlen(other.large_data);
            large_data = new char[len + 1];
            std::strcpy(large_data, other.large_data);
        } else {
            std::strcpy(short_data, other.short_data);
        }
        std::cout << "Message " << id << " copied\n";
    }

    Message& operator=(Message other) {
        std::swap(is_large, other.is_large);
        std::swap(large_data, other.large_data);
        std::cout << "Message " << id << " copied\n";
        return *this;
    }


    // Move constructor
    // This function allows Return Value Optimization (RVO) and Named Return Value Optimization (NRVO)
    // to be applied when a Message object is returned from a function.
    Message(Message&& other) noexcept : is_large(other.is_large), id(other.id) {
        if (is_large) {
            large_data = other.large_data;
            other.large_data = nullptr;
        } else {
            std::strcpy(short_data, other.short_data);
        }
        other.id = 0;
        std::cout << "Message " << id << " moved\n";
    }

    // Move assignment operator
    // This function allows Return Value Optimization (RVO) and Named Return Value Optimization (NRVO)
    // to be applied when a Message object is returned from a function.
    Message& operator=(Message&& other) noexcept {
        std::swap(is_large, other.is_large);
        std::swap(large_data, other.large_data);
        std::swap(id, other.id);
        std::cout << "Message " << id << " moved\n";
        return *this;
    }

private:
    union {
        char* large_data;
        char short_data[short_max + 1];
    };
    bool is_large;
    int id;
    static int last_id;
};

int Message::last_id = 0;

class MessagePool {
public:
    MessagePool(size_t size) {
        for (size_t i = 0; i < size; ++i) {
            pool.emplace(new Message()); // new is used but Message is encapsulated within Message Pool
        }
    }

    ~MessagePool() {
        while (!pool.empty()) {
            delete pool.front();
            pool.pop();
        }
    }

    std::unique_ptr<Message> acquire() {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [this] { return !pool.empty(); });
        auto msg = pool.front();
        pool.pop();
        std::cout << "Message " << msg->id << " acquired from pool\n";
        return std::unique_ptr<Message>(msg);
    }

    void release(std::unique_ptr<Message> msg) {
        std::unique_lock<std::mutex> lock(m);
        std::cout << "Message " << msg->id << " returned to pool\n";
        pool.push(msg.release());
        cv.notify_one();
    }

private:
    std::queue<Message*> pool;
    std::mutex m;
    std::condition_variable cv;
};

// class MessagePool {
// public:
//     MessagePool(size_t size) {
//         for (size_t i = 0; i < size; ++i) {
//             pool.emplace(std::make_unique<Message>());
//         }
//     }

//     std::unique_ptr<Message> acquire() {
//         std::unique_lock<std::mutex> lock(m);
//         cv.wait(lock, [this] { return !pool.empty(); });
//         auto msg = std::move(pool.front());
//         pool.pop();
//         return msg;
//     }

//     void release(std::unique_ptr<Message> msg) {
//         std::unique_lock<std::mutex> lock(m);
//         pool.push(std::move(msg));
//         cv.notify_one();
//     }

// private:
//     std::queue<std::unique_ptr<Message>> pool;
//     std::mutex m;
//     std::condition_variable cv;
// };

int main() {
    MessagePool pool(5); // Create a pool with 5 messages

    auto msg = pool.acquire(); // Acquire a message from the pool
    msg->publicMethod(); // Use the message

    pool.release(std::move(msg)); // Return the message to the pool

    return 0;
}