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
        Node* temp = new Node(data);
        if (root == nullptr) {
            root = temp;
        } else {
            insertAndBalance(temp, root);
        }
    }

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
            Node* current = levelQueue.front();
            levelQueue.pop();

            std::cout << current->data << " ";

            if (current->left != nullptr) {
                levelQueue.push(current->left);
            }
            if (current->right != nullptr) {
                levelQueue.push(current->right);
            }
        }

        std::cout << std::endl;
    }

private:
    Node* root;
    int size;

    // Recursive function to insert and balance the tree
    void insertAndBalance(Node* newNode, Node*& curr) {
        // if the node is null 
        if (curr == nullptr) {
            curr = newNode; // set that node to the new node
        } else {
            if (newNode->data < curr->data) { // if its less recursive
                insertAndBalance(newNode, curr->left);
            } else if (newNode->data > curr->data) {  // if its move recursive
                insertAndBalance(newNode, curr->right);
            } else {
                delete newNode; // Node with the same value already exists
                return;
            }

            // Update height of the current node
            curr->height = 1 + std::max(getHeight(curr->left), getHeight(curr->right));

            // Check balance factor and perform rotations if needed
            int balance = getHeight(curr->left) - getHeight(curr->right);

            // Left-Left case
            if (balance > 1 && newNode->data < curr->left->data) {
                curr = RightRotate(curr);
            }
            // Right-Right case
            else if (balance < -1 && newNode->data > curr->right->data) {
                curr = LeftRotate(curr);
            }
            // Left-Right case
            else if (balance > 1 && newNode->data > curr->left->data) {
                curr = LeftRightRotate(curr);
            }
            // Right-Left case
            else if (balance < -1 && newNode->data < curr->right->data) {
                curr = RightLeftRotate(curr);
            }
        }
    }

    // Function to get the height of a node
    int getHeight(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
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
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    Node* LeftRotate(Node* a) {
        Node* b = a->right;
        a->right = b->left;
        b->left = a;

        // Update heights
        a->height = 1 + std::max(getHeight(a->left), getHeight(a->right));
        b->height = 1 + std::max(getHeight(b->left), getHeight(b->right));
        return b;
    }

    Node* RightRotate(Node* a) {
        Node* b = a->left;
        a->left = b->right;
        b->right = a;
        // Update heights
        
        a->height = 1 + std::max(getHeight(a->left), getHeight(a->right));
        b->height = 1 + std::max(getHeight(b->left), getHeight(b->right));
        return b;
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
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    // Generate and print 10 random numbers
    std::cout << "Insetion Order: ";
    for (int i = 0; i < 10; ++i) {
        int random_number = distribution(generator);
        t.insert(random_number);
        std::cout << random_number << " ";
    }
    std::cout << std::endl;


    // Print the tree in the specified format
    std::cout << "In-Order Traversal: ";
    t.inOrderPrint();
    std::cout << "Level-Order Traversal: ";
    t.levelOrderPrint();

    return 0;
}
