#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>

// LoggerBase (base class)
class LoggerBase {
public:
    virtual void write(const std::string& text) = 0;  // pure virtual function
};

// FileLogger (derived class)
class FileLogger : public LoggerBase {
public:
    FileLogger(const std::string& filename) : fstream_(filename) { 
        if (!fstream_) {
            throw std::runtime_error("Could not open file");
        }
    }

    void write(const std::string& text) override {
        std::lock_guard<std::mutex> lock(mutex_);
        fstream_ << text;
    }

private:
    std::ofstream fstream_;
    std::mutex mutex_;
};

// Factory function
std::unique_ptr<LoggerBase> createLogger(const std::string& type, const std::string& name) {
    if (type == "file") {
        return std::make_unique<FileLogger>(name);
    }
    throw std::runtime_error("Invalid logger type");
}

int main() {
    try {
        auto logger = createLogger("file", "test.txt");
        logger->write("Hello, World!");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
    return 0;
}