#include <iostream>

#include <string>

using namespace std;

 

// General binary tree node stores staff name

class NameNode {

public:

    string name;

    NameNode* left;

    NameNode* right;

 

    NameNode(string n) {

        name = n;

        left = nullptr;

        right = nullptr;

    }

};

 

class NameTree {

public:

    NameNode* root;

 

    NameTree() {

        root = nullptr;

    }

 

    void display(NameNode* node) {

        if (node == nullptr)

            return;

 

        cout << "Staff: " << node->name << endl;

        cout << "  Left child: ";

        if (node->left != nullptr)

            cout << node->left->name << endl;

        else

            cout << "NULL" << endl;

 

        cout << "  Right child: ";

        if (node->right != nullptr)

            cout << node->right->name << endl;

        else

            cout << "NULL" << endl;

 

        cout << endl;

        display(node->left);

        display(node->right);

    }

 

    void destroy(NameNode* node) {

        if (node == nullptr)

            return;

        destroy(node->left);

        destroy(node->right);

        delete node;

    }

 

    ~NameTree() {

        destroy(root);

    }

};

 

// BST node stores staff ID

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

            cout << "Duplicate ID rejected: " << value << endl;

 

        return node;

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

 

            // No left child: leaf or one right child

            if (node->left == nullptr) {

                Node* temp = node->right;

                delete node;

                return temp;

            }

 

            // One left child

            if (node->right == nullptr) {

                Node* temp = node->left;

                delete node;

                return temp;

            }

 

            // Two children: use smallest value in right subtree

            Node* temp = findMin(node->right);

            node->data = temp->data;

            bool ignored = false;

            node->right = deleteNode(node->right, temp->data, ignored);

        }

 

        return node;

    }

 

    bool searchNode(Node* node, int value, int& visits) {

        if (node == nullptr)

            return false;

 

        visits++;

        if (value == node->data)

            return true;

        if (value < node->data)

            return searchNode(node->left, value, visits);

        return searchNode(node->right, value, visits);

    }

 

    void inorder(Node* node) {

        if (node == nullptr)

            return;

        inorder(node->left);

        cout << node->data << " ";

        inorder(node->right);

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

            cout << "ID inserted: " << value << endl;

    }

 

    void searchValue(int value) {

        int visits = 0;

        bool found = searchNode(root, value, visits);

        if (found)

            cout << "ID " << value << " exists. Node visits: " << visits << endl;

        else

            cout << "ID " << value << " not found. Node visits: " << visits << endl;

    }

 

    void deleteValue(int value) {

        bool removed = false;

        root = deleteNode(root, value, removed);

        if (removed) {

            cout << "ID deleted. Remaining IDs: ";

            display();

        } else {

            cout << "ID " << value << " does not exist." << endl;

        }

    }

 

    void display() {

        inorder(root);

        cout << endl;

    }

 

    // Used for demonstrating deletion cases with a fresh tree

    void makeOriginalTree() {

        insertValue(48);

        insertValue(28);

        insertValue(68);

        insertValue(18);

        insertValue(38);

        insertValue(58);

        insertValue(78);

    }

};

 

int main() {

    cout << "UNIVERSITY STAFF MANAGEMENT SYSTEM" << endl;

 

    // General binary tree with seven staff names

    NameTree names;

    names.root = new NameNode("Ali");

    names.root->left = new NameNode("Sara");

    names.root->right = new NameNode("Ahmed");

    names.root->left->left = new NameNode("Hina");

    names.root->left->right = new NameNode("Usman");

    names.root->right->left = new NameNode("Ayesha");

    names.root->right->right = new NameNode("Bilal");

 

    cout << "\nGENERAL BINARY TREE (staff names and children)" << endl;

    names.display(names.root);

 

    BST tree;

    cout << "\nInitial staff IDs:" << endl;

    tree.insertValue(48);

    tree.insertValue(28);

    tree.insertValue(68);

    tree.insertValue(18);

    tree.insertValue(38);

    tree.insertValue(58);

    tree.insertValue(78);

 

    cout << "\nEnter three additional staff IDs:" << endl;

    for (int i = 1; i <= 3; i++) {

        int id;

        cout << "ID " << i << ": ";

        cin >> id;

        tree.insertValue(id);

    }

 

    cout << "\nIDs in ascending order: ";

    tree.display();

 

    int searchID;

    cout << "\nEnter an ID to search: ";

    cin >> searchID;

    tree.searchValue(searchID);

 

    // Required search tests: existing, missing, and smaller than all initial IDs

    cout << "\nSearch test for existing ID 48:" << endl;

    tree.searchValue(48);

    cout << "Search test for missing ID 999:" << endl;

    tree.searchValue(999);

    cout << "Search test for ID smaller than all initial IDs (1):" << endl;

    tree.searchValue(1);

 

    int deleteID;

    cout << "\nEnter an ID to delete from the current tree: ";

    cin >> deleteID;

    tree.deleteValue(deleteID);

 

    // Each deletion case uses a fresh copy of the original seven-ID BST.

    cout << "\nDELETION CASE TESTS (fresh original tree each time)" << endl;

 

    cout << "\n1. Leaf node deletion (18):" << endl;

    {

        BST test;

        test.makeOriginalTree();

        test.deleteValue(18);

    }

 

    cout << "\n2. One-child deletion (18 has child 17):" << endl;

    {

        BST test;

        test.makeOriginalTree();

        test.insertValue(17);

        test.deleteValue(18);

    }

 

    cout << "\n3. Two-children deletion (28):" << endl;

    {

        BST test;

        test.makeOriginalTree();

        test.deleteValue(28);

    }

 

    cout << "\nExplanation:" << endl;

    cout << "A general binary tree has no sorting rule, so its values may be in any order." << endl;

    cout << "In a BST, smaller values go left and larger values go right." << endl;

    cout << "Therefore, in-order traversal (left, root, right) displays BST IDs in ascending order." << endl;

 

    return 0;

}


