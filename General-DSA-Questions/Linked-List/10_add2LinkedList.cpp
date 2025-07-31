// Write a function to add two numbers represented by linked lists. The digits are stored in form of a singly linked list, where each node represents a digit of the number.

// Notes : https://takeuforward.org/data-structure/add-two-numbers-represented-as-linked-lists/

// Approach:
// 1. Reverse both linked lists. This way, the least significant digit is at the head of the list.
// 2. Traverse both linked lists simultaneously and add the corresponding digits along with the carry.
// 3. Create a new linked list to store the result.
// 4. Reverse the result linked list to get the final result.

#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

// Function to reverse a linked list
Node* reverseList(Node* head) {
    Node* prev = nullptr;
    Node* curr = head;
    Node* next = nullptr;

    while (curr != nullptr) {
        next = curr->next; // Store the next node
        curr->next = prev; // Reverse the current node's pointer
        prev = curr;       // Move prev to the current node
        curr = next;       // Move to the next node
    }

    return prev; // New head of the reversed list
}

// Function to add two numbers represented by linked lists
Node* addTwoNumbers(Node* l1, Node* l2) {
    // Reverse both linked lists
    l1 = reverseList(l1);
    l2 = reverseList(l2);

    Node* result = nullptr;
    Node* current = nullptr;
    int carry = 0;

    // Traverse both linked lists simultaneously
    while (l1 != nullptr && l2 != nullptr) {
        int sum = l1->data + l2->data + carry;
        carry = sum / 10;
        int digit = sum % 10;

        // Create a new node for the result
        Node* newNode = new Node(digit);

        // If the result list is empty, set the new node as the head
        if (result == nullptr) {
            result = newNode;
            current = result;
        } else {
            current->next = newNode;
            current = current->next;
        }

        l1 = l1->next;
        l2 = l2->next;
    }

    // Add the remaining digits of l1
    while (l1 != nullptr) {
        int sum = l1->data + carry;
        carry = sum / 10;
        int digit = sum % 10;

        Node* newNode = new Node(digit);
        current->next = newNode;
        current = current->next;

        l1 = l1->next;
    }

    // Add the remaining digits of l2
    while (l2 != nullptr) {
        int sum = l2->data + carry;
        carry = sum / 10;
        int digit = sum % 10;

        Node* newNode = new Node(digit);
        current->next = newNode;
        current = current->next;

        l2 = l2->next;
    }

    // Add the final carry if it exists
    if (carry > 0) {
        Node* newNode = new Node(carry);
        current->next = newNode;
    }

    // Reverse the result linked list
    return reverseList(result);

    // Note:
    // We can write 3 while loops in a single loop by checking if l1 or l2 is not null or carry is not 0
    // while (l1 != nullptr || l2 != nullptr || carry > 0) {
    //     int sum = (l1 ? l1->data : 0) + (l2 ? l2->data : 0) + carry;
    //     carry = sum / 10;
    //     int digit = sum % 10;
    //     Node* newNode = new Node(digit);
    //     if (result == nullptr) {
    //         result = newNode;
    //         current = result;
    //     } else {
    //         current->next = newNode;
    //         current = current->next;
    //     }
    //     if (l1) l1 = l1->next;
    //     if (l2) l2 = l2->next;
    // }

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
    // Create first linked list: 2 -> 4 -> 3 (represents 342)
    Node* l1 = new Node(2);
    l1->next = new Node(4);
    l1->next->next = new Node(3);

    // Create second linked list: 5 -> 6 -> 4 (represents 465)
    Node* l2 = new Node(5);
    l2->next = new Node(6);
    l2->next->next = new Node(4);

    cout << "List 1: ";
    printList(l1);

    cout << "List 2: ";
    printList(l2);

    // Add the two numbers
    Node* result = addTwoNumbers(l1, l2);

    cout << "Result: ";
    printList(result);

    return 0;
}