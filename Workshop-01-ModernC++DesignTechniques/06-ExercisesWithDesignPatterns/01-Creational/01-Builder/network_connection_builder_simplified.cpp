/*
    pylNeuralNet
    2024

    Why use the Builder pattern in this case?

        1. Separation of concerns: The construction logic is isolated from the representation, making it easier to manage complexity and maintain the code.
        2. Flexibility: Different ConcreteBuilders can be created for different types of network connections without changing the underlying Director or Product classes.
        3. Scalability: New configurations and features can be added to the builders as the system evolves without affecting existing client code.
        4. Readability: The Director's API simplifies the construction process, making the client code more readable and easier to understand.

    C++20 Features and Problems Solved:

        1. RAII and Resource Management: By utilizing smart pointers such as std::unique_ptr, the Builder pattern inherently supports RAII, ensuring that resources are properly managed and released, which is critical in embedded systems.
        2. Multithreading with std::jthread: The Builder pattern can be combined with std::jthread to allow for safe and easy handling of threads when constructing the network connection, ensuring threads are joined or detached appropriately.
        3. Compile-Time Safety: The use of modern C++ features like concepts (if required) can add compile-time checks to ensure that the Builders conform to certain constraints, leading to safer and more robust code.

    By using the Builder pattern, the embedded system's network connection setup becomes modular, maintainable, and easily adaptable to future changes, which is crucial in a senior developer's code for an embedded multithreaded system.
*/

// Product
class NetworkConnection {
public:
    // Various configuration settings for a network connection
    // ...
};

// Builder Interface
class NetworkConnectionBuilder {
public:
    virtual ~NetworkConnectionBuilder() = default;
    virtual void setupSecurity() = 0;
    virtual void setupNetworking() = 0;
    virtual void setupMessaging() = 0;
    virtual std::unique_ptr<NetworkConnection> getResult() = 0;
};

// Concrete Builder for a specific type of network connection
class SecureNetworkConnectionBuilder : public NetworkConnectionBuilder {
private:
    std::unique_ptr<NetworkConnection> connection;

public:
    SecureNetworkConnectionBuilder() : connection(std::make_unique<NetworkConnection>()) {}

    void setupSecurity() override {
        // Implement security protocols like dot1x, IPSec
        // ...
    }

    void setupNetworking() override {
        // Implement networking configurations like DNS
        // ...
    }

    void setupMessaging() override {
        // Implement message exchange configurations
        // ...
    }

    std::unique_ptr<NetworkConnection> getResult() override {
        return std::move(connection);
    }
};

// Director
class NetworkManager {
public:
    std::unique_ptr<NetworkConnection> createConnection(NetworkConnectionBuilder& builder) {
        builder.setupSecurity();
        builder.setupNetworking();
        builder.setupMessaging();
        return builder.getResult();
    }
};