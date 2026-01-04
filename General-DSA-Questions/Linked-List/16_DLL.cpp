// Notes are :-

// 1. https://takeuforward.org/linked-list/introduction-to-doubly-linked-list
// 2. Inserting into DLL : https://takeuforward.org/data-structure/insert-at-end-of-doubly-linked-list/
// 3. Deleting from DLL : https://takeuforward.org/data-structure/delete-last-node-of-a-doubly-linked-list/


// We have a question for Design Browser History, which is implemented using a doubly linked list. Video Link : https://www.youtube.com/watch?v=mG3KLugbOdc

// Question : Design Browser History
// Problem Statement: You have a browser of one tab where you start on the homepage and you can visit another url,
// get back in the history number of steps or move forward in the history number of steps.

// Example:
// Input:
// homepage = "leetcode.com", BrowserHistory = ["leetcode.com"], current = "leetcode.com"
// visit("google.com"), BrowserHistory = ["leetcode.com", "google.com"], current = "google.com"
// visit("facebook.com"), BrowserHistory = ["leetcode.com", "google.com", "facebook.com"], current = "facebook.com"
// visit("youtube.com"), BrowserHistory = ["leetcode.com", "google.com", "facebook.com", "youtube.com"], current = "youtube.com"
// back(1) -> returns "facebook.com", BrowserHistory = ["leetcode.com", "google.com", "facebook.com", "youtube.com"], current = "facebook.com"
// back(1) -> returns "google.com", BrowserHistory = ["leetcode.com", "google.com", "facebook.com", "youtube.com"], current = "google.com"
// forward(1) -> returns "facebook.com", BrowserHistory = ["leetcode.com", "google.com", "facebook.com", "youtube.com"], current = "facebook.com"
// visit("linkedin.com"), BrowserHistory = ["leetcode.com", "google.com", "facebook.com", "linkedin.com"], current = "linkedin.com", so we delete all the forward history after "facebook.com"
// forward(2) -> returns "linkedin.com", BrowserHistory = ["leetcode.com", "google.com", "facebook.com", "linkedin.com"], current = "linkedin.com"
// back(2) -> returns "google.com", BrowserHistory = ["leetcode.com", "google.com", "facebook.com", "linkedin.com"], current = "google.com"
// back(7) -> returns "leetcode.com", BrowserHistory = ["leetcode.com", "google.com", "facebook.com", "linkedin.com"], current = "leetcode.com"

// Intuition:
// 1. Use a doubly linked list to represent the browser history. Reason being we can move both forward and backward and dynamically add new pages.
// 2. Each node in the doubly linked list will represent a webpage with a URL.
// 3. Maintain a pointer to the current page in the history. This pointer will help in navigating back and forth.
// 4. When visiting a new URL, create a new node and adjust the pointers accordingly.
// 5. For back and forward operations, move the current pointer the required number of steps while ensuring it doesn't go out of bounds.


#include <iostream>
#include <string>
using namespace std;

class Node {
    public:
        string url; // URL of the webpage
        Node* prev; // Pointer to the previous node
        Node* next; // Pointer to the next node

        // Constructor for Node, initially prev and next are set to nullptr and url is set to the given value
        Node(string _url) {
            url = _url;
            prev = nullptr;
            next = nullptr;
        }
};

class BrowserHistory {
    private:
        Node* head; // Pointer to the head of the doubly linked list
        Node* current; // Pointer to the current page in the history

    public:
        // Constructor to initialize the browser history with the homepage
        BrowserHistory(string homepage) {
            head = new Node(homepage); // Create a new node for the homepage
            current = head; // Set current to head
        }

        // Function to visit a new URL
        void visit(string url) {
            Node* newNode = new Node(url); // Create a new node for the new URL
            current->next = newNode; // Link current's next to the new node
            newNode->prev = current; // Link new node's prev to current
            current = newNode; // Move current to the new node
        }

        // Function to go back in history by 'steps' number of pages
        string back(int steps) {
            // Move back 'steps' times or until we reach the beginning of the history
            while (steps > 0 && current->prev != nullptr) {
                current = current->prev; // Move current back
                steps--;
            }
            return current->url; // Return the URL of the current page
        }

        // Function to go forward in history by 'steps' number of pages
        string forward(int steps) {
            // Move forward 'steps' times or until we reach the end of the history
            while (steps > 0 && current->next != nullptr) {
                current = current->next; // Move current forward
                steps--;
            }
            return current->url; // Return the URL of the current page
        }
};

int main() {
    BrowserHistory browserHistory("leetcode.com"); // Initialize browser history with homepage

    browserHistory.visit("google.com"); // Visit google.com
    browserHistory.visit("facebook.com"); // Visit facebook.com
    browserHistory.visit("youtube.com"); // Visit youtube.com

    cout << browserHistory.back(1) << endl; // Go back 1 step, should return "facebook.com"
    cout << browserHistory.back(1) << endl; // Go back 1 step, should return "google.com"
    cout << browserHistory.forward(1) << endl; // Go forward 1 step, should return "facebook.com"

    browserHistory.visit("linkedin.com"); // Visit linkedin.com

    cout << browserHistory.forward(2) << endl; // Go forward 2 steps, should return "linkedin.com"
    cout << browserHistory.back(2) << endl; // Go back 2 steps, should return "google.com"
    cout << browserHistory.back(7) << endl; // Go back 7 steps, should return "leetcode.com"

    return 0;
}