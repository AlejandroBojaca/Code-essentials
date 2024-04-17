#include <iostream>
#include <cmath>

class Pair {
public:
    int key;
    std::string value;

    Pair(int key, std::string value) : key(key), value(value) {}
};

class SortingAlgorithms {
public:
    std::vector<std::vector<Pair>> insertionSort(std::vector<Pair>& pairs) {
        std::vector<std::vector<Pair>> result;
        int length = pairs.size();
        for (int i = 0; i < length; i++) {
            int j = i;
            while (j > 0) {
                if (pairs[j - 1].key > pairs[j].key) {
                    Pair prev = pairs[j - 1];
                    pairs[j - 1] = pairs[j];
                    pairs[j] = prev;
                }
                j--;
            }
            
            result.push_back(pairs);
        }
        return result;
    }

    std::vector<Pair> merge(std::vector<Pair>& firstPairs, std::vector<Pair>& secondPairs) {
        int i = 0, j = 0;
        std::vector<Pair> result;

        while (i != firstPairs.size() && j != secondPairs.size()) {
            if (firstPairs[i].key < secondPairs[j].key) {
                result.push_back(firstPairs[i]);
                i++;
            } else {
                result.push_back(firstPairs[j]);
                j++;
            }
        }

        while (i != firstPairs.size()) {
            result.push_back(firstPairs[i]);
            i++;
        }

        while (j != secondPairs.size()) {
            result.push_back(secondPairs[j]);
            j++;
        }

        return result;
    }

    std::vector<Pair> mergeSort(std::vector<Pair>& pairs) {
        if (pairs.size() <= 1) {
            return pairs;
        }
        int middlePoint = floor(pairs.size() / 2);
        std::vector<Pair> left(pairs.begin(), pairs.begin() + middlePoint);
        std::vector<Pair> right(pairs.begin() + middlePoint + 1, pairs.end());

        mergeSort(left);
        mergeSort(right);

        return merge(left, right);
    }
};

int main() {


    return 0;
}
