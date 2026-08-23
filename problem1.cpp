#include <iostream>
using namespace std;

// Node structure
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int value) {
        key = value;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

// Get height of a node
int getHeight(Node* node) {
    if (node == nullptr)
        return 0;

    return node->height;
}

// Get maximum of two numbers
int maxValue(int a, int b) {
    return (a > b) ? a : b;
}

// Calculate balance factor
int getBalanceFactor(Node* node) {
    if (node == nullptr)
        return 0;

    return getHeight(node->left) - getHeight(node->right);
}

// Right Rotation
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + maxValue(getHeight(y->left),
                             getHeight(y->right));

    x->height = 1 + maxValue(getHeight(x->left),
                             getHeight(x->right));

    return x;
}

// Left Rotation
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + maxValue(getHeight(x->left),
                             getHeight(x->right));

    y->height = 1 + maxValue(getHeight(y->left),
                             getHeight(y->right));

    return y;
}

// Insert a node
Node* insertNode(Node* root, int key) {

    // Normal BST insertion
    if (root == nullptr)
        return new Node(key);

    if (key < root->key)
        root->left = insertNode(root->left, key);

    else if (key > root->key)
        root->right = insertNode(root->right, key);

    else {
        cout << "Duplicate value not allowed!\n";
        return root;
    }

    // Update height
    root->height = 1 + maxValue(getHeight(root->left),
                                getHeight(root->right));

    // Calculate balance factor
    int balance = getBalanceFactor(root);

    // LL Case
    if (balance > 1 && key < root->left->key) {
        return rightRotate(root);
    }

    // RR Case
    if (balance < -1 && key > root->right->key) {
        return leftRotate(root);
    }

    // LR Case
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL Case
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Find minimum value node
Node* minValueNode(Node* root) {
    Node* current = root;

    while (current->left != nullptr)
        current = current->left;

    return current;
}

// Delete a node
Node* deleteNode(Node* root, int key) {

    // Normal BST deletion
    if (root == nullptr) {
        cout << "Value not found!\n";
        return root;
    }

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    }
    else {

        // Node with no child
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }

        // Node with only right child
        else if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }

        // Node with only left child
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Node with two children
        else {
            Node* temp = minValueNode(root->right);

            root->key = temp->key;

            root->right = deleteNode(root->right, temp->key);
        }
    }

    // Update height
    root->height = 1 + maxValue(getHeight(root->left),
                                getHeight(root->right));

    // Calculate balance factor
    int balance = getBalanceFactor(root);

    // LL Case
    if (balance > 1 &&
        getBalanceFactor(root->left) >= 0) {
        return rightRotate(root);
    }

    // LR Case
    if (balance > 1 &&
        getBalanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR Case
    if (balance < -1 &&
        getBalanceFactor(root->right) <= 0) {
        return leftRotate(root);
    }

    // RL Case
    if (balance < -1 &&
        getBalanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Inorder Traversal
void inorder(Node* root) {
    if (root == nullptr)
        return;

    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

// Preorder Traversal
void preorder(Node* root) {
    if (root == nullptr)
        return;

    cout << root->key << " ";
    preorder(root->left);
    preorder(root->right);
}

// Postorder Traversal
void postorder(Node* root) {
    if (root == nullptr)
        return;

    postorder(root->left);
    postorder(root->right);
    cout << root->key << " ";
}

// Display tree with balance factor
void display(Node* root) {
    if (root == nullptr)
        return;

    display(root->left);

    cout << "Node: " << root->key
         << " | Height: " << root->height
         << " | Balance Factor: "
         << getBalanceFactor(root) << endl;

    display(root->right);
}

// Search a value
bool search(Node* root, int key) {

    if (root == nullptr)
        return false;

    if (root->key == key)
        return true;

    if (key < root->key)
        return search(root->left, key);

    return search(root->right, key);
}

// Main function
int main() {

    Node* root = nullptr;

    int choice;
    int value;

    do {
        cout << "\n========== AVL TREE MENU ==========\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Search\n";
        cout << "4. Inorder Traversal\n";
        cout << "5. Preorder Traversal\n";
        cout << "6. Postorder Traversal\n";
        cout << "7. Display Node Details\n";
        cout << "8. Exit\n";
        cout << "===================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                cout << "Enter value to insert: ";
                cin >> value;

                root = insertNode(root, value);

                cout << "Value inserted successfully.\n";
                break;

            case 2:
                cout << "Enter value to delete: ";
                cin >> value;

                if (search(root, value)) {
                    root = deleteNode(root, value);
                    cout << "Value deleted successfully.\n";
                }
                else {
                    cout << "Value not found in AVL Tree.\n";
                }

                break;

            case 3:
                cout << "Enter value to search: ";
                cin >> value;

                if (search(root, value))
                    cout << "Value found in AVL Tree.\n";
                else
                    cout << "Value not found.\n";

                break;

            case 4:
                cout << "Inorder Traversal: ";
                inorder(root);
                cout << endl;
                break;

            case 5:
                cout << "Preorder Traversal: ";
                preorder(root);
                cout << endl;
                break;

            case 6:
                cout << "Postorder Traversal: ";
                postorder(root);
                cout << endl;
                break;

            case 7:
                if (root == nullptr) {
                    cout << "Tree is empty.\n";
                }
                else {
                    cout << "\nNode Details:\n";
                    display(root);
                }
                break;

            case 8:
                cout << "Program terminated.\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 8);

    return 0;
}