// Write a function to reverse a linked list

// Notes (Check Optimal Approach 1) : https://takeuforward.org/data-structure/reverse-a-linked-list/

#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

Node* reverseLinkedList(Node* head) {
    // prevNode: Points to the previous node (initially nullptr).
    // currentNode: Points to the current node (initially the head).
    // nextNode: Temporarily holds the next node while reversing the link.

    Node* prevNode = nullptr;
    Node* currentNode = head;
    Node* nextNode = nullptr;
    
    while (currentNode != nullptr) {    // You can also write while (currentNode) {
        // Store next node
        nextNode = currentNode->next;
        
        // Reverse current node's pointer
        currentNode->next = prevNode;
        
        // Move pointers one position ahead
        prevNode = currentNode;
        currentNode = nextNode;
    }
    
    // New head is the previous node
    return prevNode;
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

    // Reverse the linked list
    head = reverseLinkedList(head);

    cout << "Reversed List: ";
    printList(head);

    return 0;
}
