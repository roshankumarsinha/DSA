// Write a function to merge k sorted linked lists into a single sorted linked list.

// This is similar to merging k sorted arrays.

// Approach:
// 1. Use a min-heap that compares nodes based on their value.
// 2. Push the head of each linked list into the heap.
// 3. While the heap is not empty:
//    a.  Pop the smallest node.
//    b. Add it to the merged list.
//    c.  If the popped node has a next, push it into the heap.
// 4. Return the merged linked list.
// 5. Time Complexity: O(N log K)
//    a.  Where N = total number of nodes, K = number of lists
// 6. Space Complexity: O(K) for the heap

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Definition of a linked list node
class Node {
public:
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = nullptr;
    }
};

// Custom comparator for the min-heap
struct Compare {
    bool operator()(Node* a, Node* b) {
      // This says:
      //   Return true if a is greater than b.
      //   That tells the priority_queue that a should go after b.
      //   So, smaller values will come first, forming a min-heap.
        return a->data > b->data; // Compare based on node values
    }
};

// Function to merge k sorted linked lists into a single sorted linked list
Node* mergeKSortedLists(vector<Node*>& lists) {
    // priority_queue<Type, Container, Comparator> name;
    priority_queue<Node*, vector<Node*>, Compare> minHeap; // Min-heap to store the nodes

    // Push the head of each linked list into the min-heap
    for (Node* list : lists) {
        if (list != nullptr) {
            minHeap.push(list);
        }
    }

    Node* dummy = new Node(0); // Dummy node to simplify the merged list
    Node* tail = dummy; // Pointer to the last node in the merged list

    // While the min-heap is not empty
    while (!minHeap.empty()) {
        Node* current = minHeap.top(); // Get the smallest node
        minHeap.pop(); // Remove it from the heap

        tail->next = current; // Add it to the merged list
        tail = tail->next; // Move to the last node in the merged list

        // If there is a next node in the same linked list, push it into the min-heap
        if (current->next != nullptr) {
            minHeap.push(current->next);
        }
    }

    tail->next = nullptr; // Set the next of the last node to null

    return dummy->next; // Return the merged linked list (skipping the dummy node)
}

// Function to print the linked list
void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << "nullptr" << endl;
}

// Function to create list of k sorted linked lists
vector<Node*> createSortedLists() {
    vector<Node*> lists;

    // Create first sorted linked list: 1 -> 4 -> 7
    Node* list1 = new Node(1);
    list1->next = new Node(4);
    list1->next->next = new Node(7);
    lists.push_back(list1);

    // Create second sorted linked list: 2 -> 5 -> 8
    Node* list2 = new Node(2);
    list2->next = new Node(5);
    list2->next->next = new Node(8);
    lists.push_back(list2);

    // Create third sorted linked list: 3 -> 6 -> 9
    Node* list3 = new Node(3);
    list3->next = new Node(6);
    list3->next->next = new Node(9);
    lists.push_back(list3);

    return lists;
}

int main() {
    vector<Node*> lists = createSortedLists(); // Create k sorted linked lists

    Node* mergedList = mergeKSortedLists(lists); // Merge the k sorted linked lists

    cout << "Merged sorted linked list: ";
    printList(mergedList); // Print the merged linked list

    return 0;
}

// Output:
// Merged sorted linked list: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> nullptr
