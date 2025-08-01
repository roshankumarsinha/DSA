// Write a code to convert a binary number to decimal number.

#include <iostream>
using namespace std;

int binaryToDecimal(int num) {
    int decimal = 0, pow = 1;
    // Converting binary to decimal. If we need to store it into an integer, we can use the following code:
    // pow is used to store 2^i, where i starts from 0 and increases by 1 for each iteration.
    // Example: If we want to convert 1101 to decimal, we will get 13.
    // 1101 % 10 = 1, 1101 / 10 = 110, decimal = 0 + 1 * 1 = 1
    // 110 % 10 = 0, 110 / 10 = 11, decimal = 1 + 0 * 2 = 1
    // 11 % 10 = 1, 11 / 10 = 1, decimal = 1 + 1 * 4 = 5
    // 1 % 10 = 1, 1 / 10 = 0, decimal = 5 + 1 * 8 = 13
    while(num > 0) {
        int rem = num % 10;
        num /= 10;
        decimal = decimal + (rem * pow);
        pow = pow * 2;
    }
    return decimal;
}

int main() {
    int num;
    cout << "Enter a binary number: ";
    cin >> num;
    cout << "Decimal equivalent of " << num << " is: "<< binaryToDecimal(num) << endl;
    return 0;
}