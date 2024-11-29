// Write a function to sort 0s, 1s, and 2s in a linked list. Note data replcement is not allowed.

// Approach 1: Count the number of 0s, 1s, and 2s in the linked list and then update the linked list with the counts. But this is not recommended.

// Approach 2: Create three separate linked lists for 0s, 1s, and 2s. Traverse the original linked list and insert the nodes into the respective lists. Finally, merge the three lists.

// Solving using Approach 2:
#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

// Function to sort 0s, 1s, and 2s in a linked list
Node* sortList(Node* head) {
    // Create three separate linked lists for 0s, 1s, and 2s
    // These lists will contain dummy nodes to make insertion easier
    Node* zeroHead = new Node(-1);
    Node* oneHead = new Node(-1);
    Node* twoHead = new Node(-1);
    
    // Create tails for each list to insert nodes at the end
    Node* zeroTail = zeroHead;
    Node* oneTail = oneHead;
    Node* twoTail = twoHead;
    
    Node* current = head;
    
    // Traverse the original linked list
    while (current != nullptr) {
        int val = current->data;

        // Insert the node into the respective list
        if (val == 0) {
            zeroTail->next = current;
            zeroTail = zeroTail->next;
        } else if (val == 1) {
            oneTail->next = current;
            oneTail = oneTail->next;
        } else {
            twoTail->next = current;
            twoTail = twoTail->next;
        }

        // Move to the next node
        current = current->next;

    }

    // Combine the three lists
    if (oneHead->next != nullptr) {
        zeroTail->next = oneHead->next;
    } else {
        zeroTail->next = twoHead->next;
    }
    oneTail->next = twoHead->next;
    twoTail->next = nullptr;

    head = zeroHead->next;

    // Delete the dummy nodes
    delete zeroHead;
    delete oneHead;
    delete twoHead;

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
    // Create a linked list: 1 -> 2 -> 0 -> 1 -> 2 -> 0
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(0);
    head->next->next->next = new Node(1);
    head->next->next->next->next = new Node(2);
    head->next->next->next->next->next = new Node(0);

    cout << "Original List: ";
    printList(head);

    // Sort the linked list
    head = sortList(head);

    cout << "Sorted List: ";
    printList(head);

    return 0;
}