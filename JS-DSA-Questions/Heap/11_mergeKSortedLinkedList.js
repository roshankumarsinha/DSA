// Merge k sorted linked lists into a single sorted linked list.

// Approach (Min-Heap):
// 1. Push the head node of each list into a min-heap ordered by node value.
// 2. Pop the smallest node, append it to the merged list, and push its next node (if any).
// 3. Repeat until the heap is empty.
// Time: O(N log K) (N total nodes, K lists). Space: O(K).

class Node {
  constructor(val) {
    this.data = val;
    this.next = null;
  }
}

// JavaScript note: C++ used a priority_queue with a custom Compare on Node*. Here we include a
// comparator-based MinHeap and order by node.data.
class MinHeap {
  constructor(compare) {
    this.a = [];
    this.compare = compare;
  }
  size() {
    return this.a.length;
  }
  push(v) {
    this.a.push(v);
    let i = this.a.length - 1;
    while (i > 0) {
      const p = Math.floor((i - 1) / 2);
      if (this.compare(this.a[p], this.a[i]) > 0) {
        [this.a[p], this.a[i]] = [this.a[i], this.a[p]];
        i = p;
      } else break;
    }
  }
  pop() {
    const top = this.a[0];
    const last = this.a.pop();
    if (this.a.length > 0) {
      this.a[0] = last;
      let i = 0;
      const n = this.a.length;
      while (true) {
        const l = 2 * i + 1;
        const r = 2 * i + 2;
        let s = i;
        if (l < n && this.compare(this.a[l], this.a[s]) < 0) s = l;
        if (r < n && this.compare(this.a[r], this.a[s]) < 0) s = r;
        if (s !== i) {
          [this.a[i], this.a[s]] = [this.a[s], this.a[i]];
          i = s;
        } else break;
      }
    }
    return top;
  }
}

function mergeKSortedLists(lists) {
  const minHeap = new MinHeap((x, y) => x.data - y.data);

  for (const list of lists) {
    if (list !== null) {
      minHeap.push(list);
    }
  }

  const dummy = new Node(0);
  let tail = dummy;

  while (minHeap.size() > 0) {
    const current = minHeap.pop();
    tail.next = current;
    tail = tail.next;

    if (current.next !== null) {
      minHeap.push(current.next);
    }
  }

  tail.next = null;
  return dummy.next;
}

function printList(head) {
  const out = [];
  while (head !== null) {
    out.push(head.data);
    head = head.next;
  }
  console.log(out.join(" -> ") + " -> null");
}

function createSortedLists() {
  const lists = [];
  const list1 = new Node(1);
  list1.next = new Node(4);
  list1.next.next = new Node(7);
  lists.push(list1);

  const list2 = new Node(2);
  list2.next = new Node(5);
  list2.next.next = new Node(8);
  lists.push(list2);

  const list3 = new Node(3);
  list3.next = new Node(6);
  list3.next.next = new Node(9);
  lists.push(list3);

  return lists;
}

const merged = mergeKSortedLists(createSortedLists());
process.stdout.write("Merged sorted linked list: ");
printList(merged); // 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> null
