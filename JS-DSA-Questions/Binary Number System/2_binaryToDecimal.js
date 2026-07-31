// Write a code to convert a binary number to decimal number.

function binaryToDecimal(num) {
  let decimal = 0;
  let pow = 1;
  // Converting binary to decimal. Here `num` is a number whose digits are 0s and 1s (like 1101).
  // pow is used to store 2^i, where i starts from 0 and increases by 1 for each iteration.
  // Example: If we want to convert 1101 to decimal, we will get 13.
  // 1101 % 10 = 1, 1101 / 10 = 110, decimal = 0 + 1 * 1 = 1
  // 110 % 10 = 0, 110 / 10 = 11, decimal = 1 + 0 * 2 = 1
  // 11 % 10 = 1, 11 / 10 = 1, decimal = 1 + 1 * 4 = 5
  // 1 % 10 = 1, 1 / 10 = 0, decimal = 5 + 1 * 8 = 13
  // (In JavaScript the built-in way is `parseInt("1101", 2)`, but here we do it manually for learning.)
  while (num > 0) {
    const rem = num % 10;
    num = Math.floor(num / 10);
    decimal = decimal + rem * pow;
    pow = pow * 2;
  }
  return decimal;
}

const num = 1101;
console.log(`Decimal equivalent of ${num} is: ${binaryToDecimal(num)}`); // 13
