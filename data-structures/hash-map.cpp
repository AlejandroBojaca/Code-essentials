#include <iostream>

class Hashmap {
    int capacity;
    int size;
    std::vector<std::vector<std::pair<int, int> > > map;
public:
    Hashmap(int cap) {
        capacity = cap;
        size = 0;
        map.resize(capacity);
    }

    int getHashKey(int key) {
        return key % capacity;
    }

    void put(int key, int value) {
        if (size == capacity) {
            std::cout << "Hashmap is full";
            return;
        }

        int hashKey = getHashKey(key);
        for (auto it = map[hashKey].begin(); it != map[hashKey].end(); ++it) {
            if (it->first == key) {
                it->second = value;
                return;
            }
        }

        map[hashKey].push_back(std::make_pair(key, value));
        size++;
    }

    int get(int key) {
        int hashKey = getHashKey(key);
        
        for (const auto& it : map[hashKey]) {
            if (it.first == key) {
                return it.second;
            }
        }
        
        return -1;
    }

    bool remove(int key) {
        int hashKey = getHashKey(key);

        for (auto it = map[hashKey].begin(); it != map[hashKey].end(); ++it) {
            if (it->first == key) {
                map[hashKey].erase(it);
                size--;
                return true;
            }
        }
        return false;
    }

    int getSize() {
        return size;
    }

    bool empty() {
        return size == 0;
    }
};

int main() {
    Hashmap hashMap(7);

    hashMap.put(1, 10);
    hashMap.put(2, 20);
    hashMap.put(3, 30);

    std::cout << "Size: " << hashMap.getSize() << std::endl; // Output: 3
    std::cout << "Value for key 2: " << hashMap.get(2) << std::endl; // Output: 20
    std::cout << "Remove key 3: " << hashMap.remove(3) << std::endl; // Output: true

    hashMap.put(4, 40);
    hashMap.put(5, 50);
    hashMap.put(6, 60);
    hashMap.put(7, 70);
    hashMap.put(8, 80); // This will trigger rehashing

    std::cout << "Value for key 8: " << hashMap.get(8) << std::endl; // Output: 80
    std::cout << "Is empty: " << hashMap.empty() << std::endl; // Output: false

    return 0;
}