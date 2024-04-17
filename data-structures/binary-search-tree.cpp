struct Node {
    Node* left;
    Node* right;
    int val;

    Node(int value) {
        left = nullptr;
        right = nullptr;
        val = value;
    }
};

class BinaryTree {
    Node* root;
    int height;
public:
    BinaryTree () {
        root->left = nullptr;
        root->right = nullptr;
        height = 0;
    }
    
    Node* insertHelper(Node* root, int val) {
        if (root == nullptr) return new Node();

        if (root->val <= val) {
            root->left = insertHelper(root->left, val);
        } else {
            root->right = insertHelper(root->right, val);
        }

        return root;
    }

    Node* insert (int val) {
        return insertNode(root, val);
    }

    Node* removeNode(Node* root, int val) {
        if (root == nullptr) {
            return root;
        }

        if (val < root->val) {
            root->left = removeNode(root->left, val);
        } else if (val > root->val) {
            root->right = removeNode(root->right, val);
        } else {
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                return nullptr;
            }

            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            int minVal = findMinValue(root->right);
            root->val = minVal;
            root->right = removeNode(root->right, minVal);
        }

        return root;
    }

    void remove (int val) {
        root = removeNode(root, val);
    }

    bool search (int val) {
        Node* itr = root;
        while (itr != nullptr) {
            if (itr->val == val) {
                return true;
            }
            if (itr->val > val) {
                itr = itr->left;
            } else {
                itr = itr->right;
            }
        }
        return false;
    }

    int findMin () {
        Node* min = root;
        while (itr != nullptr && itr->left != nullptr) {
            min = min->left;
        }
        return min->val;
    }

    int findMax () {
        Node* max = root;
        while (itr != nullptr && itr->right != nullptr) {
            max = max->right;
        }
        return max->val;
    }

    int getHeightHelper(Node* root) {
        if (root == nullptr) return 0;
        return (std::max(getHeightHelper(root->left), getHeightHelper(root->right))) + 1;
    }

    int getHeight() {
        if (root == nullptr) return 0;
        return getHeightHelper(root);
    }

    void printInOrderHelper(Node* root) {
        if (root == nullptr) return;
        printInOrder(root->left);
        std::cout << root->val << " ";
        printInOrder(root->right);
    }

    void printInOrder() {
        printInOrder(root);
    }
}

int main() {
    BinarySearchTree bst;
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(1);
    bst.insert(4);

    cout << "In-order traversal: ";
    bst.printInOrder(); // Output: 1 3 4 5 7

    cout << "Minimum value: " << bst.findMin() << endl; // Output: 1
    cout << "Maximum value: " << bst.findMax() << endl; // Output: 7
    cout << "Height of the tree: " << bst.getHeight() << endl; // Output: 2

    cout << "Searching for 4: " << bst.search(4) << endl; // Output: 1 (true)
    cout << "Searching for 10: " << bst.search(10) << endl; // Output: 0 (false)

    bst.remove(3);
    cout << "After removing 3, in-order traversal: ";
    bst.printInOrder(); // Output: 1 4 5 7

    return 0;
}