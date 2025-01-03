// Write a function to remove duplicates from a sorted linked list. The function should modify the list in place and return the head of the modified list.

#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

// Function to remove duplicates from a sorted linked list
Node* removeDuplicates(Node* head) {
    // If the list is empty or has only one node, there are no duplicates
    if (head == nullptr || head->next == nullptr) return head;

    Node* current = head;

    // Traverse the list
    while (current != nullptr && current->next != nullptr) {
        // If the current node's data is the same as the next node's data
        if (current->data == current->next->data) {
            // Skip the next node
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        } else {
            // Move to the next node
            current = current->next;
        }
    }

    return head;
}

// Helper function to print the linked list
void printList(Node* head) {
    Node* current = head;

    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }

    cout << endl;
}

int main() {
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(2);
    head->next->next->next = new Node(2);
    head->next->next->next->next = new Node(3);

    printList(head);
    printList(removeDuplicates(head));
}

// Assume that we have given that linked list is not sorted then we have 2 solutions to solve the same questions to duplicate the elements in the linked list.
// 1. Using Hashing(map) - Time complexity: O(N), Space complexity: O(N) - store the elements in the map and check if the element is already present in the map then delete the node.
//    a. Create a map to store the elements of the linked list. like map<int, bool> m;
//    b. Traverse the linked list and check if the element is already present in the map then delete the node.
//    c. If the element is not present in the map then insert the element in the map.
//    d. Return the head of the linked list.
// 2. Using 2 pointers - Time complexity: O(N^2), Space complexity: O(1) - This is the brute force approach