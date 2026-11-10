#include <iostream>
#include <string>
using namespace std;

struct Node {
    string name;
    Node* left;
    Node* right;

    Node(string val) {
        name = val;
        left = NULL;
        right = NULL;
    }
};

void printTree(Node* root) {
    if (root == NULL) return;

    cout << "Member: " << root->name << endl;
    if (root->left != NULL)
        cout << "  Left Child:  " << root->left->name << endl;
    else
        cout << "  Left Child:  None" << endl;

    if (root->right != NULL)
        cout << "  Right Child: " << root->right->name << endl;
    else
        cout << "  Right Child: None" << endl;

    cout << "-----------------------------------" << endl;

    printTree(root->left);
    printTree(root->right);
}

int main() {
    Node* hod = new Node("Dr. HOD");
    Node* coord1 = new Node("CS Coordinator");
    Node* coord2 = new Node("SE Coordinator");
    Node* f1 = new Node("Prof. Ali");
    Node* f2 = new Node("Prof. Sara");
    Node* f3 = new Node("Prof. Usman");
    Node* f4 = new Node("Prof. Ayesha");

    hod->left = coord1;
    hod->right = coord2;

    coord1->left = f1;
    coord1->right = f2;

    coord2->left = f3;
    coord2->right = f4;

    cout << "=== UNIVERSITY DEPARTMENT HIERARCHY ===" << endl << endl;
    printTree(hod);

    return 0;
}
