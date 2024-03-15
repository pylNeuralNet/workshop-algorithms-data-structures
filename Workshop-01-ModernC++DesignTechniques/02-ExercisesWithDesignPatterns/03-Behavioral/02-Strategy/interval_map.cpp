#include <map>
#include <iostream>

template<typename K, typename V>
class IntervalMap {
private:
    std::map<K, V> intervals;

public:
    void set(const K& start, const K& end, const V& value) {
        if (start >= end) {
            return; // Invalid interval, return or throw an exception.
        }

        // Simplified logic for setting intervals:
        // - Overwrite intervals that are fully contained within the new interval
        // - Adjust the start and end of overlapping intervals
        auto itLow = intervals.lower_bound(start);
        auto itHigh = intervals.upper_bound(end);

        // Erase fully contained intervals
        intervals.erase(itLow, itHigh);

        // Insert the new interval
        intervals[start] = value;

        // If necessary, adjust the end of the previous interval
        if (itLow != intervals.begin() && std::prev(itLow)->second == value) {
            auto itPrev = std::prev(itLow);
            intervals.erase(itPrev);
            intervals[start] = value;
        }

        // If necessary, adjust the start of the following interval
        if (itHigh != intervals.end() && itHigh->second == value) {
            intervals[end] = itHigh->second;
        }
    }

    V get(const K& key) const {
        auto it = intervals.upper_bound(key);
        if (it == intervals.begin()) {
            throw std::out_of_range("Key is below the first interval.");
        }
        --it;
        return it->second;
    }

    void print() const {
        for (const auto& interval : intervals) {
            std::cout << "[" << interval.first << "): " << interval.second << "\n";
        }
    }
};

int main() {
    IntervalMap<int, char> imap;
    imap.set(1, 5, 'A');
    imap.set(6, 10, 'B');
    imap.print();
    std::cout << "Get 3: " << imap.get(3) << std::endl;
    std::cout << "Get 7: " << imap.get(7) << std::endl;

    // Overlapping intervals
    imap.set(4, 8, 'C');
    imap.print();

    return 0;
}