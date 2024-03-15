/*
    pylNeuralNet
    2024

    Explanation:

    In this example, SensorData is the subject that maintains a list of observers. When sensor data changes, it notifies all registered observers using the notify method. Observers implement the IObserver interface and are notified with the update method.

    Logger, Display, and NetworkManager are concrete observer classes that perform specific actions when notified of a change in sensor data.

    C++ Problems Solved:

        1. Decoupling: The Observer pattern decouples the state-holding subject from its observers, enabling independent extensibility. This is particularly useful in embedded systems where modules may be added or removed depending on the configuration or requirements.
        2. Notification Mechanism: The Observer pattern provides a standardized way to handle notifications. This is beneficial in a multithreaded environment where sensor data changes could occur at any time and need to be communicated to multiple subsystems efficiently.
        3. Thread Safety: The use of std::mutex ensures that the subject's state changes and the corresponding notifications to observers are thread-safe. This prevents race conditions and data corruption, which are critical concerns in a multithreaded embedded system.
        4. Resource Management: By using std::shared_ptr for observer management, the pattern integrates well with the RAII paradigm, ensuring that resources are managed correctly and that memory leaks are avoided.
*/


#include <iostream>
#include <vector>
#include <memory>
#include <mutex>

// Observer interface
class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void update(const std::string& message) = 0;
};

// Subject interface
class ISubject {
public:
    virtual ~ISubject() = default;
    virtual void attach(std::shared_ptr<IObserver> observer) = 0;
    virtual void detach(std::shared_ptr<IObserver> observer) = 0;
    virtual void notify() = 0;
};

// Concrete subject that holds state and notifies observers upon changes
class SensorData : public ISubject {
private:
    std::vector<std::shared_ptr<IObserver>> observers;
    std::string message;
    std::mutex mtx;

public:
    void attach(std::shared_ptr<IObserver> observer) override {
        std::lock_guard<std::mutex> lock(mtx);
        observers.push_back(observer);
    }

    void detach(std::shared_ptr<IObserver> observer) override {
        std::lock_guard<std::mutex> lock(mtx);
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify() override {
        std::lock_guard<std::mutex> lock(mtx);
        for (const auto& observer : observers) {
            observer->update(message);
        }
    }

    void setSensorData(const std::string& newMessage) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            message = newMessage;
        }
        notify(); // Notify observers of the change
    }
};

// Concrete observer classes
class Logger : public IObserver {
public:
    void update(const std::string& message) override {
        std::cout << "Logger: " << message << std::endl;
        // Additional logging logic could go here
    }
};

class Display : public IObserver {
public:
    void update(const std::string& message) override {
        std::cout << "Display: " << message << std::endl;
        // Additional display update logic could go here
    }
};

class NetworkManager : public IObserver {
public:
    void update(const std::string& message) override {
        std::cout << "NetworkManager: " << message << std::endl;
        // Additional network transmission logic could go here
    }
};

int main() {
    auto sensorData = std::make_shared<SensorData>();
    auto logger = std::make_shared<Logger>();
    auto display = std::make_shared<Display>();
    auto networkManager = std::make_shared<NetworkManager>();

    sensorData->attach(logger);
    sensorData->attach(display);
    sensorData->attach(networkManager);

    // Simulate sensor data changes
    sensorData->setSensorData("Heart rate: 80 bpm");
    sensorData->setSensorData("Blood pressure: 120/80 mmHg");

    // Detach logger, it will no longer receive updates
    sensorData->detach(logger);

    // Simulate another sensor data change
    sensorData->setSensorData("Oxygen saturation: 98%");

    return 0;
}