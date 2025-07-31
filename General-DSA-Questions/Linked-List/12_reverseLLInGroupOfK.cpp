// Write a function to reverse a linked list with a given group size k.

// If the Linked List is: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10
// and k = 3, the output should be: 3 -> 2 -> 1 -> 6 -> 5 -> 4 -> 9 -> 8 -> 7 -> 10

// Notes : https://takeuforward.org/data-structure/reverse-linked-list-in-groups-of-size-k/

// Intiution without recursion:
// The approach simplifies reversing linked list nodes by breaking the list into segments of K nodes and reversing each segment individually.
// Starting from the head, the algorithm traverses the list to identify segments of K nodes.
// Upon finding a segment, it reverses it, returning the modified list. If a segment has less than K nodes left (ie. remaining nodes at the end), they are left unaltered. 



#include <iostream>

using namespace std;

// Node class represents a
// node in a linked list
class Node {
public:
    // Data stored in the node
    int data;   
    
    // Pointer to the next node in the list
    Node* next;      

    // Constructor with both data and
    // next node as parameters
    Node(int data1, Node* next1) {
        data = data1;
        next = next1;
    }

    // Constructor with only data as a
    // parameter, sets next to nullptr
    Node(int data1) {
        data = data1;
        next = nullptr;
    }
};

// This function has been explained
// in previous videos/articles

// Function to reverse a linked list
// using the 3-pointer approach
Node* reverseLinkedList(Node *head)
{
   // Initialize'temp' at
   // head of linked list
   Node* temp = head;  
   
   // Initialize pointer 'prev' to NULL,
   // representing the previous node
   Node* prev = NULL;  
   
   // Traverse the list, continue till
   // 'temp' reaches the end (NULL)
   while(temp != NULL){  
       // Store the next node in
       // 'front' to preserve the reference
       Node* front = temp->next;  
       
       // Reverse the direction of the
       // current node's 'next' pointer
       // to point to 'prev'
       temp->next = prev;  
       
        // Move 'prev' to the current
        // node for the next iteration
       prev = temp;  
       
        // Move 'temp' to the 'front' node
        // advancing the traversal
       temp = front; 
   }
   
   // Return the new head of
   // the reversed linked list
   return prev;  
}

// Function to get the Kth node from
// a given position in the linked list
Node* getKthNode(Node* temp, int k){
    // Decrement K as we already
    // start from the 1st node
    k -= 1; 

    // Decrement K until it reaches
    // the desired position
    while(temp != NULL && k > 0){
        // Decrement k as temp progresses
        k--; 
        
        // Move to the next node
        temp = temp -> next; 
    }
    
    // Return the Kth node
    return temp; 
}

// Function to reverse nodes in groups of K
Node* kReverse(Node* head, int k){
    // Initialize a temporary
    // node to traverse the list
    Node* temp = head; 

    // Initialize a pointer to track the last node of previous group, this will be used to link the current group to the previous one
    // after reversal
    // Initially, there is no previous group, so set it to NULL
    Node* prevLast = NULL; 
    
    // Traverse through the linked list
    while(temp != NULL){
        // Get the Kth node of the current group
        // This function returns the Kth node from the current position
        // If Kth node is NULL, it means the group is not complete
        // and we should not reverse it, it will return NULL
        // If Kth node is not NULL, we will reverse the nodes from temp to Kth node
        // and link it to the previous group
        Node* kThNode = getKthNode(temp, k); 

        // If the Kth node is NULL
        // (not a complete group)
        if(kThNode == NULL){
            // If there was a previous group,
            // link the last node to the current node
            if(prevLast){
                prevLast -> next = temp;  // Link Previous group to the current group
            }
            
            // Exit the loop
            break; 
        }
        
        // Store the next node
        // after the Kth node
        Node* nextNode = kThNode -> next; // Store the next node so that we can continue traversing the list after reversing the current group

        // Disconnect the Kth node
        // to prepare for reversal
        kThNode -> next = NULL; 

        // Reverse the nodes from
        // temp to the Kth node
        // The reversed linked list segment returns a modified list with `temp` now at its tail  and the `KthNode` pointing to its head.
        reverseLinkedList(temp); 
        
        // Adjust the head if the reversal
        // starts from the head
        if(temp == head){
            head = kThNode;
        }else{
            // Link the last node of the previous
            // group to the reversed group
            prevLast -> next = kThNode; 
        }

        // Update the pointer to the
        // last node of the previous group
        prevLast = temp; 

        // Move to the next group
        temp = nextNode; 
    }
    
    // Return the head of the
    // modified linked list
    return head; 
}

// Function to print the linked list
void printLinkedList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    // Create a linked list with
    // values 5, 4, 3, 7, 9 and 2
    Node* head = new Node(5);
    head->next = new Node(4);
    head->next->next = new Node(3);
    head->next->next->next = new Node(7);
    head->next->next->next->next = new Node(9);
    head->next->next->next->next->next = new Node(2);

    // Print the original linked list
    cout << "Original Linked List: ";
    printLinkedList(head);

    // Reverse the linked list
    head = kReverse(head, 4);

    // Print the reversed linked list
    cout << "Reversed Linked List: ";
    printLinkedList(head);

    return 0;
}