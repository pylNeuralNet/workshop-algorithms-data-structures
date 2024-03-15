#include <map>
#include <iostream>
#include <mutex>
#include <functional>
#include <vector>

template<typename K, typename V>
class IntervalMap {
private:
    std::map<K, V> intervals;
    std::mutex intervalsMutex; // Mutex to protect the map for thread-safety

    using MergeStrategy = std::function<bool(const V&, const V&)>;
    MergeStrategy mergeStrategy; // Strategy Pattern for merging intervals

    // Observer Pattern
    std::vector<std::function<void(const K&, const K&, const V&)>> observers;

public:
    IntervalMap(MergeStrategy strategy) : mergeStrategy(strategy) {}

    void addObserver(std::function<void(const K&, const K&, const V&)> observer) {
        observers.push_back(observer);
    }

    void notifyObservers(const K& start, const K& end, const V& value) {
        for (auto& observer : observers) {
            observer(start, end, value);
        }
    }

    void set(const K& start, const K& end, const V& value) {
        std::unique_lock<std::mutex> lock(intervalsMutex);
        // Implementation with merge strategy...
        // Notify observers after the interval is set
        notifyObservers(start, end, value);
    }

    V get(const K& key) {
        std::unique_lock<std::mutex> lock(intervalsMutex);
        // Implementation...
    }
};

// Use case example
int main() {
    // Define merge strategy for intervals with the same value
    auto mergeSameValue = [](const char& a, const char& b) -> bool {
        return a == b;
    };

    IntervalMap<int, char> imap(mergeSameValue);

    // Add observer for logging
    imap.addObserver([](const int& start, const int& end, const char& value) {
        std::cout << "Interval [" << start << ", " << end << ") set to '" << value << "'\n";
    });

    imap.set(1, 5, 'A');
    imap.set(6, 10, 'B');

    return 0;
}