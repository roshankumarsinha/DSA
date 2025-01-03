// Write a function to check if a linked list is a palindrome. A palindrome is a sequence that reads the same forwards and backwards.

// Approach 1: You can copy the elements of the linked list to an array and then check if the array is a palindrome. This approach requires O(n) extra space.
// Approach 2: You can reverse the second half of the linked list and then compare it with the first half. This approach requires O(1) extra space.

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

// Function to check if a linked list is a palindrome
bool isPalindrome(Node* head) {
    // If the list is empty or has only one node, it is a palindrome
    if (head == nullptr || head->next == nullptr) return true;

    Node* slow = head;
    Node* fast = head;

    // Find the middle of the linked list
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Reverse the second half of the linked list
    // When number of nodes is odd, the middle node is part of the second half
    // Example: 1 -> 2 -> 3 -> 2 -> 1
    // First half: 1 -> 2 -> 3 (before Reverse)
    // Second half: 1 -> 2 -> 3 (after Reverse)
    // When number of nodes is even, the middle node is part of the first half
    // Example: 1 -> 2 -> 2 -> 1
    // First half: 1 -> 2 -> 2 (before Reverse)
    // Second half: 1 -> 2 (after Reverse)
    Node* secondHalf = reverseList(slow);

    // Compare the first and second halves of the linked list
    Node* firstHalf = head;
    // Since list is not broken firstHalf still contain all data of original list
    while (secondHalf != nullptr) {
        if (firstHalf->data != secondHalf->data) {
            return false;
        }
        firstHalf = firstHalf->next;
        secondHalf = secondHalf->next;
    }

    return true;
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
    // Create a linked list: 1 -> 2 -> 3 -> 2 ->` 1
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(2);
    head->next->next->next->next = new Node(1);
    cout << "Linked List: ";
    printList(head);

    // Check if the linked list is a palindrome
    if (isPalindrome(head)) {
        cout << "The linked list is a palindrome." << endl;
    } else {
        cout << "The linked list is not a palindrome." << endl;
    }

    return 0;
}