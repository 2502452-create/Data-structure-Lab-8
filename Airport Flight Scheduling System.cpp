
#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int flightNo;
    string destination;
    string departureTime;
    Node* left;
    Node* right;

    Node(int no, string dest, string time) {
        flightNo = no;
        destination = dest;
        departureTime = time;
        left = NULL;
        right = NULL;
    }
};

class BST {
public:
    Node* root;

    BST() {
        root = NULL;
    }

    Node* insert(Node* node, int no, string dest, string time) {
        if (node == NULL) {
            return new Node(no, dest, time);
        }

        if (no < node->flightNo) {
            node->left = insert(node->left, no, dest, time);
        }
        else if (no > node->flightNo) {
            node->right = insert(node->right, no, dest, time);
        }

        return node;
    }

    void insertFlight(int no, string dest, string time) {
        root = insert(root, no, dest, time);
    }

    Node* search(Node* node, int no) {
        if (node == NULL || node->flightNo == no) {
            return node;
        }

        if (no < node->flightNo) {
            return search(node->left, no);
        }

        return search(node->right, no);
    }

    void searchFlight(int no) {
        Node* result = search(root, no);

        if (result != NULL) {
            cout << "\nFlight Found!";
            cout << "\nFlight Number: " << result->flightNo;
            cout << "\nDestination: " << result->destination;
            cout << "\nDeparture Time: " << result->departureTime;
        }
        else {
            cout << "\nFlight Not Found!";
        }
    }

    Node* findMin(Node* node) {
        while (node != NULL && node->left != NULL) {
            node = node->left;
        }
        return node;
    }

    Node* findMax(Node* node) {
        while (node != NULL && node->right != NULL) {
            node = node->right;
        }
        return node;
    }

    Node* deleteFlight(Node* node, int no) {
        if (node == NULL) {
            return node;
        }

        if (no < node->flightNo) {
            node->left = deleteFlight(node->left, no);
        }
        else if (no > node->flightNo) {
            node->right = deleteFlight(node->right, no);
        }
        else {
            if (node->left == NULL) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == NULL) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = findMin(node->right);

            node->flightNo = temp->flightNo;
            node->destination = temp->destination;
            node->departureTime = temp->departureTime;

            node->right = deleteFlight(node->right, temp->flightNo);
        }

        return node;
    }

    void removeFlight(int no) {
        root = deleteFlight(root, no);
    }

    void inorder(Node* node) {
        if (node != NULL) {
            inorder(node->left);
            display(node);
            inorder(node->right);
        }
    }

    void preorder(Node* node) {
        if (node != NULL) {
            display(node);
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(Node* node) {
        if (node != NULL) {
            postorder(node->left);
            postorder(node->right);
            display(node);
        }
    }

    void display(Node* node) {
        cout << "\nFlight No: " << node->flightNo
             << " | Destination: " << node->destination
             << " | Time: " << node->departureTime;
    }

    int countFlights(Node* node) {
        if (node == NULL) {
            return 0;
        }

        return 1 + countFlights(node->left) +
                   countFlights(node->right);
    }

    int height(Node* node) {
        if (node == NULL) {
            return 0;
        }

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        if (leftHeight > rightHeight) {
            return leftHeight + 1;
        }

        return rightHeight + 1;
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

        cout << node->flightNo << endl;

        displayTree(node->left, space);
    }
};

int main() {
    BST airport;

    airport.insertFlight(50, "London", "08:00 AM");
    airport.insertFlight(30, "Dubai", "09:00 AM");
    airport.insertFlight(70, "Paris", "10:00 AM");
    airport.insertFlight(20, "New York", "11:00 AM");
    airport.insertFlight(40, "Istanbul", "12:00 PM");
    airport.insertFlight(60, "Tokyo", "01:00 PM");
    airport.insertFlight(80, "Toronto", "02:00 PM");
    airport.insertFlight(10, "Sydney", "03:00 PM");
    airport.insertFlight(25, "Doha", "04:00 PM");
    airport.insertFlight(35, "Berlin", "05:00 PM");
    airport.insertFlight(45, "Rome", "06:00 PM");
    airport.insertFlight(65, "Madrid", "07:00 PM");

    cout << "\n===== INORDER TRAVERSAL =====";
    airport.inorder(airport.root);

    cout << "\n\n===== PREORDER TRAVERSAL =====";
    airport.preorder(airport.root);

    cout << "\n\n===== POSTORDER TRAVERSAL =====";
    airport.postorder(airport.root);

    cout << "\n\n===== SEARCH FLIGHT =====";
    airport.searchFlight(40);

    cout << "\n\n===== MINIMUM FLIGHT =====";
    Node* minimum = airport.findMin(airport.root);
    cout << "\nMinimum Flight Number: " << minimum->flightNo;

    cout << "\n\n===== MAXIMUM FLIGHT =====";
    Node* maximum = airport.findMax(airport.root);
    cout << "\nMaximum Flight Number: " << maximum->flightNo;

    cout << "\n\nTotal Flights: "
         << airport.countFlights(airport.root);

    cout << "\nTree Height: "
         << airport.height(airport.root);

    cout << "\n\n===== DELETE FLIGHT =====";
    airport.removeFlight(30);

    cout << "\nFlight 30 Deleted Successfully!";

    cout << "\n\n===== FINAL BST STRUCTURE =====";
    airport.displayTree(airport.root);

    cout << "\n\n===== FINAL INORDER =====";
    airport.inorder(airport.root);

    cout << "\n\nTotal Flights After Deletion: "
         << airport.countFlights(airport.root);

    cout << "\nTree Height After Deletion: "
         << airport.height(airport.root);

    return 0;
}

