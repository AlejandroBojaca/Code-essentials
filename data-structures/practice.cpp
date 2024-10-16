#include <iostream>
#include <queue>
#include <ctime> // For time() to seed srand()
#include <cstdlib> // For rand() and srand()
#include <random> 
using namespace std;

//Linked lists
struct Node {
    Node* next;
    int value;

    Node(int value) {
        this->value = value; 
        this->next = NULL;
    }
};

struct LinkedList {
    Node* head;
    Node* tail;

    LinkedList() {
        this->head = NULL;
        this->tail = NULL;
    }

    bool add_head(int value) {
        Node* new_node = new Node(value);

        if (this->head == NULL) {
            this->head = new_node;
            this->tail = new_node;
            return true;
        }

        new_node->next = this->head;
        this->head = new_node;

        return true;
    }

    bool add_tail(int value) {
        Node* new_node = new Node(value);
        
        if (this->head == NULL) {
            this->head = new_node;
            this->tail = new_node;
            return true;
        }
       
        this->tail->next = new_node;
        this->tail = new_node;
        return true;
    }

    bool add_middle(int after_value, int value) {
        if (this->head == NULL) {
            this->head = new Node(value);
            return true;
        }

        Node* traversal = this->head;
        while (traversal != NULL && traversal->value != after_value) {
            traversal = traversal->next;
        }

        if (traversal != NULL) {
            Node * new_node = new Node(value);
            new_node->next = traversal->next;
            traversal->next = new_node;
            return true;
        }

        return false;
    }

    bool delete_head() {
        if (this->head == NULL) {
            return false;
        }
        if (this->head == this->tail) {
            Node* tmp = this->head;
            this->head = NULL;
            this->tail = NULL;
            delete tmp;
            return true;
        }
        Node* tmp = this->head;
        this->head = this->head->next;
        delete tmp;
        return true;
    }

    bool delete_tail() {
        if (this->head == NULL) {
            return false;
        }
        if (this->head == this->tail) {
            Node* tmp = this->head;
            this->head = NULL;
            this->tail = NULL;
            delete tmp;
            return true;
        }
        Node* tmp = this->tail;
        Node* prev = this->head;
        Node* traversal = this->head;
        while (traversal->next != NULL) {
            prev = traversal;
            traversal = traversal->next;
        }
        this->tail = prev;
        prev->next = NULL;
        delete tmp;
        return true;
    }

    bool delete_middle(int value) {
        if (this->head == NULL) {
            return false;
        }

        if (this->head->value == value) {
            Node* tmp = this->head;
            this->head = this->head->next;
            if (tmp == this->tail) {
                this->tail = NULL;
            }
            delete tmp;
            return true;
        }

        Node* traversal = this->head;
        Node* prev = NULL;
        while (traversal != NULL && traversal->value != value) {
            prev = traversal;
            traversal = traversal->next;
        }

        if (traversal != NULL) {
            prev->next = traversal->next;
            delete traversal;
            return true;
        }

        return false;
    }

    void print_list() {
        Node* traversal = this->head;
        while (traversal != NULL) {
            cout << "(value: " << traversal->value << "  adress: " << traversal << "  next: " << traversal->next << ")  ->  ";
            traversal = traversal->next;
        }
    }

    ~LinkedList() {
        Node* traversal = head;
        while (traversal != NULL) {
            Node* temp = traversal;
            traversal = traversal->next;
            delete temp;
        }   
    }
};

// Binary Tree
struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) {
        this->value = value;
        this->left = NULL;
        this->right = NULL;
    }
};

struct BinarySearchTree {
    TreeNode* root;
    int size;

    BinarySearchTree(int value) {
        root = new TreeNode(value);
        size = 1;
    }

    bool insert_node(int value) {
        TreeNode* new_node = new TreeNode(value);
        if (this->root == nullptr) {
            this->root = new_node;
            return true;
        }

        bool inserted = insert_node_r(this->root, value);
        if (inserted ) this->size += 1;
        return inserted;
    }

    bool insert_node_r(TreeNode* node, int value) {
        if (value == node->value) {
            return false;
        }

        if (value < node->value) {
            if (node->left == nullptr) {
                node->left = new TreeNode(value);
                return true;
            } else {
                return insert_node_r(node->left, value);
            }
        } else {
            if (node->right == nullptr) {
                node->right = new TreeNode(value);
                return true;
            } else {
                return insert_node_r(node->right, value);
            }
        }
    }

    void depth_first_search() {
        cout << "Depth first search: ";
        depth_first_search_r(this->root);
        cout << endl;
    }

    void depth_first_search_r(TreeNode* node) {
        if (node != NULL) {
            depth_first_search_r(node->left);
            cout << node->value << " ";
            depth_first_search_r(node->right);
        }
    }

    void breadth_first_search() {
        cout << "Breadth first search: ";
        breadth_first_search_r(this->root);
        cout << endl;
    }

    void breadth_first_search_r(TreeNode* node) {
        if (this->root == NULL) return;

        queue<TreeNode*> q;
        q.push(node);

        while(!q.empty()) {
            TreeNode* node = q.front();
            q.pop();

            cout << node->value << " ";
            
            if (node->left != NULL) {
                q.push(node->left);
            }
            if (node->right != NULL) {
                q.push(node->right);
            }
        }
    }

    TreeNode* find_min() {
        return find_min_r(this->root);
    }

    TreeNode* find_min_r(TreeNode* node) {
        if (this->root == NULL) {
            return NULL;
        }
        while (node->left != NULL) {
            node = node->left;
        }
        return node;
    }

    TreeNode* find_max() {
        return find_max_r(this->root);
    }

    TreeNode* find_max_r(TreeNode* node) {
        if (this->root == NULL) {
            return NULL;
        }
        while (node->right != NULL) {
            node = node->right;
        }
        return node;
    }

    int get_size() {
        return this->size;
    }

    int get_level(TreeNode* node, int value, int level) {
        if (node == nullptr) {
            return -1;
        }

        if (node->value == value) {
            return level;
        }

        if (value < node->value) {
            return get_level(node->left, value, level + 1);
        }

        return get_level(node->right, value, level + 1);
    }

    int get_level(int value) {
        return get_level(this->root, value, 0);
    }

    bool delete_node(int value) {
        cout << "Deleting node: " << value << endl;
        delete_node_r(this->root, value);
        return true;
    }

    TreeNode* delete_node_r(TreeNode* node, int value) {
        if (node == NULL) return node;
        if (node->value < value) {
            node->left = delete_node_r(node->left, value);
        }
        if (node->value > value) {
            node->right = delete_node_r(node->right, value);
        } else {
            if (node->right == NULL && node->left == NULL) {
                delete node;
                return NULL;
            }

            if (node->right == NULL) {
                TreeNode* next_node = node->left;
                delete node;
                return next_node;
            }

            if (node->left == NULL) {
                TreeNode* next_node = node->right;
                delete node;
                return next_node;
            }

            TreeNode* sucessor_node = find_min_r(node->right);
            node->value = sucessor_node->value;
            node->right = delete_node_r(node->right, sucessor_node->value);
        }
        return node;
    }
};

//insertion sort
void insertion_sort(int array[], int size) {
    for (int i = 1; i < size; i++) {
        for (int j = i; j > 0 && array[j] < array[j - 1]; j-- ) {
            int tmp = array[j];
            array[j] = array[j - 1];
            array[j - 1] = tmp;
        }
    }
}


//merge sort
void merge(int array[], int start, int mid, int end) {
    int left_size = mid - start + 1;
    int right_size = end - mid;

    int* left_array = new int[left_size];
    int* right_array = new int[right_size];

    for (int i = 0; i < left_size; i++) {
        left_array[i] = array[start + i];
    }
    for (int i = 0; i < right_size; i++) {
        right_array[i] = array[mid + 1 + i];
    }

    int i = 0, j = 0, k = start;
    while (i < left_size && j < right_size) {
        if (left_array[i] <= right_array[j]) {
            array[k] = left_array[i];
            i++;
        } else {
            array[k] = right_array[j];
            j++;
        }
        k++;
    }

    while (i < left_size) {
        array[k] = left_array[i];
        i++;
        k++;
    }

    while (j < right_size) {
        array[k] = right_array[j];
        j++;
        k++;
    }

    delete[] left_array;
    delete[] right_array;
}

void merge_sort(int array[], int start, int end) {
    if (start < end) {
        int mid = (start + end) / 2;

        merge_sort(array, start, mid);
        merge_sort(array, mid + 1, end);

        merge(array, start, mid, end);
    }
}

//quick sort
int partition(int array[], int low, int high) {
    int pivot = array[high];
    int last_index = low;

    for (int i = low; i <= high - 1; i ++) {
        if (array[i] < pivot) {
            swap(array[last_index], array[i]);
            last_index ++;
        }
    }

    swap(array[last_index], array[high]);
    return last_index;
}

void quick_sort(int array[], int low, int high) {
    if (low < high) {
        int p = partition(array, low, high);
        quick_sort(array, low, p - 1);
        quick_sort(array, p + 1, high);
    }
}

int binary_search(int array[], int size, int target) {
    int l = 0;
    int r = size - 1;

    while (l <= r) {
        int middle = (l + r) / 2;
        if (array[middle] == target) return middle;
        if (array[middle] < target) {
            l = middle + 1;
        } else {
            r = middle - 1;
        }
    }

    return -1;
}

int binary_range_search(int array[], int size, int target) {
    int l = 0;
    int r = size - 1;
    int middle = 0;

    while (l <= r) {
        middle = l + (r - l) / 2;
        // cout << " l: " << l << " r: " << r << " m: " << middle << ", ";
        if (array[middle] == target) return middle;
        if (array[middle] < target) {
            l = middle + 1;
        } else {
            r = middle - 1;
        }
    }

    if (middle < size - 1 && array[middle] < target && array[middle + 1] > target) {
        return middle;
    }

    if (middle > 0 && array[middle] > target && array[middle - 1] < target) {
        return middle - 1;
    }

    return -1;
}

int main() {
    ////Linked lists
    // LinkedList* ll = new LinkedList();
    // ll->add_head(5);
    // ll->delete_tail();
    // ll->add_head(4);
    // ll->add_head(3);
    // ll->add_head(2);
    // ll->add_tail(6);
    // ll->add_tail(7);
    // ll->delete_tail();
    // ll->delete_middle(4);
    // ll->print_list();
    // delete ll;


    //// Sorting
    // int arr[10] = { 2, 3, 5, 6, 9, 0, 10, 25, 1, 4 };
    // int size = sizeof(arr) / sizeof(arr[0]);

    // insertion_sort(arr, size);
    // merge_sort(arr, 0, size);
    // quick_sort(arr, 0, size - 1);

    // for (int i = 0; i < size; i++) {
    //     cout << arr[i] << " ";
    // }


    // Trees
    // BinarySearchTree bst(5);
    // bst.insert_node(10);
    // bst.insert_node(20);
    // bst.insert_node(15);
    // bst.insert_node(1);
    // bst.insert_node(3);
    // bst.insert_node(4);
    // bst.delete_node(3);
    // bst.depth_first_search();
    // bst.breadth_first_search();
    // cout << "Max value: " << bst.find_max()->value << " ";
    // cout << "Min value: " << bst.find_min()->value << " ";

    //// binary search
    // int arr[10] = { 0, 2, 5, 8, 16, 20, 25, 105 };
    // int size = sizeof(arr) / sizeof(arr[0]);
    // cout << "binary search: " << binary_search(arr, size, 5) << endl;
    // cout << "binary range search: " << binary_range_search(arr, size, 1) << endl;
    return 0;
}