/*
    pylNeuralNet
    2024
*/

/*
    In the example, Protocol is a Flyweight class which is used to store the common data associated with a protocol. ProtocolFactory is a factory class that creates a new Protocol object only if no matching object exists; otherwise, it returns a pointer to the already created Protocol object.

    The Flyweight pattern is useful in this case because it allows sharing of common data between objects, resulting in reduced memory usage. This is particularly important in an embedded environment where memory is usually a constrained resource.

    At a senior C++ conference, the usage of the Flyweight pattern could be presented as an efficient way to manage memory in a system with a large number of objects with shared data. The use of C++20 features like std::shared_ptr for shared ownership and automatic cleanup, and std::mutex for thread safety in the ProtocolFactory class can be highlighted.

    The Flyweight pattern helps with:

        1. Reducing memory usage: By sharing common data among objects, we drastically reduce the memory footprint, especially when there are a large number of objects.

        2. Improving performance: Creating a new object is a costly operation in terms of time and resources. The Flyweight pattern helps to minimize object creation by reusing existing objects.

        3. Encapsulating complexity: The Flyweight pattern abstracts the complexity of object creation and reuse. This makes the client code simpler and easier to manage.

        4. Concurrency: The Flyweight factory uses a mutex to ensure that only one thread can create a protocol at a time, which is especially important in a multithreaded environment.
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <mutex>

class Protocol {
public:
    Protocol(const std::string& name, const std::string& version, const std::string& encryption): 
        name_(name), version_(version), encryption_(encryption) {}

    std::string getName() const { return name_; }
    std::string getVersion() const { return version_; }
    std::string getEncryption() const { return encryption_; }

private:
    std::string name_;
    std::string version_;
    std::string encryption_;
};

class ProtocolFactory {
public:
    std::shared_ptr<Protocol> getProtocol(const std::string& name, const std::string& version, const std::string& encryption) {
        std::lock_guard<std::mutex> lock(mutex_);
        std::string key = name + version + encryption;
        if(auto it = protocols_.find(key); it != protocols_.end()) {
            return it->second;
        }

        auto protocol = std::make_shared<Protocol>(name, version, encryption);
        protocols_[key] = protocol;
        return protocol;
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Protocol>> protocols_;
    std::mutex mutex_;
};

class Session {
public:
    Session(std::shared_ptr<Protocol> protocol, const std::string& sessionId):
        protocol_(protocol), sessionId_(sessionId) {}

    void print() const {
        std::cout << "Session Id: " << sessionId_ << ", Protocol: " << protocol_->getName() << ", Version: " << protocol_->getVersion() << ", Encryption: " << protocol_->getEncryption() << std::endl;
    }

private:
    std::shared_ptr<Protocol> protocol_;
    std::string sessionId_;
};