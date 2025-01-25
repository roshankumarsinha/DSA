// Write a Queue class that implements a queue using an array. The class should have the following functions:-
// push(int value) which adds an element to the end of the queue
// pop() which removes and logs the deleted element from the front of the queue and if queue is empty, logs "Queue Underflow!"
// isEmpty() which returns true if the queue is empty and false otherwise
// front() which returns the front element of the queue and if queue is empty, logs "Queue is empty!"

#include <iostream>
#define SIZE 5

using namespace std;

class Queue {
private:
    int arr[SIZE];
    int front, rear;

public:
    Queue() {
        front = rear = -1;
    }

    // Add element to the queue
    void enqueue(int value) {
        if (rear == SIZE - 1) {
            cout << "Queue Overflow!" << endl;
            return;
        }
        if (front == -1) front = 0; // Initialize front, if it's the first element
        rear = rear + 1;
        arr[rear] = value;
    }

    // Remove element from the queue
    void dequeue() {
        if (front == -1 || front > rear) {
            cout << "Queue Underflow!" << endl;
            return;
        }
        cout << "Dequeued: " << arr[front] << endl;
        if (front == rear) front = rear = -1; // Reset front and rear, if it's the last element
        else front = front + 1; // Move front to the next element
    }

    // Display front element
    void displayFront() {
        if (front == -1 || front > rear) {
            cout << "Queue is empty!" << endl;
        } else {
            cout << "Front: " << arr[front] << endl;
        }
    }

    // Check if the queue is empty
    bool isEmpty() {
        return front == -1 || front > rear;
    }
};

int main() {
    Queue q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    q.displayFront();
    q.dequeue();
    q.displayFront();

    q.dequeue();
    q.dequeue();
    q.dequeue(); // Queue underflow

    return 0;
}
