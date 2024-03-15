 #include <iostream>

class Resource {
public:
    Resource();
    ~Resource();
    void update();
    int getValue() const; // Method to confirm the state change

private:
    struct Impl; // Forward declaration of the implementation
    Impl* pImpl; // Pointer to the implementation
};

/** Source file */
struct Resource::Impl {
    int value;

    void update() {
        value++;
    }
};

Resource::Resource() : pImpl(new Impl{0}) {}

Resource::~Resource() {
    delete pImpl;
}

void Resource::update() {
    pImpl->update();
}

int Resource::getValue() const {
    return pImpl->value;
}

// Inline function defined in the header
inline void problematicUpdate(int& resource) {
    resource++;
    /** 
     * Issues with this inline function:
     * 1. ABI Stability: If the implementation changes, all clients must recompile.
     * 2. Hidden Dependencies: Changes in the function force recompilation of all sources including this header.
     * 3. Code Bloat: The function body is duplicated at each call site, increasing binary size.
     */
}

int main() {
    Resource res;
    res.update(); // Update the resource using the pImpl idiom

    // Confirm the state change
    std::cout << "Resource value after update: " << res.getValue() << std::endl;

    // Using the inline function
    int inlineResource = 0;
    problematicUpdate(inlineResource); // Potential issue if the inline function changes
    std::cout << "Inline resource value after update: " << inlineResource << std::endl;

    return 0;
}
