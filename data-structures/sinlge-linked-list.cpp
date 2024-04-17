
#include <iostream>
#include <vector>

class ListNode {
public:
    int val;
    ListNode* next;    

    ListNode(int val) : val(val), next(nullptr) {}
    ListNode(int val, ListNode* next) : val(val), next(next) {}
};

class LinkedList {
    ListNode* head;
    ListNode* tail;
public:
    LinkedList() {
        head = new ListNode(-1);
        tail = head;
    }

    int get(int index) {
        ListNode* curr = head->next;
        for (int i = 0; i < index && curr != nullptr; i++) {
            curr = curr->next;
        }
        if (curr == nullptr) {
            return -1;
        }
        return curr->val;
    }

    void insertHead(int val) {
        ListNode* newNode = new ListNode(val);
        newNode->next = head->next;
        head->next = newNode;
        if (newNode->next == nullptr) {
            tail = newNode;
        }
    }
    
    void insertTail(int val) {
        tail->next = new ListNode(val);
        tail = tail->next;
    }

    bool remove(int index) {
        ListNode* curr = head;
        for (int i = 0; i < index && curr != nullptr; i++) {
            curr = curr->next;
        }
        if (curr != nullptr && curr->next != nullptr) {
            if (curr->next == tail) {
                tail = curr;
            }
            ListNode* toDelete = curr->next;
            curr->next = curr->next->next;
            delete toDelete;
            return true;
        }
        return false;
    }

    std::vector<int> getValues() {
        ListNode* curr = head->next;
        std::vector<int> result;
        while (curr != nullptr) {
            result.push_back(curr->val);
            curr = curr->next;
        }
        return result;
    }
};

int main() {
    LinkedList list;

    // Test insertHead
    list.insertHead(3);
    list.insertHead(2);
    list.insertHead(1);

    // Test getValues
    std::vector<int> values = list.getValues();
    std::cout << "Values after insertHead: ";
    for (int val : values) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Test get
    std::cout << "Value at index 1: " << list.get(1) << std::endl;

    // Test insertTail
    list.insertTail(4);
    list.insertTail(5);
    values = list.getValues();
    std::cout << "Values after insertTail: ";
    for (int val : values) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Test remove
    list.remove(2);
    values = list.getValues();
    std::cout << "Values after remove: ";
    for (int val : values) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}