
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

struct Node {
    int token;
    Node* left;
    Node* right;
    int height;

    Node(int val) {
        token = val;
        left = NULL;
        right = NULL;
        height = 1;
    }
};

int getHeight(Node* n) {
    if (n == NULL) return 0;
    return n->height;
}

int getBalance(Node* n) {
    if (n == NULL) return 0;
    return getHeight(n->left) - getHeight(n->right);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

Node* insert(Node* node, int token) {
    if (node == NULL) return new Node(token);

    if (token < node->token)
        node->left = insert(node->left, token);
    else if (token > node->token)
        node->right = insert(node->right, token);
    else
        return node;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && token < node->left->token)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && token > node->right->token)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && token > node->left->token) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && token < node->right->token) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inOrder(Node* root) {
    if (root == NULL) return;
    inOrder(root->left);
    cout << root->token << " ";
    inOrder(root->right);
}

void printTreeStructure(Node* root, string indent = "", bool isLast = true) {
    if (root != NULL) {
        cout << indent;
        if (isLast) {
            cout << "+-- ";
            indent += "    ";
        } else {
            cout << "+-- ";
            indent += "¦   ";
        }
        cout << root->token << endl;
        printTreeStructure(root->left, indent, false);
        printTreeStructure(root->right, indent, true);
    }
}

int main() {
    Node* root = NULL;
    int tokens[] = {15, 25, 35, 45, 55, 65, 75};

    for (int i = 0; i < 7; i++) {
        root = insert(root, tokens[i]);
    }

    cout << "=== HOSPITAL APPOINTMENT SYSTEM (AVL TREE) ===" << endl << endl;

    cout << "In-Order Traversal (Sorted Tokens):" << endl;
    inOrder(root);
    cout << endl << endl;

    cout << "Final Balanced AVL Tree Structure:" << endl;
    printTreeStructure(root);

    return 0;
}
