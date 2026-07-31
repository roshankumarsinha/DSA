// Write a code to convert a decimal number to binary number.

// Video link : https://www.youtube.com/watch?v=xpy5NXiBFvA&list=PLfqMhTWNBTe137I_EPQd34TsgV6IO55pt&index=6

function decimalToBinary(num) {
  let binary = 0;
  let pow = 1;
  // Converting decimal to binary. If we need to store it as a number, we can use the following code:
  // pow is used to store 10^i, where i starts from 0 and increases by 1 for each iteration.
  // Example: If we want to convert 13 to binary, we will get 1101.
  // 13 % 2 = 1, 13 / 2 = 6, binary = 0 + 1 * 1 = 1
  // 6 % 2 = 0, 6 / 2 = 3, binary = 1 + 0 * 10 = 1
  // 3 % 2 = 1, 3 / 2 = 1, binary = 1 + 1 * 100 = 101
  // 1 % 2 = 1, 1 / 2 = 0, binary = 101 + 1 * 1000 = 1101

  // If we want to store the binary number as a string, then calculate the remainder and reverse the
  // string. That will be the binary number.
  // (In JavaScript the built-in way is `num.toString(2)`, but here we do it manually for learning.)
  while (num > 0) {
    const rem = num % 2;
    num = Math.floor(num / 2);
    binary = binary + rem * pow;
    pow = pow * 10;
  }
  return binary;
}

const num = 13;
console.log(`Binary equivalent of ${num} is: ${decimalToBinary(num)}`); // 1101
