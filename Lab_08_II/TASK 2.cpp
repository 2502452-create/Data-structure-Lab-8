#include <iostream>
#include <string>
#include <queue>
using namespace std;

struct Node {
    string category;
    Node* left;
    Node* right;

    Node(string val) {
        category = val;
        left = NULL;
        right = NULL;
    }
};

void bfs(Node* root) {
    if (root == NULL) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        cout << curr->category << " -> ";

        if (curr->left != NULL) q.push(curr->left);
        if (curr->right != NULL) q.push(curr->right);
    }
    cout << "END" << endl;
}

int main() {
    Node* root = new Node("Electronics");
    root->left = new Node("Mobiles");
    root->right = new Node("Laptops");

    root->left->left = new Node("Clothing");
    root->left->right = new Node("Men");

    root->right->left = new Node("Women");
    root->right->right = new Node("Accessories");

    cout << "=== SHOPPING CATEGORIES (BFS TRAVERSAL) ===" << endl;
    bfs(root);

    return 0;
}
