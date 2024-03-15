/*
    pylNeuralNet
    2024
*/

/*
    The Bridge Design Pattern is a structural pattern that helps in dividing a monolithic class into separate class hierarchies - abstraction and implementation. This can lead to an easier-to-maintain codebase and can potentially increase the performance by reducing the class hierarchy complexity.

    Let's consider a use-case of an embedded system, specifically a network device that supports different types of network connections and protocols. We can have an abstract 'Connection' class and several concrete 'Protocol' classes. The Bridge pattern can be used to separate the connection from the protocol, so that the two can vary independently.

        1. Decoupling of abstraction and implementation: By separating the connection from the protocol, the two can vary independently. This means we can add more protocols or connection types without changing the existing code.

        2. Single Responsibility Principle: Each class or module is responsible for a single part of the system's functionality, which is encapsulated by the class.

        3. Open-Closed Principle: The system is open for extension (we can add more protocols or connection types) but closed for modification.
*/

#include <iostream>
#include <string>
#include <memory>

// Implementor
class Protocol {
public:
    virtual ~Protocol() = default;
    virtual void send(const std::string& message) const = 0;
};

class Dot1x : public Protocol {
public:
    void send(const std::string& message) const override {
        std::cout << "Dot1x: " << message << std::endl;
    }
};

class IPSec : public Protocol {
public:
    void send(const std::string& message) const override {
        std::cout << "IPSec: " << message << std::endl;
    }
};

// Abstraction
class Connection {
public:
    // The constructor takes ownership of the Protocol object using std::move,
    // avoiding unnecessary copying and allowing the Connection object to manage
    // the Protocol's memory.
    Connection(std::unique_ptr<Protocol> protocol) : protocol_(std::move(protocol)) {}
    virtual ~Connection() = default;

    virtual void send(const std::string& message) {
        protocol_->send(message);
    }

protected:
    std::unique_ptr<Protocol> protocol_;
};

// Refined abstraction
class SecureConnection : public Connection {
public:
    SecureConnection(std::unique_ptr<Protocol> protocol) : Connection(std::move(protocol)) {}

    void send(const std::string& message) override {
        std::cout << "Securing data..." << std::endl;
        Connection::send(message);
    }
};

int main() {
    // Create a regular connection with Dot1x protocol
    std::unique_ptr<Protocol> dot1x = std::make_unique<Dot1x>();
    Connection regularConnection(std::move(dot1x));
    regularConnection.send("Hello through regular connection!");

    // Create a secure connection with IPSec protocol
    std::unique_ptr<Protocol> ipsec = std::make_unique<IPSec>();
    SecureConnection secureConnection(std::move(ipsec));
    secureConnection.send("Hello through secure connection!");
    
    return 0;
}