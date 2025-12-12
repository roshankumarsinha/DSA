// Check if a number is prime or not

#include <iostream>
using namespace std;

int main() {
    int num;
    cout << "Enter a number: ";
    cin >> num;
    if (num <= 1) {
        cout << "not a prime number" << endl;
        return 0;
    }
    if (num <= 3 && num > 1) {
        cout << "prime number" << endl;
        return 0;
    }
    bool isPrime = true;
    // We are checking till the square root of the number.
    // If a number is not prime, it can be factored into two factors, a and b.
    // If both a and b were greater than the square root of n, a*b would be greater than n.
    // So at least one of those factors must be less than or equal to the square root of n, and to check if n is prime, we only need to test for factors less than or equal to the square root.
    // Time complexity: O(sqrt(n)) 
    for (int i=2; i*i<=num; i++) {
        if (num % i == 0) {
            cout << "not a prime number" << endl;
            return 0;
        }
    }
    cout << "prime number" << endl;
}