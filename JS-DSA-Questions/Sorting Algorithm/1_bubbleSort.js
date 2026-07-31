// Write a function to sort an array using bubble sort.

function bubbleSort(num) {
  const length = num.length;
  for (let i = 0; i < length - 1; i++) {
    for (let j = 0; j < length - i - 1; j++) {
      if (num[j] > num[j + 1]) {
        // Swap adjacent elements using array destructuring (JavaScript idiom for std::swap).
        [num[j], num[j + 1]] = [num[j + 1], num[j]];
      }
    }
  }
}

const num = [64, 25, 12, 22, 11];
bubbleSort(num);
console.log(num.join(" "));

// Bubble Sort is the simplest sorting algorithm that works by repeatedly swapping the adjacent elements if they are in the wrong order. This algorithm is not suitable for large data sets as its average and worst-case time complexity are quite high.

// We sort the array using multiple passes. After the first pass, the maximum element goes to end (its correct position). Same way, after second pass, the second largest element goes to second last position and so on.
// In every pass, we process only those elements that have already not moved to correct position. After k passes, the largest k elements must have been moved to the last k positions.
// In a pass, we consider remaining elements and compare all adjacent and swap if larger element is before a smaller element. If we keep doing this, we get the largest (among the remaining elements) at its correct position.
// The time complexity of Bubble Sort is O(n^2) in all cases. It is not recommended for large datasets.
