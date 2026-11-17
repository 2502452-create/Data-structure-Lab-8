#include <iostream>
#include <string>
using namespace std;

struct Node {
    string folder;
    Node* left;
    Node* right;

    Node(string val) {
        folder = val;
        left = NULL;
        right = NULL;
    }
};

void preOrder(Node* root) {
    if (root == NULL) return;
    cout << root->folder << " ";
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(Node* root) {
    if (root == NULL) return;
    inOrder(root->left);
    cout << root->folder << " ";
    inOrder(root->right);
}

void postOrder(Node* root) {
    if (root == NULL) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->folder << " ";
}

int main() {
    Node* root = new Node("C:");
    root->left = new Node("Documents");
    root->right = new Node("Pictures");

    root->left->left = new Node("Work");
    root->left->right = new Node("Personal");

    root->right->left = new Node("Vacation");
    root->right->right = new Node("Projects");

    cout << "=== FILE EXPLORER DFS TRAVERSALS ===" << endl << endl;

    cout << "Pre-order Traversal (Root -> Left -> Right):" << endl;
    preOrder(root);
    cout << endl << endl;

    cout << "In-order Traversal (Left -> Root -> Right):" << endl;
    inOrder(root);
    cout << endl << endl;

    cout << "Post-order Traversal (Left -> Right -> Root):" << endl;
    postOrder(root);
    cout << endl;

    return 0;
}
