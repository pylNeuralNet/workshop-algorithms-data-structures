#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <initializer_list>

class PriorityTaskMap {
private:
    std::map<int, std::vector<std::string>> tasks;

public:
    // Constructor that allows initializing with a list of priorities and their tasks.
    PriorityTaskMap(std::initializer_list<std::pair<const int, std::vector<std::string>>> il) : tasks(il) {}

    // Overloaded subscript operator to access or create a task list for a given priority.
    std::vector<std::string>& operator[](int priority) {
        // This will create an empty vector for the priority if it does not exist.
        return tasks[priority];
    }

    // Function to print all tasks organized by priority.
    void printTasks() const {
        for (const auto& [priority, taskList] : tasks) {
            std::cout << "Priority " << priority << ":" << std::endl;
            for (const auto& task : taskList) {
                std::cout << "  - " << task << std::endl;
            }
        }
    }
};

int main() {
    // Initialize with some tasks
    PriorityTaskMap taskMap{
        {1, {"Critical bug fix", "System update"}},
        {2, {"Develop new feature", "Code review"}}
    };

    // Add a task to an existing priority
    taskMap[1].push_back("Security patch");

    // Add a task to a new priority (which will be created)
    taskMap[3].push_back("Write documentation");

    // Print all tasks
    taskMap.printTasks();

    return 0;
}