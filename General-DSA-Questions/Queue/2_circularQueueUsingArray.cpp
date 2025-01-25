// Write a circluar queue using array.

#include <iostream>
#define SIZE 5

using namespace std;

class CircularQueue {
private:
    int arr[SIZE];
    int front, rear;

public:
    CircularQueue() {
        front = rear = -1;
    }

    // Add an element to the queue
    void enqueue(int value) {
      // The % SIZE (modulo operation) in (rear + 1) % SIZE == front is necessary to implement the circular behavior of the queue.
      // Without the modulo operation, the queue would not "wrap around" when rear reaches the end of the array, effectively breaking the concept of a circular queue.
        if ((rear + 1) % SIZE == front) {
            cout << "Queue Overflow! Cannot insert " << value << endl;
            return;
        }
        if (front == -1) front = 0; // Initialize front if it's the first element
        rear = (rear + 1) % SIZE;
        arr[rear] = value;
    }

    // Remove an element from the queue
    void dequeue() {
        if (front == -1) {
            cout << "Queue Underflow! Cannot dequeue" << endl;
            return;
        }
        cout << "Dequeued: " << arr[front] << endl;
        if (front == rear) {  // Single element in the queue
            // Queue becomes empty
            front = rear = -1;
        } else {
            front = (front + 1) % SIZE;
        }
    }

    // Display front element
    void displayFront() {
        if (front == -1) {
            cout << "Queue is empty!" << endl;
        } else {
            cout << "Front: " << arr[front] << endl;
        }
    }

    // Display all elements in the queue
    void displayQueue() {
        if (front == -1) {
            cout << "Queue is empty!" << endl;
            return;
        }
        cout << "Queue elements are: ";
        int i = front;
        while (true) {
            cout << arr[i] << " ";
            if (i == rear) break;
            i = (i + 1) % SIZE;
        }
        cout << endl;
    }

    // Check if the queue is empty
    bool isEmpty() {
        return front == -1;
    }

    // Check if the queue is full
    bool isFull() {
        return (rear + 1) % SIZE == front;
    }
};

int main() {
    CircularQueue q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.enqueue(50); // This will cause overflow

    q.displayQueue();
    q.displayFront();

    q.dequeue();
    q.displayQueue();

    q.enqueue(50); // Now this should be possible
    q.displayQueue();

    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue(); // This will cause underflow

    return 0;
}
