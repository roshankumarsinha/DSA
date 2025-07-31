// Write a C++ code to flatten a multilevel sorted linked list.

// Notes : https://takeuforward.org/data-structure/flattening-a-linked-list/

// You are given a special linked list where:
// Each node has:
//  next pointer → points to the next node horizontally
//  child pointer → points to a sorted linked list vertically

// The task is to flatten the linked list such that all nodes are in a single sorted linked list, maintaining the order of nodes.

// Example:
// Input: 1 -> 2 -> 3 -> 4 -> 5
//        |    |    |    |
//        6    7    8    9
//        |
//       10
// Output: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10

// Approach 1 (using Array):
// 1. Traverse each node with all its child nodes and store them in an array.
// 2. We will have N different arrays, each containing the nodes of a child linked list.
// 3. We can now merge these N arrays into a single sorted array using mergeKSortedArrays code which we read on heap.

// Approach 2 (using recursion and without extra space):
// 1. We will use approach of merge 2 sorted linked lists.
// 2. We will use recursion to select last 2 linked lists and merge them and make a single faltten linked list and then repeat the process until we have only one linked list left.

// For above example flow will be :
// 1. flattenLinkedList(1) -> flattenLinkedList(2) -> flattenLinkedList(3) -> flattenLinkedList(4) -> flattenLinkedList(5)
// 2. It will merge(4, 5 is mergedHead) -> merge(3, mergedHead) -> merge(2, mergedHead) -> merge(1, mergedHead)


#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node *next;
    Node *child;

    // Constructors to initialize the
    // data, next, and child pointers
    Node() : data(0), next(nullptr), child(nullptr) {};
    Node(int x) : data(x), next(nullptr), child(nullptr) {}
    Node(int x, Node *nextNode, Node *childNode) : data(x), next(nextNode), child(childNode) {}
};

// Merges two linked lists in a particular
// order based on the data value
Node* merge(Node* list1, Node* list2){
    // Create a dummy node as a
    // placeholder for the result
    Node* dummyNode = new Node(-1);
    Node* res = dummyNode;

    // Merge the lists based on data values
    while(list1 != NULL && list2 != NULL){
        if(list1->data < list2->data){
            // If list1's data is smaller, add it to the result
            // and move to the next node in list1
            res->child = list1;
            res = list1;  // Move to the next node in the result
            list1 = list1->child;
        }
        else{
            res->child = list2;
            res = list2;
            list2 = list2->child;
        }
        res->next = NULL; // Ensure the next pointer of the result node is NULL
    }

    // Connect the remaining
    // elements if any
    if(list1){
        res->child = list1;
    } else {
        res->child = list2;
    }

    // Break the last node's
    // link to prevent cycles
    if(dummyNode->child){
        dummyNode->child->next = NULL;
    }

    return dummyNode->child;
}

// Flattens a linked list with child pointers
Node* flattenLinkedList(Node* head){
    // If head is null or there 
    // is no next node, return head
    if(head == NULL || head->next == NULL){
        return head;
    }

    // Recursively flatten the
    // rest of the linked list
    Node* mergedHead = flattenLinkedList(head->next);
    head = merge(head, mergedHead);
    return head;
}

// Print the linked list by
// traversing through child pointers
void printLinkedList(Node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->child;
    }
    cout << endl;
}

// Print the linked list
// in a grid-like structure
void printOriginalLinkedList(Node* head, int depth) {
    while (head != nullptr) {
        cout << head->data;

        // If child exists, recursively
        // print it with indentation
        if (head->child) {
            cout << " -> ";
            printOriginalLinkedList(head->child, depth + 1);
        }

        // Add vertical bars
        // for each level in the grid
        if (head->next) {
            cout << endl;
            for (int i = 0; i < depth; ++i) {
                cout << "| ";
            }
        }
        head = head->next;
    }
}

int main() {
    // Create a linked list with child pointers
    Node* head = new Node(5);
    head->child = new Node(14);
    
    head->next = new Node(10);
    head->next->child = new Node(4);
    
    head->next->next = new Node(12);
    head->next->next->child = new Node(20);
    head->next->next->child->child = new Node(13);
    
    head->next->next->next = new Node(7);
    head->next->next->next->child = new Node(17);

    // Print the original
    // linked list structure
    cout << "Original linked list:" << endl;
    printOriginalLinkedList(head, 0);

    // Flatten the linked list
    // and print the flattened list
    Node* flattened = flattenLinkedList(head);
    cout << "\nFlattened linked list: ";
    printLinkedList(flattened);

    return 0;
}

