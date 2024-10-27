// Write a function to calucate power(x,n) where x is a double and n is an integer.

#include <iostream>
using namespace std;

double power(double x, int n) {

    long binaryForm = n;
    double result = 1;

    if (binaryForm < 0) {
        binaryForm = -binaryForm;   // If n is negative, we will calculate 1/x^n
        x = 1/x;    // x = 1/x, because x^(-n) = 1/x^n
    }

    while (binaryForm > 0) {    // O(logn): We are calculating the power in binary form.
        if (binaryForm % 2 == 1) {
            result = result * x;
        }
        x = x * x; // x^2, x^4, x^8, x^16, x^32, x^64, x^128, x^256, x^512, x^1024
        binaryForm = binaryForm / 2;
    }

    return result;
}

int main() {
    double x = 3;
    int n = 13;
    cout << power(x, n) << endl;
    return 0;
}

// How does it work?
// Assume x = 3 and n = 13. We can write 13 as 1101 in binary form.
// So, 3^13 = 3^8 * 3^4 * 3^1
// 3^1 = 3
// 3^2 = 3*3 = 9
// 3^4 = 9*9 = 81
// 3^8 = 81*81 = 6561
// 3^13 = 6561 * 81 * 3 = 1594323