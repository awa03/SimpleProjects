#include <iostream>
#include <limits>
#include <random>
#include <queue>

template <typename T>
class Tree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;  // Height of the node
        Node(T val) : data(val), left(nullptr), right(nullptr), height(1) {}
    };

public:
    Tree() : root(nullptr), size(0) {}

    ~Tree() {
        clear(root);
    }

    // Copy constructor
    Tree(const Tree& copy) : root(copyTree(copy.root)) {}

    // Copy assignment operator
    Tree& operator=(const Tree& other) {
        if (this != &other) {
            clear(root);
            root = copyTree(other.root);
        }
        return *this;
    }

    // Insertion function
    void insert(T data) {
        // INIT new node
        Node* insertNode = new Node(data);

        // if the root is empty then add to root
        if(root == nullptr){
            root = insertNode;
        }
        else {
            insertAndBalance(insertNode, root);
        }
    }

    // insert Node;

    // In-order print function
    void inOrderPrint() {
        inOrderPrint(root);
        std::cout << std::endl;
    }

    void levelOrderPrint() {
        if (root == nullptr) {
            return;
        }

        std::queue<Node*> levelQueue;
        levelQueue.push(root);

        while (!levelQueue.empty()) {
            Node* curr = levelQueue.front();
            levelQueue.pop();

            std::cout << curr->data << " ";

            if (curr->left != nullptr) {
                levelQueue.push(curr->left);
            }
            if (curr->right != nullptr) {
                levelQueue.push(curr->right);
            }
        }

        std::cout << std::endl;
    }

private:
    Node* root;
    int size;

    // Recursive function to insert and balance the tree
    void insertAndBalance(Node* newNode, Node*& curr) {
        if(curr == nullptr){
            curr = newNode;
        }
        else{
            if (newNode->data < curr->data) { // if its less recursive
                insertAndBalance(newNode, curr->left);
            } else if (newNode->data > curr->data) {  // if its move recursive
                insertAndBalance(newNode, curr->right);
            } else {
                delete newNode; // Node with the same value already exists
                return;
            }
            
            // adjust height
            curr->height = 1+ std::max(getHeight(curr->left), getHeight(curr->right));
            // find balance factor l - r
            int balance = getHeight(curr->left) - getHeight(curr->right);

            // > 1 && RR newNode->data < curr->left->data
            // < -1 && LR newNode->data > curr->right->data
            // > 1 && LRR newNode->data > curr->left->data
            // < -1 && RLR newNode->data < curr->right->data

            // find position through rotation
            if(balance > -1 && newNode->data < curr->left->data){
                curr = RightRotate(curr);
            }
            else if(balance > -1 && newNode->data < curr->left->data){
                curr = LeftRightRotate(curr);
            }
            
            else if(balance > 1 && newNode->data > curr->left->data){
                curr = LeftRightRotate(curr);
            }

            else if(balance > -1 && newNode->data < curr->right->data){
                curr = RightLeftRotate(curr);
            }
        }
    }

    // Function to get the height of a node
    int getHeight(Node* node) const {
        // base case recursive
        if(node == nullptr){
            return 0;
        }
        return node->height; // return height 
    }

    // In-order print helper function
    void inOrderPrint(Node* node) const {
        if (node != nullptr) {
            inOrderPrint(node->left);
            std::cout << node->data << " ";
            inOrderPrint(node->right);
        }
    }

    // Clear function to delete all nodes in the tree
    void clear(Node* node) {
        if(node != nullptr){
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    Node* LeftRotate(Node* a) {
        Node* b = a->right;
        a->right = b->left;
        b->left = a;

        // update the nodes heights 
        a->height = 1+ std::max(getHeight(a->left), getHeight(a->right));
        b->height = 1+ std::max(getHeight(a->left), getHeight(b->right));
        return b; // return new "subroot"
    }

    Node* RightRotate(Node* a) { 
        // a is the curr node 
        Node* b = a->left; // set b as the new "subroot"
        b->right = a; // b right node is now a

        // update the nodes heights 
        a->height = 1+ std::max(getHeight(a->left), getHeight(a->right));
        b->height = 1+ std::max(getHeight(a->left), getHeight(b->right));
        return b; // return new "subroot"
    }

    Node* LeftRightRotate(Node* a) {
        a->left = LeftRotate(a->left);
        return RightRotate(a);
        
    }

    Node* RightLeftRotate(Node* a) {
        a->right = RightRotate(a->right);
        return LeftRotate(a);
    }
};

int main() {
    Tree<int> t;
    t.insert(10);

    return 0;
}
