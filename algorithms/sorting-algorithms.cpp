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

    std::vector<Pair> quickSort(std::vector<Pair>& pairs) {
        if (pairs.size() <= 1) {
            return pairs;
        }
        int left = 0;
        int center = floor(pairs.size() / 2);
        int right = pairs.size() - 1;

        for (auto it : pairs) {
            std::cout << it.key << " ";
        }

        compareSwap(pairs, left, center);
        compareSwap(pairs, center, right);
        compareSwap(pairs, left, center);
        Pair temp = pairs[pairs.size() - 1];
        pairs[pairs.size() - 1] = pairs[center];
        pairs[center] = temp;

        int i = 0;
        int j = pairs.size() - 2;
        int pivot = center;
        while (i > j) {
            while (pairs[i].key < pairs[pairs.size() - 1].key) {
                i++;
            }
            while (pairs[j].key > pairs[0].key) {
                j--;
            }
            if (i < j) {
                Pair temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
            } else {
                if (i != 0) {
                    Pair temp = pairs[i];
                    pairs[i] = pairs[];
                    pairs[j] = temp;
                }
            }
        }

        for (auto it : pairs) {
            std::cout << it.key << " ";
        }

        return pairs;
    }

    std::vector<Pair> compareSwap(std::vector<Pair>& pairs, int left, int right) {
        if (pairs[left].key > pairs[right].key) {
            Pair temp = pairs[right];
            pairs[right] = pairs[left];
            pairs[left] = temp;
        }

        return pairs;
    }
};

int main() {
    SortingAlgorithms sortingAlgorithms;

    std::vector<Pair> pairs;

    pairs.push_back(Pair(3, "3"));
    pairs.push_back(Pair(4, "4"));
    pairs.push_back(Pair(5, "5"));
    pairs.push_back(Pair(9, "9"));
    pairs.push_back(Pair(2, "2"));
    pairs.push_back(Pair(1, "1"));


    sortingAlgorithms.quickSort(pairs);

    return 0;
}
