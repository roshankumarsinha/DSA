// Write a function to merge two sorted linked lists into a single sorted linked list. The function should return the head of the merged list.

#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

// Function to merge two sorted linked lists
Node* mergeSortedLists(Node* l1, Node* l2) {
    // If one of the lists is empty, return the other list
    if (l1 == nullptr) return l2;
    if (l2 == nullptr) return l1;

    // Create a dummy node to store the merged list
    Node* dummy = new Node(-1);
    Node* current = dummy;

    //Traverse both lists and merge them
    while(l1 != nullptr && l2 != nullptr) {
        if (l1->data <= l2->data) {
            current->next = l1; // Append l1's node
            l1 = l1->next;      // Move l1 forward
        } else {
            current->next = l2; // Append l2's node
            l2 = l2->next;      // Move l2 forward
        }
        current = current->next; // Move the current pointer forward
    }

    // Append the remaining nodes of l1 or l2
    if (l1 != nullptr) {
        current->next = l1;
    } else {
        current->next = l2;
    }

    Node* mergedHead = dummy->next;
    delete dummy;

    return mergedHead;

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
    // Create first sorted linked list: 1 -> 3 -> 5
    Node* l1 = new Node(1);
    l1->next = new Node(3);
    l1->next->next = new Node(5);

    // Create second sorted linked list: 2 -> 4 -> 6
    Node* l2 = new Node(2);
    l2->next = new Node(4);
    l2->next->next = new Node(6);

    cout << "List 1: ";
    printList(l1);

    cout << "List 2: ";
    printList(l2);

    // Merge the two sorted lists
    Node* mergedList = mergeSortedLists(l1, l2);

    cout << "Merged List: ";
    printList(mergedList);

    return 0;
}

