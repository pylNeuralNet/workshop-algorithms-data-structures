#include <iostream>
#include <vector>
#include <string>
#include <utility> // for std::pair

// A simple log entry structure
struct LogEntry {
    std::string timestamp;
    std::string message;

    // Constructor for easy initialization
    LogEntry(std::string ts, std::string msg) : timestamp(std::move(ts)), message(std::move(msg)) {}
};

class TelecomLog {
private:
    std::vector<LogEntry> logEntries;

public:
    // Constructor is implicitly defined (default constructor).

    // Overloaded subscript operator for accessing log entries by index.
    LogEntry& operator[](size_t index) {
        return logEntries.at(index); // at() checks bounds and throws if out of bounds
    }

    // Overloaded subscript operator for const access to log entries by index.
    const LogEntry& operator[](size_t index) const {
        return logEntries.at(index);
    }

    // Function to add a log entry using rvalue references for efficient string handling.
    void addLogEntry(std::string&& timestamp, std::string&& message) {
        logEntries.emplace_back(std::move(timestamp), std::move(message));
    }

    // Function to get all log entries for structured bindings usage.
    const std::vector<LogEntry>& getLogEntries() const {
        return logEntries;
    }
};

int main() {
    TelecomLog telecomLog;

    // Adding log entries
    telecomLog.addLogEntry("2023-04-01 12:00:00", "User authentication successful.");
    telecomLog.addLogEntry("2023-04-01 12:05:00", "User attempted invalid access.");

    // Demonstrate the subscript operator
    std::cout << "First log entry: [" << telecomLog[0].timestamp << "] " << telecomLog[0].message << std::endl;

    // Demonstrate structured bindings with the log entries
    for (const auto& [timestamp, message] : telecomLog.getLogEntries()) {
        std::cout << "Log entry: [" << timestamp << "] " << message << std::endl;
    }

    return 0;
}