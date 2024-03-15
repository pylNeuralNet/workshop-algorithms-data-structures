#include <iostream>
#include <memory>
#include <map>
#include <thread>
#include <mutex>

/**
 * The Connection class hierarchy represents different types of network connections.
 * Polymorphism is used to provide a common interface for all connection types.
 */
class Connection {
public:
    virtual ~Connection() = default;
    virtual void connect() = 0;
    virtual void transferData() = 0;
    virtual void disconnect() = 0;
};

class EthernetConnection : public Connection {
public:
    void connect() override {
        std::cout << "Ethernet connection established.\n";
    }
    void transferData() override {
        std::cout << "Data transferring over Ethernet.\n";
    }
    void disconnect() override {
        std::cout << "Ethernet connection disconnected.\n";
    }
};

class WiFiConnection : public Connection {
public:
    void connect() override {
        std::cout << "WiFi connection established.\n";
    }
    void transferData() override {
        std::cout << "Data transferring over WiFi.\n";
    }
    void disconnect() override {
        std::cout << "WiFi connection disconnected.\n";
    }
};

class CellularConnection : public Connection {
public:
    void connect() override {
        std::cout << "Cellular connection established.\n";
    }
    void transferData() override {
        std::cout << "Data transferring over Cellular.\n";
    }
    void disconnect() override {
        std::cout << "Cellular connection disconnected.\n";
    }
};

/**
 * The ConnectionFactory class is a Factory for creating connections.
 * It uses a map from strings to std::function to decide which connections to create.
 * This is a form of metaprogramming, using the type system to generate code.
 */
class ConnectionFactory {
public:
    ConnectionFactory() {
        creators["Ethernet"] = [] { return std::make_unique<EthernetConnection>(); };
        creators["WiFi"] = [] { return std::make_unique<WiFiConnection>(); };
        creators["Cellular"] = [] { return std::make_unique<CellularConnection>(); };
    }

    std::unique_ptr<Connection> createConnection(const std::string& type) {
        return creators[type]();
    }

private:
    std::map<std::string, std::function<std::unique_ptr<Connection>()>> creators;
};

/**
 * The ConnectionManager class is responsible for creating and managing connections.
 * It uses RAII principles - the constructor creates a ConnectionFactory, and the destructor joins the thread.
 * This ensures that resources are correctly managed even in the case of exceptions.
 */
class ConnectionManager {
public:
    ConnectionManager(const std::string& connectionType) : factory(), connectionType(connectionType) {
        managementThread = std::thread([this] {
            while (!done) {
                manageConnection();
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        });
    }

    ~ConnectionManager() {
        done = true;
        managementThread.join();
    }

    void manageConnection() {
        std::unique_ptr<Connection> connection = factory.createConnection(connectionType);
        std::lock_guard<std::mutex> lock(consoleMutex);
        connection->connect();
        connection->transferData();
        connection->disconnect();
    }

private:
    ConnectionFactory factory;
    std::string connectionType;
    std::thread managementThread;
    std::atomic<bool> done{false};
    static std::mutex consoleMutex;
};

std::mutex ConnectionManager::consoleMutex;

int main() {
    // Create a ConnectionManager for each type of connection
    ConnectionManager ethernetManager("Ethernet");
    ConnectionManager wifiManager("WiFi");
    ConnectionManager cellularManager("Cellular");

    // The ConnectionManagers will automatically be destroyed when they go out of scope,
    // stopping their management threads and ensuring that all resources are cleaned up correctly.
    std::this_thread::sleep_for(std::chrono::seconds(10));
    return 0;
}