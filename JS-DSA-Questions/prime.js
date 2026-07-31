// Check if a number is prime or not

function isPrime(num) {
  if (num <= 1) {
    return false;
  }
  if (num <= 3 && num > 1) {
    return true;
  }
  // We are checking till the square root of the number.
  // If a number is not prime, it can be factored into two factors, a and b.
  // If both a and b were greater than the square root of n, a*b would be greater than n.
  // So at least one of those factors must be less than or equal to the square root of n, and to
  // check if n is prime, we only need to test for factors less than or equal to the square root.
  // Time complexity: O(sqrt(n))
  for (let i = 2; i * i <= num; i++) {
    if (num % i === 0) {
      return false;
    }
  }
  return true;
}

// In C++ this read the number from `cin`. Here we just test with sample values.
const num = 29;
console.log(isPrime(num) ? "prime number" : "not a prime number");
