// Write a function to calucate power(x,n) where x is a double and n is an integer.

// Video link : https://www.youtube.com/watch?v=WBzZCm46mFo&list=PLfqMhTWNBTe137I_EPQd34TsgV6IO55pt&index=13

// Intuition:
// Any integer power n can be broken down using its binary representation.
// Any integer power n can be broken down using its binary representation because binary represents a number as a sum of powers of 2.
// Any integer n can be written in binary as:
//      n = (b_k * 2^k) + (b_(k-1) * 2^(k-1)) + ... + (b_1 * 2^1) + (b_0 * 2^0)
//      where b_i is either 0 or 1.
// Let's say :
//  1. x^n = x^2^0 * x^2^1 * x^2^2 * ... * x^2^k
// This means:
// Instead of multiplying x n times,
// We square the base repeatedly and multiply only when needed, based on the binary bits of n.

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
        if (binaryForm % 2 == 1) {  // If the last bit is 1, we multiply the result with x
            // Example: If n = 13, binaryForm = 1101, we will multiply result with x for the last bit.
            // 13 % 2 = 1, so we multiply result with x.
            // 13 / 2 = 6, so we will square x for the next iteration.
            // 6 % 2 = 0, so we will not multiply result with x.
            // 6 / 2 = 3, so we will square x for the next iteration.
            // 3 % 2 = 1, so we multiply result with x.
            // 3 / 2 = 1, so we will square x for the next iteration.
            // 1 % 2 = 1, so we multiply result with x.
            // 1 / 2 = 0, so we will exit the loop.
            // So, we will multiply result with x for the last bit.
            // In this case, we will multiply result with x for the first, third and fourth bits.
            // So, result = x^1 * x^3 * x^4 = x^(1+3+4) = x^8
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

// Time Complexity: O(log n) - We are dividing n by 2 in each iteration, so the number of iterations is logarithmic in relation to n.
// Space Complexity: O(1) - We are using a constant amount of space for the variables result, x, and binaryForm.

// How does it work?
// Assume x = 3 and n = 13. We can write 13 as 1101 in binary form.
// So, 3^13 = 3^8 * 3^4 * 3^1
// 3^1 = 3
// 3^2 = 3*3 = 9
// 3^4 = 9*9 = 81
// 3^8 = 81*81 = 6561
// 3^13 = 6561 * 81 * 3 = 1594323