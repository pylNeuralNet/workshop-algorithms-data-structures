#include <fstream>
#include <iostream>
#include <memory>

class File {
public:
    File(const std::string& filename) : fstream_(filename) { 
        if (!fstream_) {
            throw std::runtime_error("Could not open file");
        }
    }

    ~File() {
        fstream_.close();
    }

    void write(const std::string& text) {
        fstream_ << text;
    }

private:
    std::ofstream fstream_;
};

// Factory function
std::unique_ptr<File> createFile(const std::string& filename) {
    return std::make_unique<File>(filename);
}

int main() {
    try {
        auto file = createFile("test.txt");
        file->write("Hello, World!");
        // File is automatically closed here when `file` goes out of scope
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
    return 0;
}