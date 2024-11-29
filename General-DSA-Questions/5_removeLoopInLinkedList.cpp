// Write a function to remove a loop in a linked list. If a loop is detected, remove the loop and return true; otherwise, return false.

#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

// Fuction to detect a cycle in the linked list
Node* detectCycle(Node* head) {
    // If the list is empty, there is no cycle
    if (head == nullptr) return nullptr;

    Node* slow = head;
    Node* fast = head;

    // Move `slow` by 1 step and `fast` by 2 steps
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        // If slow and fast meet, there is a cycle
        if (slow == fast) {
            return slow;
        }
    }

    // If we reach the end, there is no cycle
    return nullptr;
}

// Function to remove a cycle in the linked list
Node* removeCycle(Node* head) {
    Node* meetingPoint = detectCycle(head);

    // If there is no cycle, return nullptr
    if (meetingPoint == nullptr) return nullptr;

    // Reset one of the pointers to the head
    Node* slow = head;

    // Move both pointers one step at a time until they meet
    // This is the point where the cycle starts, i.e., the node where the slow and meetingPoint pointers meet
    while (slow != meetingPoint) {
        slow = slow->next;
        meetingPoint = meetingPoint->next;
    }

    // The start of the cycle is found
    return slow;
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
    Node* cycleStart = removeCycle(head);

    if (cycleStart) {
        cout << "Cycle removed at node: " << cycleStart->data << endl;
    } else {
        cout << "No cycle detected" << endl;
    }
}

// Maths behind the solution that when slow pointer is reset to head and fast pointer at meeting point, start moving with same speed meet at start of cycle how?
// 1. Let:
//      x: Distance from the head of the list to the start of the cycle.
//      y: Distance from the start of the cycle to the meeting point.
//      C: Length of the entire cycle (number of nodes in the cycle).

// 2. Total distance covered by slow pointer = x + y, before meeting the fast pointer. That means: fast pointer covered 2(x + y) distance as it moves twice the speed of slow pointer.

// 3. Also the total distance covered by fast pointer = x + y + kC, where k is the number of complete cycles made by the fast pointer. 

// 4. We can equate the two distances of fast pointer as:
//      2(x + y) = x + y + kC
//      => x + y = kC
//      => which means x + y is a multiple of C. i.e., x + y is kind of total distance of complete cycle.
//      => From this we can say that if we move slow pointer to head and when it covers distance x, so that means even fast pointer which is at meeting point should also have covered x distance. So, when slow pointer and fast pointer move with same speed they will meet at start of cycle. Since fast pointer has already covered y distance from start of cycle to meeting point, so when it covers x distance it will be at start of cycle.