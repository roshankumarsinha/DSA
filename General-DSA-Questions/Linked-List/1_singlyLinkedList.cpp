// Implement Singly Linked List

#include<iostream>

using namespace std;

class Node {

    public:
        int data;
        Node* next;

    Node(int data) {
        this -> data = data;
        this -> next = nullptr;
    }
};

void insertAtBegining(int data, Node* &head) {
    Node* temp = new Node(data);
    temp -> next = head;
    head = temp;
}

void insertAtEnd(int data, Node* &tail) {
    Node* temp = new Node(data);
    tail -> next = temp;
    tail = temp;
}

void insertAtMiddle(int data, int position, Node* &head, Node* &tail) {
    if (position <= 0) {
        cout << "You entered wrong position value" << endl;
        return;
    }
    Node* temp = new Node(data);
    Node* temp1 = head;
    int count = 1;
    if (position == count) {
        temp -> next = head;
        head = temp;
        return;
    }
    while (count != position - 1 && temp1 != nullptr) {
        temp1 = temp1 -> next;
        count++;
    }
    if (temp1 == nullptr) {
        cout << "Position you mentioned is too large" << endl;
        return;
    } else if (temp1 == tail) {
        temp1 -> next = temp;
        tail = temp;
    } else {
        temp -> next = temp1 -> next;
        temp1 -> next = temp;
    }
}

void deleteAtBegining(Node* &head) {
    if (head == nullptr) {
        cout << "List is already Empty" << endl;
        return;
    }
    if (head -> next == nullptr) {
        head = nullptr;
        return;
    }
    Node* temp = head -> next;
    head -> next = nullptr;
    head = temp;
}

void deleteAtEnd(Node* &tail) {
    if (tail == nullptr) {
        cout << "List is already Empty" << endl;
        return;
    }
    if (tail -> next == nullptr) {
        tail = nullptr;
        return;
    }
}

void printList(Node* &head) {
    if (head == nullptr) {
        cout << "No data to print" << endl;
        return;
    }
    Node* temp = head;
    cout << "Data : ";
    while (temp != nullptr) {
        cout << temp -> data << " ";
        temp = temp -> next;
    }
    cout << endl;
}

int main() {

    Node* head = new Node(10);
    Node* tail = head;

    cout << "Head : " << head -> data << endl;
    cout << "Tail : " << tail -> data << endl;

    insertAtBegining(12, head);
    printList(head);
    insertAtBegining(15, head);
    printList(head);
    insertAtEnd(16, tail);
    printList(head);
    insertAtMiddle(11, 2, head, tail);
    printList(head);
    cout << "Head : " << head -> data << endl;
    cout << "Tail : " << tail -> data << endl;
    deleteAtBegining(head);
    printList(head);
    cout << "Head : " << head -> data << endl;
    cout << "Tail : " << tail -> data << endl;
    deleteAtBegining(head);
    printList(head);
    cout << "Head : " << head -> data << endl;
    cout << "Tail : " << tail -> data << endl;
    deleteAtBegining(head);
    printList(head);
    cout << "Head : " << head -> data << endl;
    cout << "Tail : " << tail -> data << endl;
    deleteAtBegining(head);
    printList(head);
    cout << "Head : " << head -> data << endl;
    cout << "Tail : " << tail -> data << endl;
    deleteAtBegining(head);
    printList(head);
    cout << "Head : " << head -> data << endl;
    cout << "Tail : " << tail -> data << endl;

    return 0;
}