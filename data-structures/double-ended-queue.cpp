#include <iostream>

struct DoubleListNode {
    int val;
    DoubleListNode* next;
    DoubleListNode* prev;

    DoubleListNode(int value) {
        val = value;
        next = nullptr;
        prev = nullptr;
    }
};

class Deque {
    DoubleListNode* front;
    DoubleListNode* rear;
    int size;
public:
    Deque () {
        front = nullptr;
        rear = nullptr;
        size = 0;
    }

    void pushFront (int val) {
        DoubleListNode* newNode = new DoubleListNode(val);
        if (front == nullptr && rear != nullptr) {
            rear->prev = newNode;
        } else if (front != nullptr && rear != nullptr) {
            front->prev = newNode;
        }
        newNode->next = front;
        front = newNode;
        size ++;
    }

    void pushRear (int val) {
        DoubleListNode* newNode = new DoubleListNode(val);
        if (rear == nullptr && front != nullptr) {
            front->next = newNode;
        } else if (rear != nullptr && rear != nullptr) {
            rear->next = newNode;
        }
        newNode->prev = rear;
        rear = newNode;
        size++;
    }

    int popFront () {
        DoubleListNode* tmp = front;
        int val = -1;
        if (front != nullptr) {
            val = front->val;
            tmp = front->next;
        }
        front = tmp;
        if (front == nullptr) {
            rear = front;
        }
        size--;
        return val;
    }

    int popRear () {
        DoubleListNode* tmp = rear;
        int val = -1;
        if (rear != nullptr) {
            val = rear->val;
            tmp = rear->prev;
        }
        rear = tmp;
        if (rear == nullptr) {
            front = rear;
        }
        size--;
        return val;
    }

    int getFront () {
        return front != nullptr ? front->val : -1;
    }

    int getRear () {
        return rear != nullptr ? rear->val : -1;
    }

    int getSize () {
        return size;
    }

    bool isEmpty () {
        return (front == nullptr && rear == nullptr);
    }
};

int main() {
    Deque deque;
    deque.pushFront(1);
    deque.pushRear(2);
    std::cout << deque.getFront() << std::endl; // Output: 1
    std::cout << deque.getRear() << std::endl; // Output: 2
    
    deque.pushFront(2);
    deque.pushRear(3);
    
    std::cout << deque.getFront() << std::endl; // Output: 2
    std::cout << deque.getRear() << std::endl; // Output: 3

    deque.pushFront(3);
    deque.pushRear(4);
    std::cout << deque.popFront() << std::endl; // Output: 3
    std::cout << deque.popRear() << std::endl; // Output: 4

    std::cout << deque.getFront() << std::endl; // Output: 2
    std::cout << deque.getRear() << std::endl; // Output: 3

    std::cout << deque.popFront() << std::endl; // Output: 2
    std::cout << deque.popRear() << std::endl; // Output: 3

    std::cout << deque.getFront() << std::endl; // Output: 1
    std::cout << deque.getRear() << std::endl; // Output: 2

    std::cout << deque.popFront() << std::endl; // Output: 1
    std::cout << deque.popRear() << std::endl; // Output: 2

    std::cout << deque.getFront() << std::endl; // Output: 2
    std::cout << deque.getRear() << std::endl; // Output: 2

    std::cout << "empty: " << deque.isEmpty() << std::endl; // Output: 0 (false)
    std::cout << "size: " << deque.getSize() << std::endl; // Output 4
    return 0;
}