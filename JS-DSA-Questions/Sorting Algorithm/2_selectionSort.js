// Write a function to sort an array using selection sort.

function selectionSort(num) {
  const length = num.length;
  for (let i = 0; i < length - 1; i++) {
    let minIndex = i;
    for (let j = i + 1; j < length; j++) {
      if (num[j] < num[minIndex]) {
        minIndex = j;
      }
    }
    // Swap the smallest found element into position i (JavaScript idiom for std::swap).
    [num[i], num[minIndex]] = [num[minIndex], num[i]];
  }
}

const num = [64, 25, 12, 22, 11];
selectionSort(num);
console.log(num.join(" "));

// Selection Sort is a comparison-based sorting algorithm. It sorts an array by repeatedly selecting the smallest (or largest) element from the unsorted portion and swapping it with the first unsorted element. This process continues until the entire array is sorted.

// First we find the smallest element and swap it with the first element. This way we get the smallest element at its correct position.
// Then we find the smallest among remaining elements (or second smallest) and move it to its correct position by swapping.
// We keep doing this until we get all elements moved to correct position.
// The time complexity of Selection Sort is O(n^2) in all cases. It is not recommended for large datasets.
// It is rarely used in practice because of its poor performance compared to other sorting algorithms like Quick Sort, Merge Sort, and Heap Sort.
