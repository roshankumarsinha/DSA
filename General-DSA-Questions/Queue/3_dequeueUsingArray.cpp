// Write a Dequeue class that implements a doubly ended queue using an array. The class should have the following functions:-
// insertFront(int value) which adds an element to the front of the dequeue
// insertRear(int value) which adds an element to the rear of the dequeue
// deleteFront() which removes and logs the deleted element from the front of the dequeue and if dequeue is empty, logs "Dequeue Underflow!"
// deleteRear() which removes and logs the deleted element from the rear of the dequeue and if dequeue is empty, logs "Dequeue Underflow!"
// getFront() which returns the front element of the dequeue and if dequeue is empty, logs "Dequeue is empty!"
// getRear() which returns the rear element of the dequeue and if dequeue is empty, logs "Dequeue is empty!"
// isFull() which returns true if the dequeue is full and false otherwise
// isEmpty() which returns true if the dequeue is empty and false otherwise




#include <iostream>
#define SIZE 5

using namespace std;

class Dequeue {
private:
    int arr[SIZE]; // Array to store elements
    int front, rear; // Indices for the front and rear

public:
    // Constructor to initialize the dequeue
    Dequeue() {
        front = rear = -1;
    }

    // Check if the dequeue is empty
    bool isEmpty() {
        return (front == -1);
    }

    // Check if the dequeue is full
    bool isFull() {
        return ((front == 0 && rear == SIZE - 1) || (rear + 1) % SIZE == front);
    }

    // Insert an element at the front
    void insertFront(int value) {
        if (isFull()) {
            cout << "Dequeue Overflow! Cannot insert " << value << " at the front." << endl;
            return;
        }

        // If dequeue is empty, and we are inserting the first element
        if (isEmpty()) {
            front = rear = 0;
        }
        // Wrap around if front is at the beginning
        else if (front == 0) {
            front = SIZE - 1;
        }
        // Normal case
        else {
            front--;
        }

        arr[front] = value;
    }

    // Insert an element at the rear
    void insertRear(int value) {
        if (isFull()) {
            cout << "Dequeue Overflow! Cannot insert " << value << " at the rear." << endl;
            return;
        }

        // If dequeue is empty, and we are inserting the first element
        if (isEmpty()) {
            front = rear = 0;
        }
        // Wrap around if rear is at the end
        else if (rear == SIZE - 1) {
            rear = 0;
        }
        // Normal case
        else {
            rear++;
        }

        arr[rear] = value;
    }

    // Delete an element from the front
    void deleteFront() {
        if (isEmpty()) {
            cout << "Dequeue Underflow! Cannot delete from the front." << endl;
            return;
        }

        cout << "Deleted from front: " << arr[front] << endl;

        // If there's only one element
        if (front == rear) {
            front = rear = -1;
        }
        // Wrap around if front is at the end
        else if (front == SIZE - 1) {
            front = 0;
        }
        // Normal case
        else {
            front++;
        }
    }

    // Delete an element from the rear
    void deleteRear() {
        if (isEmpty()) {
            cout << "Dequeue Underflow! Cannot delete from the rear." << endl;
            return;
        }

        cout << "Deleted from rear: " << arr[rear] << endl;

        // If there's only one element
        if (front == rear) {
            front = rear = -1;
        }
        // Wrap around if rear is at the beginning
        else if (rear == 0) {
            rear = SIZE - 1;
        }
        // Normal case
        else {
            rear--;
        }
    }

    // Get the element at the front
    void getFront() {
        if (isEmpty()) {
            cout << "Dequeue is empty!" << endl;
            return;
        }
        cout << "Front element: " << arr[front] << endl;
    }

    // Get the element at the rear
    void getRear() {
        if (isEmpty()) {
            cout << "Dequeue is empty!" << endl;
            return;
        }
        cout << "Rear element: " << arr[rear] << endl;
    }

    // Display all elements in the dequeue
    void display() {
        if (isEmpty()) {
            cout << "Dequeue is empty!" << endl;
            return;
        }

        cout << "Dequeue elements: ";
        int i = front;
        while (true) {
            cout << arr[i] << " ";
            if (i == rear) break;
            i = (i + 1) % SIZE;
        }
        cout << endl;
    }
};

int main() {
    Dequeue dq;

    dq.insertRear(10);
    dq.insertRear(20);
    dq.insertFront(5);
    dq.insertFront(1);
    dq.display();

    dq.getFront();
    dq.getRear();

    dq.deleteFront();
    dq.display();

    dq.deleteRear();
    dq.display();

    dq.insertRear(30);
    dq.insertRear(40);
    dq.insertFront(0); // Overflow example
    dq.display();

    return 0;
}
