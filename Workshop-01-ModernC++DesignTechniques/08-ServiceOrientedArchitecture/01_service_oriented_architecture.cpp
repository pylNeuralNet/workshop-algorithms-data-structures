/**
    Service-Oriented Architecture (SOA) is a design pattern where services are provided to other components via a communication protocol over a network. The basic principles of service-oriented architecture are independent of vendors, products, and technologies.

    In a Service-Oriented Architecture (SOA), services are designed to communicate with each other within the same application process. They can operate on separate threads, like in the C++ example I provided before where ServiceA and ServiceB are running on separate threads and communicating via the MessageQueue. These services can be considered "in-process" services as they reside in the same memory space and communicate directly with each other through memory. This allows for efficient communication but requires careful synchronization to avoid concurrency issues. In the SOA case, the services are loosely coupled, meaning that they interact with each other through well-defined interfaces and can be developed and updated independently as long as the interfaces remain the same.

    In contrast, a Microservices Architecture involves services that run in separate processes, often on separate machines. These services communicate over a network protocol, such as HTTP, gRPC, or AMQP, which requires data to be serialized and deserialized for transmission. This inter-service communication can be slower and more complex than in SOA, due to the need to handle network latency, failures, and data serialization. However, it allows each service to be developed, deployed, and scaled independently, and can be more resilient to faults since a failure in one service doesn't directly affect the others.

    The key distinction between SOA and Microservices is the boundary of the services and how they communicate. In SOA, the services reside within the same application boundary and communicate in-process, whereas in a Microservices architecture, each service is its own separate application, running in its own process and communicating over a network.
*/

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

class MessageQueue {
    std::queue<int> queue;
    std::mutex mtx;
    std::condition_variable cv;

public:
    void send(int message) {
        std::lock_guard<std::mutex> lock(mtx);
        queue.push(message);
        cv.notify_one();
    }

    int receive() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this](){ return !queue.empty(); }); // block until a message is available
        int message = queue.front();
        queue.pop();
        return message;
    }
};

class ServiceA {
    MessageQueue& queue;
public:
    ServiceA(MessageQueue& q) : queue(q) {}

    void operator()() {
        for (int i = 0; i < 10; ++i) {
            std::cout << "ServiceA sending message: " << i << std::endl;
            queue.send(i);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};

class ServiceB {
    MessageQueue& queue;
public:
    ServiceB(MessageQueue& q) : queue(q) {}

    void operator()() {
        while (true) {
            int message = queue.receive();
            std::cout << "ServiceB received message: " << message << std::endl;
        }
    }
};

int main() {
    MessageQueue queue;

    ServiceA serviceA(queue);
    ServiceB serviceB(queue);

    std::thread threadA(serviceA);
    std::thread threadB(serviceB);

    threadA.join();
    threadB.detach();

    return 0;
}

/**
    In this example, ServiceA and ServiceB are two services that communicate with each other over a MessageQueue. ServiceA sends messages to ServiceB by pushing them to the message queue. ServiceB receives messages by pulling them from the message queue. Both services run in their own threads and communicate asynchronously.

    This is an example of SOA as each service is separate and communicates via a well defined interface (the MessageQueue). This makes it easy to modify or replace one service without affecting the others, as long as the communication interface remains the same.

    This approach can be contrasted with other architectures like monolithic architecture, where all the functionalities are handled in one component, or microservices architecture, where each service runs in its own process and communicates over the network.

    SOA gives a balance between these two extremes. It has more modularity than a monolithic architecture, making it easier to develop and maintain, but it has less overhead than a microservices architecture as communication between services is done in-process rather than over the network.

    However, it's worth noting that C++ is generally not the first choice for implementing SOA due to the lack of built-in support for networking and serialization. Languages like Java or frameworks like .NET, which have built-in support for these features, are generally more commonly used for SOA.
*/