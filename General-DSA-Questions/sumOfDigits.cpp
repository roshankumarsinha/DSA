// wite a function to find the sum of digits of a number

#include <iostream>
using namespace std;

int sumOfDigits(int num) {
    int sum = 0;
    while (num > 0) {
        // Extract the last digit by taking modulo 10, and remove the last digit by dividing by 10
        int digit = num % 10;
        num /= 10;
        sum += digit;
    }
    return sum;
}

int main() {
    int num;
    cout << "Enter a number: ";
    cin >> num;
    cout << "Sum of digits: "<< sumOfDigits(num) << endl;
    return 0;
}