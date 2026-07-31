// Write a function to find the sum of digits of a number

function sumOfDigits(num) {
  let sum = 0;
  while (num > 0) {
    // Extract the last digit by taking modulo 10, and remove the last digit by dividing by 10.
    // Note: JavaScript has no integer division, so we use Math.floor to drop the fractional part.
    const digit = num % 10;
    num = Math.floor(num / 10);
    sum += digit;
  }
  return sum;
}

// In C++ this read the number from `cin`. In Node.js you could read from stdin using the
// `readline` module, but for a self-contained example we just call the function with a sample value.
const num = 12345;
console.log("Sum of digits:", sumOfDigits(num)); // 15
