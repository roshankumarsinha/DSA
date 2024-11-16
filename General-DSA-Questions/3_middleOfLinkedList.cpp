// Write a function to find the middle of a linked list, if the number of nodes is odd, return the middle node. If the number of nodes is even, return the second middle node.

#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

// To find the middle of a singly linked list, you can use the two-pointer technique, often referred to as the "slow and fast pointer" approach.
// This method allows you to find the middle of the linked list in a single traversal.

// Explanation :-
// 1. Two-Pointer Technique:-
//   a. Use two pointers: slow and fast.
//   b. slow pointer moves one node at a time, while the fast pointer moves two nodes at a time.
// 2. Finding the Middle:
//   a. When the fast pointer reaches the end of the list, the slow pointer will be at the middle of the list.
//   b. If the list has an even number of nodes, this approach will return the second middle node.

Node* findMiddle(Node* head) {
    if (head == nullptr) return nullptr;

    Node* slow = head;
    Node* fast = head;

    // Move `fast` by 2 steps and `slow` by 1 step
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // When `fast` reaches the end, `slow` will be at the middle
    return slow;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    // Creating a simple linked list 1 -> 2 -> 3 -> 4 -> 5
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);

    cout << "Original List: ";
    printList(head);

    // Find the middle of the linked list
    Node* middle = findMiddle(head);

    if (middle != nullptr) {
        cout << "Middle Node: " << middle->data << endl;
    } else {
        cout << "The list is empty." << endl;
    }

    return 0;
}