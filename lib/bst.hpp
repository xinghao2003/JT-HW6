#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <random>

struct BSTNode {
    int data;
    BSTNode *left;
    BSTNode *right;

    BSTNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode *root;

    // Helper function to insert a new value into the tree recursively
    BSTNode* insert(BSTNode *node, int value) {
        if (!node)
            return new BSTNode(value);
        if (value < node->data)
            node->left = insert(node->left, value);
        else
            node->right = insert(node->right, value);
        return node;
    }

    // Helper function to delete a node with the given value and maintain BST properties
    BSTNode* deleteNode(BSTNode* node, int value, bool& success) {
        if (!node) {
            success = false;  // Not found, set success to false
            return nullptr;
        }

        if (value < node->data) {
            node->left = deleteNode(node->left, value, success);
        } else if (value > node->data) {
            node->right = deleteNode(node->right, value, success);
        } else {  // Node found
            // Node with only one child or no child
            if (!node->left || !node->right) {
                BSTNode* temp = node->left ? node->left : node->right;
                if (!temp) {  // No child case
                    temp = node;
                    node = nullptr;
                } else {  // One child case
                    *node = *temp; // Copy the contents of the non-empty child
                }
                delete temp;
                success = true;
            } else {
                // Node with two children: Get the inorder successor
                BSTNode* temp = minValueNode(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data, success);
            }
        }
        return node;
    }

    // Helper function to find the node with the minimum value in the tree
    BSTNode* minValueNode(BSTNode* node) {
        BSTNode* current = node;
        while (current && current->left) {
            current = current->left;
        }
        return current;
    }

    // Helper function to search for a value in the tree recursively
    bool search(BSTNode* node, int value) const {
        if (!node) return false; // Base case: value not found
        if (node->data == value) return true; // Value found
        return value < node->data ? search(node->left, value) : search(node->right, value);
    }

    // Helper function for inorder traversal
    void inorderTraversal(BSTNode *node, std::vector<int> &result) const {
        if (!node)
            return;
        inorderTraversal(node->left, result);
        result.push_back(node->data);
        inorderTraversal(node->right, result);
    }

    // Helper function for preorder traversal
    void preorderTraversal(BSTNode* node, std::vector<int>& result) const {
        if (!node) return;
        result.push_back(node->data);
        preorderTraversal(node->left, result);
        preorderTraversal(node->right, result);
    }

    // Helper function for postorder traversal
    void postorderTraversal(BSTNode* node, std::vector<int>& result) const {
        if (!node) return;
        postorderTraversal(node->left, result);
        postorderTraversal(node->right, result);
        result.push_back(node->data);
    }

    // Helper function to delete all nodes in the tree recursively
    void deleteTree(BSTNode* node) {
        if (node) {
            deleteTree(node->left);   // Recursively delete left subtree
            deleteTree(node->right);  // Recursively delete right subtree
            delete node;              // Delete the current node
        }
    }

    // Helper function to print the tree structure with spacing for visualization
    void printTree(BSTNode* node, int space, int count = 10) const {
        if (!node) return;
        space += count;  // Increase distance between levels
        printTree(node->right, space);  // Process the right child first
        std::cout << std::endl;
        for (int i = count; i < space; i++) std::cout << " ";  // Print current node after space
        std::cout << node->data << "\n";
        printTree(node->left, space);  // Then process the left child
    }

    // Helper function to clear the tree
    void clearTree(BSTNode*& node) {
        if (node != nullptr) {
            clearTree(node->left);
            clearTree(node->right);
            delete node;
            node = nullptr;
        }
    }

public:
    // Constructor to initialize the BST with an empty root
    BST() : root(nullptr) {}

    // Destructor to delete all nodes in the tree
    ~BST() {
        deleteTree(root);  // Call the recursive helper function starting at the root
    }

    // Function to get the root node of the tree
    BSTNode* getRoot() const { return root; }

    // Function to insert a new value into the tree
    void insert(int value) { root = insert(root, value); }

    // Function to clear the tree
    void clear() {
        clearTree(root);
    }

    // Function to delete a node with the given value from the tree
    bool deleteNode(int value) {
        bool success = false;
        root = deleteNode(root, value, success);
        return success;
    }

    // Function to search for a value in the tree
    bool search(int value) const {
        return search(root, value);
    }

    // Function to print the tree structure
    void printTree() const {
        printTree(root, 0);
    }

    // Function to perform inorder traversal and return the result as a vector
    std::vector<int> inorder() const {
        std::vector<int> result;
        inorderTraversal(root, result);
        return result;
    }

    // Function to perform preorder traversal and return the result as a vector
    std::vector<int> preorder() const {
        std::vector<int> result;
        preorderTraversal(root, result);
        return result;
    }

    // Function to perform postorder traversal and return the result as a vector
    std::vector<int> postorder() const {
        std::vector<int> result;
        postorderTraversal(root, result);
        return result;
    }

    // Function to perform level-order traversal and return the result as a vector
    std::vector<int> levelorder() {
        std::vector<int> result;
        if (!root) return result;
        std::queue<BSTNode*> q;
        q.push(root);
        while (!q.empty()) {
            BSTNode* node = q.front();
            q.pop();
            result.push_back(node->data);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        return result;
    }

    // Function to perform non-recursive inorder traversal and return the result as a vector
    std::vector<int> inorderNonRecursive() {
        std::vector<int> result;
        std::stack<BSTNode*> stack;
        BSTNode* current = root;

        while (current != nullptr || !stack.empty()) {
            while (current != nullptr) {
                stack.push(current);
                current = current->left;
            }
            current = stack.top();
            stack.pop();
            result.push_back(current->data);
            current = current->right;
        }
        return result;
    }

    // Function to perform non-recursive preorder traversal and return the result as a vector
    std::vector<int> preorderNonRecursive() {
        if (root == nullptr) return {};

        std::vector<int> result;
        std::stack<BSTNode*> stack;
        stack.push(root);

        while (!stack.empty()) {
            BSTNode* node = stack.top();
            stack.pop();
            result.push_back(node->data);

            if (node->right) stack.push(node->right); // Right child is pushed first
            if (node->left) stack.push(node->left);   // Left child is pushed last
        }
        return result;
    }

    // Function to perform non-recursive postorder traversal and return the result as a vector
    std::vector<int> postorderNonRecursive() {
        if (root == nullptr) return {};

        std::vector<int> result;
        std::stack<BSTNode*> stack1, stack2;
        stack1.push(root);

        while (!stack1.empty()) {
            BSTNode* node = stack1.top();
            stack1.pop();
            stack2.push(node);

            if (node->left) stack1.push(node->left);
            if (node->right) stack1.push(node->right);
        }

        while (!stack2.empty()) {
            result.push_back(stack2.top()->data);
            stack2.pop();
        }
        return result;
    }
};

