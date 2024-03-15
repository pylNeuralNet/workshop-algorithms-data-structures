## Multimap vs Set
Both multiset and map are associative containers provided by the C++ Standard Library, and both are usually implemented as balanced binary search trees (like red-black trees). However, they serve different purposes and have some key differences:

### std::multiset

A multiset is a collection of ordered elements, and multiple elements can have equivalent values.
It is designed to store a sorted set of elements. Elements are sorted according to a specified comparison function (less-than by default).
In a multiset, the value of an element is also the key used for ordering.
All operations on a multiset (insertion, deletion, search) have logarithmic complexity in the size of the container.
It is mainly used for cases where you need to store multiple elements that can be the same, and you want them to be automatically sorted.
Example usage of a multiset:

```C++
std::multiset<int> mset = {1, 2, 3, 3, 4}; // 3 appears twice
```

### std::map

A map stores key-value pairs, where each key is unique, and keys are sorted according to a specified comparison function (less-than by default).
The key is used for sorting and indexing the data, and the value is the data associated with that key.
It is mainly used for associative array-like access where each key maps to a value.
All operations on a map (insertion, deletion, lookup) also have logarithmic complexity in the size of the container.
Example usage of a map:

```C++
std::map<int, std::string> mp = {{1, "one"}, {2, "two"}, {3, "three"}};
```

### Comparison

Purpose: multiset is for storing sorted elements which can have duplicates, whereas map is for storing unique keys each associated with a value.
Content: multiset contains only one type of value (which acts as the key), while map contains pairs of keys and values.
Uniqueness: multiset allows multiple equivalent elements, but map requires keys to be unique.
Usage: Use multiset when you only need ordered elements and duplicates are acceptable. Use map when you need to associate unique keys with values.
Access: You cannot directly modify the elements in a multiset because it would potentially alter the container's ordering. Any modification requires removal and re-insertion with the new value. In a map, you can modify the value part of a key-value pair directly through its unique key.

Both containers have their specific use cases, and the choice between them depends on your particular needs regarding data storage, access patterns, and operations you need to perform on the data.

## multimap_sibscribe_notify_async.cpp
```C++
std::map<SubscriberId, std::set<PacketType>> subscriberPreferences;
std::set<PacketType> packetTypesInterestedIn = subscriberPreferences[subscriberId];
std::multimap<PacketType, SubscriberId> packetTypeSubscribers;
```

## k most frequent

### std::multiset
```C++
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // Count the frequency of each number using a hash table
        unordered_map<int, int> frequencyMap;
        for (int num : nums) {
            frequencyMap[num]++;
        }

        // Custom comparator for sorting the pairs by frequency in descending order
        auto comp = [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second > b.second || (a.second == b.second && a.first < b.first);
        };

        // Define a multiset with the custom comparator
        multiset<pair<int, int>, decltype(comp)> sortedByFreq(comp);

        // Insert all elements and their frequencies into the multiset
        for (const auto& [num, freq] : frequencyMap) {
            sortedByFreq.emplace(num, freq);
        }

        // Extract the top k frequent elements from the multiset
        vector<int> topK;
        auto it = sortedByFreq.begin();
        while (k > 0 && it != sortedByFreq.end()) {
            topK.push_back(it->first);
            ++it;
            --k;
        }

        return topK;
    }
};
```

### std::multimap

https://leetcode.com/problems/top-k-frequent-elements/solutions/2976091/easy-to-understand-solution-map-multimap/
```C++
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k)
    {
        map<int,int>mp;
        vector<int>v;
        for(int i=0; i<nums.size(); i++)
        {
            mp[nums[i]]++;
        }
        multimap<int,int>mp1;
        for(auto it:mp)
        {
            mp1.insert({it.second,it.first});
        }
        for(auto it=mp1.rbegin();it!=mp1.rend();it++)
        {
            if(k>0)
            {
                v.push_back(it->second);
                k--;
            }
        }
        return v;
    }
};
```

### std::map, std::make_pair, std::vector

```C++

https://leetcode.com/problems/top-k-frequent-elements/solutions/4789656/beats-100-of-users-with-c-using-vector-using-map-using-pair-step-by-step-explain/
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k)
    {
        vector<int>ans;
        map<int,int>mp;
        for(int i=0;i<nums.size();i++)
            mp[nums[i]]++;
        vector<pair<int,int>>v;
        for(auto it : mp )
            v.push_back(make_pair(it.second,it.first));
        sort(v.rbegin(),v.rend());
        for(int i=0;i<v.size() && k!=0 ;i++)
        {
            ans.push_back(v[i].second);
            k--;
        }
        return ans;
    }
};
```