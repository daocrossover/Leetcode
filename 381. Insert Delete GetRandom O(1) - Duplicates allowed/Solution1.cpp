// 381. Insert Delete GetRandom O(1) - Duplicates allowed
// Description:
// Design a data structure that supports all following operations in average O(1) time.

// Note: Duplicate elements are allowed.
// 1. insert(val): Inserts an item val to the collection.
// 2. remove(val): Removes an item val from the collection if present.
// 3. getRandom: Returns a random element from current collection of elements. 
// The probability of each element being returned is linearly related to the number of same value the collection contains.

// Example:
// Init an empty collection.
// RandomizedCollection collection = new RandomizedCollection();

// Inserts 1 to the collection. Returns true as the collection did not contain 1.
// collection.insert(1);

// Inserts another 1 to the collection. Returns false as the collection contained 1. Collection now contains [1,1].
// collection.insert(1);

// Inserts 2 to the collection, returns true. Collection now contains [1,1,2].
// collection.insert(2);

// getRandom should return 1 with the probability 2/3, and returns 2 with the probability 1/3.
// collection.getRandom();

// Removes 1 from the collection, returns true. Collection now contains [1,2].
// collection.remove(1);

// getRandom should return 1 and 2 both equally likely.
// collection.getRandom();

// Hashmap + Vector Solution:
// Using hashset to store indices

#include <unordered_map>
#include <unordered_set>
#include <vector>
using std::unordered_map;
using std::unordered_set;
using std::vector;

class RandomizedCollection {
public:
    /** Initialize your data structure here. */
    RandomizedCollection() {
        
    }
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        dict[val].insert(data.size());
        data.push_back(val);
        return dict[val].size() == 1;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        if (dict.find(val) == dict.end()) return false;
        int index = *dict[val].begin();
        dict[val].erase(index);
        if (dict[val].empty()) {
            dict.erase(val);
        }
        if (index != data.size() - 1) {
            int end = data.back();
            data[index] = end;
            dict[end].erase(data.size() - 1);
            dict[end].insert(index);
        }
        data.pop_back();
        return true;
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        return data[rand() % data.size()];
    }

private:
    unordered_map<int, unordered_set<int>> dict;
    vector<int> data;
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */

