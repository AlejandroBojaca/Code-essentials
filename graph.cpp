#include<iostream>

class ListNode {
    int val;
    ListNode* next;

public:
    ListNode(int value) {
        val = value;
        next = nullptr;
    }
};

class Graph {
    std::vector<ListNode*> graph;
public:

    Graph(int n) {
        graph.resize(n);
        for (auto it : graph) {
            
        }
    }
};
