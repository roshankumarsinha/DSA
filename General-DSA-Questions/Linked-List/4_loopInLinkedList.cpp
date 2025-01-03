// Write a function to detect a loop in a linked list. If a loop is detected, return true; otherwise, return false.

#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

// To detect a cycle in a linked list, we can use Floyd’s Cycle-Finding Algorithm, also known as the "Tortoise and Hare" approach.
// This technique uses two pointers to traverse the linked list at different speeds, which allows detection of a cycle in linear time.

// Explanation of the Approach
// 1. Two Pointers (Slow and Fast):
//   a. Use two pointers, slow and fast.
//   b. slow moves one step at a time, while fast moves two steps at a time.
// 2. Detecting a Cycle:
//   a. If there is a cycle, fast and slow will eventually meet inside the cycle.
//   b. If fast reaches the end (nullptr), then there is no cycle.

// Maths behind the approach: 
// Since the fast pointer moves twice as fast as the slow pointer, the distance between them decreases by 1 at each step. So, definitely, the fast pointer will meet the slow pointer if there is a cycle.

// Function to detect cycle in the linked list
bool hasCycle(Node* head) {
    // If the list is empty, there is no cycle
    if (head == nullptr) return false;

    Node* slow = head;
    Node* fast = head;

    // Move `slow` by 1 step and `fast` by 2 steps
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        // If slow and fast meet, there is a cycle
        if (slow == fast) {
            return true;
        }
    }

    // If we reach the end, there is no cycle
    return false;
}

// Helper function to create a cycle for testing purposes
// pos: Position of the node where the cycle should start (0-indexed)
// If pos = -1, no cycle is created
void createCycle(Node* head, int pos) {
    if (pos == -1) return;

    Node* temp = head;
    Node* cycleNode = nullptr;
    int index = 0;

    // Find the node at position `pos`
    while (temp->next != nullptr) {
        if (index == pos) {
            cycleNode = temp;
        }
        temp = temp->next;
        index++;
    }

    // Link the last node to the node at `pos` to create a cycle
    temp->next = cycleNode;
}

int main() {
    // Creating a linked list 1 -> 2 -> 3 -> 4 -> 5
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);

    // Create a cycle in the linked list at position 2 (0-indexed)
    createCycle(head, 2);

    // Detect cycle
    if (hasCycle(head)) {
        cout << "Cycle detected in the linked list." << endl;
    } else {
        cout << "No cycle in the linked list." << endl;
    }

    return 0;
}