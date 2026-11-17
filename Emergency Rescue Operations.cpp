
#include <iostream>
#include <string>
#include <queue>
using namespace std;

class Node {
public:
    int emergencyID;
    string location;
    int severity;
    int height;
    Node* left;
    Node* right;

    Node(int id, string loc, int sev) {
        emergencyID = id;
        location = loc;
        severity = sev;
        height = 1;
        left = NULL;
        right = NULL;
    }
};

class AVL {
public:
    Node* root;

    AVL() {
        root = NULL;
    }

    int getHeight(Node* node) {
        if (node == NULL) {
            return 0;
        }
        return node->height;
    }

    int getBalance(Node* node) {
        if (node == NULL) {
            return 0;
        }

        return getHeight(node->left) - getHeight(node->right);
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(getHeight(y->left),
                            getHeight(y->right));

        x->height = 1 + max(getHeight(x->left),
                            getHeight(x->right));

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(getHeight(x->left),
                            getHeight(x->right));

        y->height = 1 + max(getHeight(y->left),
                            getHeight(y->right));

        return y;
    }

    Node* insert(Node* node, int id, string loc, int sev) {
        if (node == NULL) {
            return new Node(id, loc, sev);
        }

        if (id < node->emergencyID) {
            node->left = insert(node->left, id, loc, sev);
        }
        else if (id > node->emergencyID) {
            node->right = insert(node->right, id, loc, sev);
        }
        else {
            return node;
        }

        node->height = 1 + max(getHeight(node->left),
                               getHeight(node->right));

        int balance = getBalance(node);

        if (balance > 1 && id < node->left->emergencyID) {
            return rightRotate(node);
        }

        if (balance < -1 && id > node->right->emergencyID) {
            return leftRotate(node);
        }

        if (balance > 1 && id > node->left->emergencyID) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && id < node->right->emergencyID) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void insertEmergency(int id, string loc, int sev) {
        root = insert(root, id, loc, sev);
    }

    Node* search(Node* node, int id) {
        if (node == NULL || node->emergencyID == id) {
            return node;
        }

        if (id < node->emergencyID) {
            return search(node->left, id);
        }

        return search(node->right, id);
    }

    void searchEmergency(int id) {
        Node* result = search(root, id);

        if (result != NULL) {
            cout << "\nEmergency Found!";
            display(result);
        }
        else {
            cout << "\nEmergency Not Found!";
        }
    }

    Node* findMin(Node* node) {
        while (node->left != NULL) {
            node = node->left;
        }

        return node;
    }

    Node* deleteNode(Node* node, int id) {
        if (node == NULL) {
            return node;
        }

        if (id < node->emergencyID) {
            node->left = deleteNode(node->left, id);
        }
        else if (id > node->emergencyID) {
            node->right = deleteNode(node->right, id);
        }
        else {
            if (node->left == NULL || node->right == NULL) {
                Node* temp;

                if (node->left != NULL) {
                    temp = node->left;
                }
                else {
                    temp = node->right;
                }

                if (temp == NULL) {
                    delete node;
                    return NULL;
                }
                else {
                    Node* oldNode = node;
                    node = temp;
                    delete oldNode;
                }
            }
            else {
                Node* temp = findMin(node->right);

                node->emergencyID = temp->emergencyID;
                node->location = temp->location;
                node->severity = temp->severity;

                node->right = deleteNode(node->right,
                                         temp->emergencyID);
            }
        }

        if (node == NULL) {
            return node;
        }

        node->height = 1 + max(getHeight(node->left),
                               getHeight(node->right));

        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0) {
            return rightRotate(node);
        }

        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && getBalance(node->right) <= 0) {
            return leftRotate(node);
        }

        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void deleteEmergency(int id) {
        root = deleteNode(root, id);
    }

    void display(Node* node) {
        cout << "\nEmergency ID: " << node->emergencyID
             << " | Location: " << node->location
             << " | Severity: " << node->severity;
    }

    void inorder(Node* node) {
        if (node != NULL) {
            inorder(node->left);
            display(node);
            inorder(node->right);
        }
    }

    void levelOrder(Node* node) {
        if (node == NULL) {
            return;
        }

        queue<Node*> q;
        q.push(node);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            display(current);

            if (current->left != NULL) {
                q.push(current->left);
            }

            if (current->right != NULL) {
                q.push(current->right);
            }
        }
    }

    void displayBalance(Node* node) {
        if (node != NULL) {
            displayBalance(node->left);

            cout << "\nID: " << node->emergencyID
                 << " | Height: " << node->height
                 << " | Balance Factor: " << getBalance(node);

            displayBalance(node->right);
        }
    }

    void displayTree(Node* node, int space = 0) {
        if (node == NULL) {
            return;
        }

        space += 5;

        displayTree(node->right, space);

        cout << endl;

        for (int i = 5; i < space; i++) {
            cout << " ";
        }

        cout << node->emergencyID << endl;

        displayTree(node->left, space);
    }
};

int main() {
    AVL rescue;

    rescue.insertEmergency(50, "Islamabad", 5);
    rescue.insertEmergency(30, "Lahore", 4);
    rescue.insertEmergency(70, "Karachi", 5);
    rescue.insertEmergency(20, "Peshawar", 3);
    rescue.insertEmergency(40, "Quetta", 4);
    rescue.insertEmergency(60, "Multan", 2);
    rescue.insertEmergency(80, "Faisalabad", 5);
    rescue.insertEmergency(10, "Sialkot", 3);
    rescue.insertEmergency(25, "Murree", 2);
    rescue.insertEmergency(35, "Gujranwala", 4);
    rescue.insertEmergency(45, "Hyderabad", 3);
    rescue.insertEmergency(65, "Abbottabad", 5);

    cout << "\n===== INORDER TRAVERSAL =====";
    rescue.inorder(rescue.root);

    cout << "\n\n===== LEVEL ORDER TRAVERSAL =====";
    rescue.levelOrder(rescue.root);

    cout << "\n\n===== SEARCH EMERGENCY =====";
    rescue.searchEmergency(40);

    cout << "\n\n===== HEIGHT AND BALANCE FACTOR =====";
    rescue.displayBalance(rescue.root);

    cout << "\n\n===== DELETE EMERGENCY =====";
    rescue.deleteEmergency(30);
    cout << "\nEmergency 30 Deleted Successfully!";

    cout << "\n\n===== FINAL AVL TREE =====";
    rescue.displayTree(rescue.root);

    cout << "\n\n===== FINAL INORDER =====";
    rescue.inorder(rescue.root);

    cout << "\n\n===== FINAL LEVEL ORDER =====";
    rescue.levelOrder(rescue.root);

    cout << "\n\n===== FINAL HEIGHT AND BALANCE =====";
    rescue.displayBalance(rescue.root);

    return 0;
}

