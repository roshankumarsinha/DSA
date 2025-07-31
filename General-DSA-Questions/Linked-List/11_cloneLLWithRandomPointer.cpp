// Write a function to clone a linked list which has a next pointer and a random pointer.

// The random pointer can point to any node in the linked list or be NULL.

// Notes : https://takeuforward.org/data-structure/clone-linked-list-with-random-and-next-pointer/

// Approach 1 : Using unordered_map
// 1. Create a mapping of original nodes to cloned nodes using an unordered_map.
// 2. Traverse the original linked list and for each node, create a new node and store it in the map.
// 3. Set the next and random pointers of the cloned nodes using the map.
// 4. Return the head of the cloned linked list.
// Time Complexity: O(n)
// Space Complexity: O(n)

// Approach 2 : Using constant space
// Step 1 : Create a copy of each node and insert it next to original node. i.e., if original linked list is 1 -> 2 -> 3, then after this step it will be 1 -> 1' -> 2 -> 2' -> 3 -> 3'.
// Step 2 : Set the random pointers of the cloned nodes. i.e., if original linked list is 1 -> 2 -> 3 and random pointers are 1 -> 3, 2 -> 1, 3 -> NULL, then after this step it will be
// 1 -> 1' -> 2 -> 2' -> 3 -> 3' with random pointers 1' -> 3', 2' -> 1', 3' -> NULL.
// Step 3 : Separate the cloned linked list from the original linked list.
// Time Complexity: O(n)
// Space Complexity: O(1)

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* random;

    Node(int val) : data(val), next(nullptr), random(nullptr) {}
};

// Function to copy the linked list with random pointers
Node* copyRandomList(Node* head) {
    if (!head) return nullptr;

    // Step 1: Clone nodes and insert them into the list
    Node* current = head;
    while (current) {
        Node* newNode = new Node(current->data);  // Create a new node with the same data
        newNode->next = current->next;  // Link the new node to the next of the current node
        current->next = newNode;  // Insert the new node after the current node
        current = newNode->next;  // Move to the next original node, which is now after the new node
    }

    // Step 2: Update random pointers for the cloned nodes
    current = head;
    while (current) {
        if (current->random) {  // If the current node has a random pointer
            // Set the random pointer of the cloned node
            // current->next is the cloned node of original current node, so here we set its random pointer to the cloned node of current->random
            current->next->random = current->random->next;
        }
        current = current->next->next; // Move to the next original node, which is two steps ahead
    }

    // Step 3: Separate the original and cloned lists
    Node* newHead = head->next; // The head of the cloned linked list
    Node* original = head;  // Pointer to traverse the original linked list
    Node* clone = newHead;  // Pointer to traverse the cloned linked list

    while (original) {
        original->next = original->next->next;  // Restore the next pointer of the original node
        if (clone->next) {  // If there is a next cloned node
            clone->next = clone->next->next;  // Restore the next pointer of the cloned node
        }
        original = original->next;  // Move to the next original node
        clone = clone->next;  // Move to the next cloned node
    }

    return newHead;
}

// Helper function to print a linked list with random pointers
void printList(Node* head) {
    Node* temp = head;
    while (temp) {
        cout << "Node: " << temp->data;
        if (temp->random) {
            cout << ", Random: " << temp->random->data;
        } else {
            cout << ", Random: NULL";
        }
        cout << endl;
        temp = temp->next;
    }
    cout << endl;
}

// Helper function to create a linked list with random pointers
Node* insertNode(Node* head, int data) {
    Node* newNode = new Node(data);
    if (!head) {
        return newNode;
    }
    Node* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

int main() {
    // Create a linked list: 1 -> 2 -> 3 -> 4
    Node* head = nullptr;
    head = insertNode(head, 1);
    head = insertNode(head, 2);
    head = insertNode(head, 3);
    head = insertNode(head, 4);

    // Assign random pointers
    head->random = head->next->next;       // 1's random points to 3
    head->next->random = head;            // 2's random points to 1
    head->next->next->random = head->next->next; // 3's random points to itself
    head->next->next->next->random = head->next; // 4's random points to 2

    cout << "Original List:" << endl;
    printList(head);

    // Copy the linked list with random pointers
    Node* copiedList = copyRandomList(head);

    cout << "Copied List:" << endl;
    printList(copiedList);

    return 0;
}


