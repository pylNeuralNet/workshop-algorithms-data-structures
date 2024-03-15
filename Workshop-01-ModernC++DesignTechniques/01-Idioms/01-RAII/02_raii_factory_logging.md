1. RAII (Resource Acquisition Is Initialization): RAII is a programming idiom used in C++ where the lifetime of an object is tied to the ownership of resources, such as memory allocation, file handles, etc.

Example: In the FileLogger class, the file resource is acquired in the constructor and released in the destructor, which is implicitly called when the object goes out of scope or is deleted.
```C++
FileLogger(const std::string& filename) : fstream_(filename) { 
    if (!fstream_) {
        throw std::runtime_error("Could not open file");
    }
}
```

2. Factory Design Pattern: The Factory Design Pattern provides a way to encapsulate the instantiation of concrete types.

Example: The createLogger function is a factory function that creates and returns a LoggerBase object based on the type string.

```C++
std::unique_ptr<LoggerBase> createLogger(const std::string& type, const std::string& name) {
    if (type == "file") {
        return std::make_unique<FileLogger>(name);
    }
    throw std::runtime_error("Invalid logger type");
}
```

3. Polymorphism: Polymorphism is a feature of object-oriented programming languages that allows methods to be used in the same general way even if they behave differently.

Example: The LoggerBase class has a virtual function write that is overridden by the FileLogger class. This allows different types of loggers to be used in the same way.

```C++
class LoggerBase {
public:
    virtual void write(const std::string& text) = 0;  // pure virtual function
};

class FileLogger : public LoggerBase {
public:
    void write(const std::string& text) override {
        std::lock_guard<std::mutex> lock(mutex_);
        fstream_ << text;
    }
};
```

4. Multithreading: Multithreading is a feature that allows concurrent execution of two or more parts of a program for maximum utilization of CPU.

Example: The write function in the FileLogger class is thread-safe because it locks a mutex before writing to the file.

```C++
void write(const std::string& text) override {
    std::lock_guard<std::mutex> lock(mutex_);
    fstream_ << text;
}
```

5. Exception Handling: Exception handling is a feature that is used for handling the runtime errors so that the normal flow of the program can be maintained.

Example: If the fstream_ constructor or the createLogger function encounters an error, they throw an exception, which can be caught and handled by the caller.

```C++
if (!fstream_) {
    throw std::runtime_error("Could not open file");
}
// ...
throw std::runtime_error("Invalid logger type");
```
