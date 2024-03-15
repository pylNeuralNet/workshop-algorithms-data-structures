/*
    pylNeuralNet
    2024

    Behavioral Design Pattern
        - Mediator

    This design pattern solves several problems:

        - Encapsulation of complexity: The Mediator encapsulates the complexity of interacting between different subsystems. Therefore, the subsystems do not need to know about each other, which simplifies their implementation and increases their reusability.

        - Concurrency issues: In a multithreaded environment, it's common to have race conditions when multiple threads simultaneously try to write to a shared resource. The Mediator handles this by using a std::mutex to ensure that only one thread can write to the log vector at a time.

        - Ease of maintenance: If we need to change the way we handle logs (e.g., changing the log format or storing logs in a file), we only need to modify the Mediator class. This change does not affect the subsystems, which makes our code easier to maintain.

        - Decoupling: The subsystems are decoupled from one another. They don't need to know about each other's existence or how they are implemented. This is important for code modularity and scalability.
*/
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <condition_variable>

class Mediator
{
public:
    void receive_log(std::string subsystem_name, std::string message)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_logs.push_back(subsystem_name + ": " + message);
    }

    void print_logs()
    {
        for(const auto& log : m_logs)
            std::cout << log << std::endl;
    }

private:
    std::vector<std::string> m_logs;
    std::mutex m_mutex;
};

class Subsystem
{
public:
    Subsystem(Mediator& mediator, std::string name)
        : m_mediator(mediator), m_name(std::move(name)) {}

    void log_message(std::string message)
    {
        m_mediator.receive_log(m_name, std::move(message));
    }

private:
    Mediator& m_mediator;
    std::string m_name;
};

void thread_function(Subsystem& subsystem, std::string message)
{
    subsystem.log_message(std::move(message));
}

int main()
{
    Mediator mediator;

    Subsystem network(mediator, "Network");
    Subsystem storage(mediator, "Storage");

    std::thread t1(thread_function, std::ref(network), "network log");
    std::thread t2(thread_function, std::ref(storage), "storage log");

    t1.join();
    t2.join();

    mediator.print_logs();

    return 0;
}