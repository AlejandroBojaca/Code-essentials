#include <iostream>

class DynamicArray {
private:
    int* arr;
    int size;
    int capacity;
public:

    DynamicArray(int capacity) : capacity(capacity), size(0) {
        arr = new int[capacity];
    }

    int get(int i) {
        return arr[i];
    }

    void set(int i, int n) {
        arr[i] = n;
    }

    void pushback(int n) {
        if (capacity == size) {
            resize();
        }
        arr[size] = n;
        size++;
    }

    int popback() {
        if (size > 0) {
            size--;
        }
        return arr[size];
    }

    void resize() {
        capacity *= 2;
        int* newArr = new int[capacity];
        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }

    int getSize() {
        return size;
    }

    int getCapacity() {
        return capacity;
    }
};


int main() {
    // Test 1: Create a DynamicArray with initial capacity 2
    DynamicArray da(2);

    // Test 2: Check initial size and capacity
    std::cout << "Initial size: " << da.getSize() << std::endl; // Expected: 0
    std::cout << "Initial capacity: " << da.getCapacity() << std::endl; // Expected: 2

    // Test 3: Push back elements and check size
    da.pushback(10);
    da.pushback(20);
    da.pushback(30); // Resize should happen here
    std::cout << "Size after pushback: " << da.getSize() << std::endl; // Expected: 3

    // Test 4: Get and set elements
    std::cout << "Element at index 0: " << da.get(0) << std::endl; // Expected: 10
    da.set(1, 25);
    std::cout << "Element at index 1: " << da.get(1) << std::endl; // Expected: 25

    // Test 5: Pop back and check size
    int popped = da.popback();
    std::cout << "Popped element: " << popped << std::endl; // Expected: 30
    std::cout << "Size after popback: " << da.getSize() << std::endl; // Expected: 2

    // Test 6: Check capacity after resize
    da.pushback(40);
    std::cout << "Capacity after resize: " << da.getCapacity() << std::endl; // Expected: 4

    // Test 7: Try out-of-bounds access
    da.get(-1); // Should print "Index out of bounds"
    da.set(3, 50); // Should print "Index out of bounds"

    // Test 8: Pop from empty array
    da.popback();
    da.popback();
    da.popback(); // Should print "Array is empty"

    return 0;
}