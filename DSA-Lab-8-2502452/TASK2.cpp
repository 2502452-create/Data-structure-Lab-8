#include <iostream>

using namespace std;

 

class Node {

public:

    int data;

    Node* left;

    Node* right;

 

    Node(int value) {

        data = value;

        left = nullptr;

        right = nullptr;

    }

};

 

class BST {

private:

    Node* root;

 

    Node* insert(Node* node, int value, bool& added) {

        if (node == nullptr) {

            added = true;

            return new Node(value);

        }

 

        if (value < node->data)

            node->left = insert(node->left, value, added);

        else if (value > node->data)

            node->right = insert(node->right, value, added);

        else

            cout << "Duplicate ID rejected." << endl;

 

        return node;

    }

 

    bool searchNode(Node* node, int value) {

        if (node == nullptr)

            return false;

        if (node->data == value)

            return true;

        if (value < node->data)

            return searchNode(node->left, value);

        return searchNode(node->right, value);

    }

 

    Node* findMin(Node* node) {

        while (node != nullptr && node->left != nullptr)

            node = node->left;

        return node;

    }

 

    Node* deleteNode(Node* node, int value, bool& removed) {

        if (node == nullptr)

            return nullptr;

 

        if (value < node->data)

            node->left = deleteNode(node->left, value, removed);

        else if (value > node->data)

            node->right = deleteNode(node->right, value, removed);

        else {

            removed = true;

 

            // Leaf node or node with only a right child

            if (node->left == nullptr) {

                Node* temp = node->right;

                delete node;

                return temp;

            }

 

            // Node with only a left child

            if (node->right == nullptr) {

                Node* temp = node->left;

                delete node;

                return temp;

            }

 

            // Node with two children

            Node* temp = findMin(node->right);

            node->data = temp->data;

            bool ignored = false;

            node->right = deleteNode(node->right, temp->data, ignored);

        }

 

        return node;

    }

 

    void inorder(Node* node) {

        if (node == nullptr)

            return;

        inorder(node->left);

        cout << node->data << " ";

        inorder(node->right);

    }

 

    void preorder(Node* node) {

        if (node == nullptr)

            return;

        cout << node->data << " ";

        preorder(node->left);

        preorder(node->right);

    }

 

    void postorder(Node* node) {

        if (node == nullptr)

            return;

        postorder(node->left);

        postorder(node->right);

        cout << node->data << " ";

    }

 

    int countNodes(Node* node) {

        if (node == nullptr)

            return 0;

        return 1 + countNodes(node->left) + countNodes(node->right);

    }

 

    // Height is measured in number of levels. Empty tree has height 0.

    int height(Node* node) {

        if (node == nullptr)

            return 0;

        int leftHeight = height(node->left);

        int rightHeight = height(node->right);

        if (leftHeight > rightHeight)

            return leftHeight + 1;

        return rightHeight + 1;

    }

 

    void destroy(Node* node) {

        if (node == nullptr)

            return;

        destroy(node->left);

        destroy(node->right);

        delete node;

    }

 

public:

    BST() {

        root = nullptr;

    }

 

    ~BST() {

        destroy(root);

    }

 

    void insertValue(int value) {

        bool added = false;

        root = insert(root, value, added);

        if (added)

            cout << "ID inserted successfully." << endl;

    }

 

    void searchValue(int value) {

        if (root == nullptr) {

            cout << "Tree is empty." << endl;

            return;

        }

 

        if (searchNode(root, value))

            cout << "ID found." << endl;

        else

            cout << "ID not found." << endl;

    }

 

    void deleteValue(int value) {

        if (root == nullptr) {

            cout << "Tree is empty. Nothing to delete." << endl;

            return;

        }

 

        bool removed = false;

        root = deleteNode(root, value, removed);

        if (removed) {

            cout << "ID deleted successfully." << endl;

            cout << "Updated in-order IDs: ";

            displayInorder();

        } else {

            cout << "ID does not exist. Tree unchanged." << endl;

        }

    }

 

    void displayInorder() {

        if (root == nullptr) {

            cout << "Tree is empty.";

        } else {

            inorder(root);

        }

        cout << endl;

    }

 

    void displayPreorder() {

        if (root == nullptr)

            cout << "Tree is empty.";

        else

            preorder(root);

        cout << endl;

    }

 

    void displayPostorder() {

        if (root == nullptr)

            cout << "Tree is empty.";

        else

            postorder(root);

        cout << endl;

    }

 

    void showCount() {

        cout << "Total nodes: " << countNodes(root) << endl;

    }

 

    void showHeight() {

        cout << "Tree height (levels): " << height(root) << endl;

    }

};

 

int main() {

    BST tree;

 

    // Initial hospital record / inventory IDs

    tree.insertValue(55);

    tree.insertValue(35);

    tree.insertValue(75);

    tree.insertValue(25);

    tree.insertValue(45);

    tree.insertValue(65);

    tree.insertValue(85);

    tree.insertValue(40);

    tree.insertValue(50);

 

    int choice, value;

 

    do {

        cout << "\nHOSPITAL AND EMERGENCY INVENTORY SYSTEM" << endl;

        cout << "1. Insert an ID" << endl;

        cout << "2. Search for an ID" << endl;

        cout << "3. Delete an ID" << endl;

        cout << "4. Display in-order traversal" << endl;

        cout << "5. Display pre-order traversal" << endl;

        cout << "6. Display post-order traversal" << endl;

        cout << "7. Count total nodes" << endl;

        cout << "8. Calculate tree height" << endl;

        cout << "9. Exit" << endl;

        cout << "Enter choice: ";

 

        if (!(cin >> choice)) {

            cout << "Invalid input. Please enter a number." << endl;

            cin.clear();

            cin.ignore(1000, '\n');

            choice = 0;

            continue;

        }

 

        switch (choice) {

        case 1:

            cout << "Enter ID to insert: ";

            cin >> value;

            tree.insertValue(value);

            break;

 

        case 2:

            cout << "Enter ID to search: ";

            cin >> value;

            tree.searchValue(value);

            break;

 

        case 3:

            cout << "Enter ID to delete: ";

            cin >> value;

            tree.deleteValue(value);

            break;

 

        case 4:

            cout << "In-order: ";

            tree.displayInorder();

            break;

 

        case 5:

            cout << "Pre-order: ";

            tree.displayPreorder();

            break;

 

        case 6:

            cout << "Post-order: ";

            tree.displayPostorder();

            break;

 

        case 7:

            tree.showCount();

            break;

 

        case 8:

            tree.showHeight();

            break;

 

        case 9:

            cout << "Program ended." << endl;

            break;

 

        default:

            cout << "Invalid choice. Select from 1 to 9." << endl;

        }

 

    } while (choice != 9);

 

    return 0;

}


