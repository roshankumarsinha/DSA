<h1>Data-Types</h1>
    <ol>
        <li>int => 4 Bytes (32 bits). Each number is converted to it's binary form and stored in int variable.
            <ul>
                <li>signed int => 4 Bytes. It's same as int. (2^31 and 1 bit is used for cheching either +ve or -ve. 0 for +ve and 1 for -ve)</li>
                <li>unsigned int => 4 Bytes. It's same as int but it can store only positive value. (2^32 all 32 bits are used)</li>
                <li>short int => 2 Bytes. This is used to store less value. (2^15 and 1 bit is used for checking either +ve or -ve)</li>
                <li>unsigned short int => 2 Bytes. (2^16)</li>
                <li>long long int => 8 Bytes. (2^63 and 1 bit is used for checking either +ve or -ve)</li>
                <li>unsigned long long int => 8 Bytes. (2^64)</li>
            </ul>
        </li>
        <li>char => 1 Byte (8 bits). Each character is first converted to ASCII value and than the binary form of ASCII value is stored in char variable</li>
        <li>float => 4 Byte (32 bits). To store decimal value. To store floating value we add 'f' in the end. EX: float PI = 3.14f . By default it's double if we don't add 'f'.</li>
        <li>bool => 1 Byte (8 bits). To store true or false. Each value is converted to 0 or 1 and than these value are converted to binary form and stored in bool variable.</li>
        <li>double => 8 byte (32 bits). To </li>
    </ol>
<h1>Type-Conversion vs Type-Casting</h1>
    <ol>
        <li>Type-Conversion => It's done by compiler. It's automatic. Generally smaller data type is converted to large data type automatically. Ex: char a = 'A'; int value = a; // Here we converted char(smaller) to int(bigger) data type. Output will be ASCII value of 'A' which is 65</li>
        <li>Type-Casting => It's done by programmer. It's manual. Generally it is used to convert large data type to small data type. EX: double a = 10.99; int b = (int)a; // Here programmer is converting double to int manually. Output will be 10</li>
    </ol>
    <h1>Operators</h1>
    <ol>
        <li>Arithmetic Operators => +, -, *, /, % (Keep in mind if one of the operand is of bigger data type than result will be of that data type. EX: 5/(double)2. Ans will be 2.5 which will be of souble type)</li>
        <li>Relational Operators(It returns boolean value) => ==, !=, >, <, >=, <o=</li>
        <li>Logical Operators => &&, ||, !</li>
        <li>Increment/Decrement(Unary) Operators => ++, --</li>
    </ol>
<h1>To Execute C++ code in VS code use <pre><code>g++ filename.cpp && ./a.out</code></pre></h1>
<h1>Tips to solve Pattern Problems :-</h1>
    <ol>
        <li>Always try to solve pattern problems by breaking it into smaller parts.</li>
        <li><b>Identify rows and columns: </b>Most pattern problems can be broken down into a series of rows and columns.</li>
        <li><b>Identify the relationship between rows and columns: </b>Try to identify the relationship between rows and columns. This will help you to understand how the pattern is formed.</li>
        <li><b>Manage Spaces: </b>If there are character after spaces than write one loop for spaces and one loop for characters</li>
</ol>
<h1>Two's complement</h1>
    <ol>
        <li>It's a way to represent negative number in binary form.</li>
        <li>First convert the number to binary form.</li>
        <li>Prefix with a 0(at MSB position). This will tell the sign bit</li>
        <li>Than take 1's complement of the number. (0 will be converted to 1 and 1 will be converted to 0)</li>
        <li>Than add 1 to the 1's complement number.</li>
        <li>Than convert the number to decimal form.</li>
    </ol>
<h1>Bitwise Operators</h1>
    <ol>
        <li>Bitwise AND => (&) It's completely similar to AND operator. The result is 1 if both bits are 1; otherwise, it's 0. Example: 5(101) & 3(011) = 1(001) </li>
        <li>Bitwise OR => (|) It's completely similar to AND operator. The result is 1 if at least one of the bits is 1; otherwise, it's 0. Example: 5(101) | 3(011) = 7(111) </li>
        <li>Bitwise XOR => (^) The result is 1 if the bits are different; otherwise, it's 0. Example : 5(101) ^ 3(011) = 6(110) </li>
        <li>Bitwise NOT => (~) Inverts the bits of the number (turns 0 into 1 and 1 into 0). Example : ~5(0000 0101) = -6(1111 1010). ~(+ve num) = (-ve num+1) </li>
        <li>Left Shift => (<<) Shifts the bits of the number to the left by a specified number of positions. Each left shift by 1 is equivalent to multiplying the number by 2. Example: 5(0000 0101) << 1 = 10(0000 1010) </li>
        <li>Right Shift => (>>) Shifts the bits of the number to the right by a specified number of positions. Each right shift by 1 is equivalent to dividing the number by 2. Example: 5(0000 0101) >> 1 = 2(0000 0010) </li>
        <li>Some Tips regarding bit manipulation:-
            <ol>
                <li><b>Bit Masking:</b>Bitwise operators are commonly used to manipulate specific bits in a number, also known as bit masking.Example: To check if the 3rd bit (from the right) of a number is 1:
<pre><code>
int num = 5;   // 0101 in binary
int mask = 4;  // Create a mask where only the 3rd bit is 1 (0100)
if (num & mask) {
    cout << "3rd bit is set." << endl;
} else {
    cout << "3rd bit is not set." << endl;
}
</code></pre>
                </li>
                <li><b>Swapping Numbers:</b>XOR can be used to swap two numbers without using a temporary variable:
<pre><code>
int a = 5, b = 3;
a = a ^ b;  // a becomes 6 (5 ^ 3)
b = a ^ b;  // b becomes 5 (6 ^ 3)
a = a ^ b;  // a becomes 3 (6 ^ 5)
// Now a = 3, b = 5
</code></pre>
                </li>
                <li><b>Checking if a Number is Even or Odd:</b>Use bitwise AND with 1 to check if the least significant bit is 1 (odd) or 0 (even):
<pre><code>
if (num & 1) {
    cout << "Odd" << endl;
} else {
    cout << "Even" << endl;
}               
</code></pre>
                </li>
                <li><b>Efficient Multiplication/Division by Powers of 2:</b>You can multiply a number by 2^k using a left shift (<< k) and divide it by 2^k using a right shift (>> k):
<pre><code>
int x = 4;
int multiply = x << 3;  // Equivalent to 4 * 2^3 = 32
int divide = x >> 1;    // Equivalent to 4 / 2^1 = 2
</code></pre>
                </li>
            </ol>
        </li>
        <h1>Some basic Knowledge :</h1>
        <ol>
            <li>+ve Infinity is denoted by INT_MAX and -ve Infinity is denoted by INT_MIN</li>
            <li>If you want to calculate length of array than, sizeof(arrayName) / sizeof(int)</li>
            <li>We can't perform any operations on Array</li>
            <li>Arrays are automatically passed by reference by default</li>
        </ol>
        <h1>Knowledge on Vectors :</h1>
        <ol>
            <li>Vector is included using a header
                <pre><code>#include <,vector,>  //You can ignore the ,,</code></pre>
            </li>
            <li>vector is Declared using :
                <pre><code>
                    vector<int> v; // This will create a vector of int type
                    vector<int> v(5); // This will create a vector of int type with size 5
                    vector<int> v(5, 10); // This will create a vector of int type with size 5 and all elements will be 10
                    vector<int> v{1, 2, 3, 4, 5}; // This will create a vector of int type with size 5 and elements will be 1, 2, 3, 4, 5
                </code></pre>
            </li>
            <li>You can loop vector with iterator also:
                <pre><code>
                    vector<int> v{1, 2, 3, 4, 5};
                    for (int value: v) {
                        cout << value << " ";   // Output will be 1 2 3 4 5, where value will be v[0], v[1], v[2], v[3], v[4]
                    }
                </code></pre>
            </li>
            <li>Some Functions related to vector :
                <pre><code>
                    vector<int> v{1, 2, 3, 4, 5};
                    v.push_back(6); // This will add 6 at the end of vector
                    v.pop_back(); // This will remove last element from vector
                    v.size(); // This will return size of vector. The number of elements currently stored in the vector.
                    v.empty(); // This will return true if vector is empty else false
                    v.clear(); // This will remove all elements from vector
                    v.front(); // This will return first element of vector
                    v.back(); // This will return last element of vector
                    v.at(2); // This will return element at index 2
                    v.insert(v.begin() + 2, 10); // This will insert 10 at index 2
                    v.erase(v.begin() + 2); // This will remove element at index 2
                    v.erase(v.begin() + 2, v.begin() + 4); // This will remove elements from index 2 to 4
                    v.resize(10); // This will resize vector to 10
                    v.resize(10, 5); // This will resize vector to 10 and all elements will be 5
                    v.capacity(); // The total amount of memory allocated, which may be more than the number of elements.
                </code></pre>
            </li>
            <li>Use <b>g++ -std=c++11 test.cpp && ./a.out</b> command if it uses stl library</li>
            <li>Array has static allocation, which means it is created at complile time, where vector has dynamic allocation , which means it is created at run time.</li>
            <li>Static allocation is done in stack memory, where dynamic allocation is done in heap memory.</li>
            <li><b>How vector gets memory :</b> When we create a vector, it will allocate some memory. If we add more elements than it's capacity than it will double the memory and copy all elements to new memory and delete old memory. A vector stores its elements in contiguous memory locations, similar to arrays. This allows direct access to elements using an index.</li>
        </ol>
        <h1>Pointers :</h1>
        <ol>
            <li>Memory Address is represented in hexadecimal form</li>
            <li>We can print address of any variable using Address of Operator (&). Example:
                <pre><code>
                    int a = 10;
                    cout << &a; // This will print address of a
                </code></pre>
            </li>
            <li>Pointers are used to store memory address</li>
            <li>We can print address of any variable using Address of Operator (&). Example:
                <pre><code>
                    int a = 10;
                    cout << &a; // This will print address of a
                </code></pre>
            </li>
            <li>Pointer is declared using (*). Example:
                <pre><code>
                    int a = 10;
                    int* p = &a; // This will create a pointer p which will store address of a
                    cout << p; // This will print address of a
                    cout << &a: // This will print address of a. It will be same as p
                </code></pre>
            </li>
            <li>We are defining type for pointer because, when address is created along with it some meta-deta is also created like how much bytes are used and for that we need to assign type for pointers.</li>
            <li>We can make pointer to pointer, which stores address of pointer. Example:
                <pre><code>
                    int a = 10;
                    int* p = &a;
                    int** q = &p; // This will create a pointer q which will store address of p. This is called pointer to pointer
                    cout << q; // This will print address of p
                    cout << &p: // This will print address of p. It will be same as q
                </code></pre>
            </li>
            <li>We have dereferencing operator (*), which is used to give value inside a memory address. Example:
                <pre><code>
                    int a = 10;
                    int* p = &a;
                    cout << *p; // This will print value of a
                    cout << *(&a); // This will print value of a. It will be same as *p
                </code></pre>
            </li>
            <li><b>Null Pointer :</b>It's a pointer which is not pointing to any memory address, it doesn't point to any valid memory location. You can't dereferenced a null pointer, since it doesn't point to any valid address. Example:
                <pre><code>
                    int* p = nullptr; // This will create a null pointer
                </code></pre>
            </li>
            <li>Pass by reference is done in 2 ways :
                <ol>
                    <li>Using Pointers:
                        <pre><code>
                            void increment(int* p) {
                                *p = *p + 1;
                            }
                            int main() {
                                int a = 10;
                                increment(&a);
                                cout << a; // This will print 11
                            }
                        </code></pre>
                    </li>
                    <li>Using Reference Variable:
                        <pre><code>
                            void increment(int &p) {    // Here & is used to pass by reference, it creates an alias for the variable
                                p = p + 1;
                            }
                            int main() {
                                int a = 10;
                                increment(a);
                                cout << a; // This will print 11
                            }
                        </code></pre>
                    </li>
                </ol>
            </li>
            <li>When we create an array, the array is stored as pointer. Example:
                <pre><code>
                    int a[5] = {1, 2, 3, 4, 5};
                    cout << a; // This will print address of a and it is called array pointer. Array pointer is a pointer which stores address of first element of array and it is a constant pointer
                </code></pre>
            </li>
            <li>Pointer Arithmetic:
                <ol>
                    <li>When we add 1 to pointer than it will move to next memory location. Example:
                        <pre><code>
                            int a = 10;
                            int* p = &a;
                            cout << p; // This will print address of a. If address of a is 1000 than it will print 1000
                            p = p + 1; // This will move pointer to next memory location, and increment pointer by 4 bytes because it's int pointer
                            cout << p; // This will print address of next memory location. If address of a is 1000 than it will print 1004. Same goes for subtraction as well
                        </code></pre>
                    </li>
                    <li>When we subtract 2 pointers than it will give difference between 2 pointers. Example:
                        <pre><code>
                            int a = 10; // Assume address of a is 1000
                            int b = 20; // Assume address of b is 1004
                            int* p = &a;
                            int* q = &b;
                            cout << q - p; // This will print 1. It will give difference between 2 pointers. If p is at 1000 and q is at 1004 than difference will be 1(which is 4 bytes)
                        </code></pre>
                    </li>
                    <li>Addition of 2 pointers is not allowed</li>
                </ol>
            </li>
        </ol>
         <h1>Double Ended Queue :</h1>
        <ol>
            <li>Double-ended queues are sequence containers with the feature of expansion and contraction on both ends. They are similar to vectors, but are more efficient in case of insertion and deletion of elements. Unlike vectors, contiguous storage allocation may not be guaranteed.</li>
            <li>The functions for deque are same as vector, with an addition of push and pop operations for both front and back.</li>
            <li>Time Complexity for doing various operations on deques are :-
                <ul>
                    <li>Insertion or Deletion at front/back - O(1)</li>
                    <li>Insertion/Deletion in middle - O(n)</li>
                    <li>Accessing element - O(1)</li>
                </ul>
            </li>
            <li>Various methods for deque :-
                <ul>
                    <li>push_front() - This will add element at front</li>
                    <li>push_back() - This will add element at back</li>
                    <li>pop_front() - This will remove element from front</li>
                    <li>pop_back() - This will remove element from back</li>
                    <li>front() - This will return first element</li>
                    <li>back() - This will return last element</li>
                    <li>size() - This will return size of deque</li>
                    <li>empty() - This will return true if deque is empty else false</li>
                    <li>clear() - This will remove all elements from deque</li>
                </ul>
                <pre>
                    <code>
                        #include <.deque.>    // Include deque header. Dot is added just to render it on Markdown
                        deque<.int.> dq = {1, 2, 3, 4, 5};    // Create a deque
                        for (int i = 0; i < dq.size(); i++) {
                            dq[i] = dq[i] + 1;    // Increment each element by 1
                            cout << dq[i] << " ";    // Output will be 2 3 4 5 6
                        }
                    </code>
                </pre>
            </li>
        </ol>
        <h1>List :-</h1>
        <ol>
            <li>Lists are sequence containers that allow non-contiguous memory allocation. As compared to the vector, the list has slow traversal, but once a position has been found, insertion and deletion are quick (constant time).</li>
            <li>List is nothing but a doubly linked list.</li>
            <li>Unlike vectors, a list does not support random access, meaning you cannot directly jump to a specific index, or access elements by index numbers.</li>
            <li>Time Complexity for doing various operations on List are :-
                <ul>
                    <li>Insertion or Deletion at front/back - O(1)</li>
                    <li>Insertion/Deletion in middle - O(1). Since it is kind of doubly linked list, but keep in mind if you need to traverse to that element than it becomes O(N)</li>
                    <li>Accessing element - O(n). Because you need to traverse whole list</li>
                </ul>
            </li>
            <li>Various methods for list :-
                <ul>
                    <li>push_front() - This will add element at front</li>
                    <li>push_back() - This will add element at back</li>
                    <li>pop_front() - This will remove element from front</li>
                    <li>pop_back() - This will remove element from back</li>
                    <li>front() - This will return first element</li>
                    <li>back() - This will return last element</li>
                    <li>size() - This will return size of list</li>
                    <li>empty() - This will return true if list is empty else false</li>
                    <li>clear() - This will remove all elements from list</li>
                    <li>erase() - This will remove element at specific position</li>
                    <li>remove() - This will remove all elements with specific value</li>
                    <li>reverse() - This will reverse the list</li>
                    <li>sort() - This will sort the list</li>
                    <li>
                        insert() - This will insert element at specific position. It takes 2 arguments, first is iterator and second is value. Example:
                        <pre>
                            <code>
                                #include <.list.>    // Include list header
                                list<.int.> l = {1, 2, 3, 4, 5};    // Create a list
                                l.insert(l.begin(), 10);    // Insert 10 at beginning
                                for(auto i = l.begin(); i != l.end(); i++) {
                                    cout << *i << " ";    // Output will be 10 1 2 3 4 5
                                }
                            </code>
                        </pre>
                    </li>
                </ul>
                <pre>
                    <code>
                        #include <.list.>    // Include list header
                        list<.int.> l = {1, 2, 3, 4, 5};    // Create a list
                        for(auto i = l.begin(); i != l.end(); i++) {    // You can't use traditional for loop, as list doesn't support random access like vector. You can use for each loop also
                            *i = *i + 1;    // Increment each element by 1
                            cout << *i << " ";    // Output will be 2 3 4 5 6
                        }
                    </code>
                </pre>
            </li>
        </ol>
        <h1>Stack :-</h1>
        <li>Unlike vectors, elements in the stack are not accessed by index numbers. Since elements are added and removed from the top, you can only access the element at the top of the stack.</li>
        <li>Various methods for stack :-
            <ul>
                <li>push() - This will add element at top</li>
                <li>pop() - This will remove element from top</li>
                <li>top() - This will return top element</li>
                <li>size() - This will return size of stack</li>
                <li>empty() - This will return true if stack is empty else false</li>
            </ul>
            <pre>
                <code>
                    #include <.stack.>    // Include stack header
                    stack<.int.> s;    // Create a stack
                    s.push(1);    // Add 1 at top
                    s.push(2);    // Add 2 at top
                    s.push(3);    // Add 3 at top
                    cout << s.top();    // This will print 3
                    s.pop();    // Remove 3 from top
                    cout << s.top();    // This will print 2
                </code>
            </pre>
        </li>
        <h1>Queue :-</h1>
        <li>Unlike vectors, elements in the queue are not accessed by index numbers. Since elements are added at the back and removed from the front, you can only access the element at the front of the queue.</li>
        <li>Various methods for queue :-
            <ul>
                <li>push() - This will add element at back</li>
                <li>pop() - This will remove element from front</li>
                <li>front() - This will return front element</li>
                <li>back() - This will return back element</li>
                <li>size() - This will return size of queue</li>
                <li>empty() - This will return true if queue is empty else false</li>
            </ul>
            <pre>
                <code>
                    #include <.queue.>    // Include queue header
                    queue<.int.> q;    // Create a queue
                    q.push(1);    // Add 1 at back
                    q.push(2);    // Add 2 at back
                    q.push(3);    // Add 3 at back
                    cout << q.front();    // This will print 1
                    q.pop();    // Remove 1 from front
                    cout << q.front();    // This will print 2
                </code>
            </pre>
        </li>
        <h1>Priority Queue :-</h1>
        <li>First element of the queue is either the greatest or the smallest of all elements in the queue, and elements are in non-increasing or non-decreasing order.</li>
        <li>Priority queues are built on the top of the max heap and min heap</li>
        <li>By default is returns greatest element in queue, but you cam change it to smallest as well.</li>
        <li>Time Complexityof various operations for Priority Queue :-
            <ul>
                <li>Insertion - O(logN)</li>
                <li>Deletion - O(logN)</li>
                <li>Accessing element - O(1)</li>
            </ul>
        </li>
        <li>Various methods in Priority Queue :-
            <ul>
                <li>push() - This will add element in queue</li>
                <li>pop() - This will remove element from queue, remove from front</li>
                <li>top() - This will return top element</li>
                <li>size() - This will return size of queue</li>
                <li>empty() - This will return true if queue is empty else false</li>
            </ul>
            <pre>
                <code>
                    #include <.queue.>    // Include queue header
                    priority_queue<.int.> pq;    // Create a priority queue, with max-heap, which means it will return greatest element, To make it min-heap use priority_queue<.int., vector<.int.>, greater<.int.>> pq;
                    pq.push(1);    // Add 1 in queue
                    pq.push(2);    // Add 2 in queue
                    pq.push(3);    // Add 3 in queue
                    cout << pq.top();    // This will print 3
                    pq.pop();    // Remove 3 from queue
                    cout << pq.top();    // This will print 2
                </code>
            </pre>
        </li>
        <h1>Map in C++ :-</h1>
        <li>Maps are associative containers that store elements in a mapped fashion. Each element has a key value and a mapped value. No two mapped values can have same key values.</li>
        <li>Automatically sorted in ascending order by their keys.</li>
        <li>map is typically implemented as a balanced binary search tree (often a Red-Black Tree), which means that the operations have logarithmic time complexity.</li>
        <li>To store element in descending order use something like :-
            <pre>
                <code>
                    map<.int, int, greater<.int>> m;    // This will store elements in descending order
                </code>
            </pre>
        </li>
        <li>Time complexity of variour operations :-
            <ul>
                <li>Insertion - O(logN)</li>
                <li>Deletion - O(logN)</li>
                <li>Accessing element - O(logN)</li>
                <li>Clearing all elements - O(N)</li>
            </ul>
        </li>
        <li>Various methods in Map :-
            <ul>
                <li>Insert : Using []
                    <pre>
                        <code>
                            #include <.map.>    // Include map header
                            map<.int, string> m;    // Create a map
                            m[1] = "abc";    // Insert 1 with value abc
                            m[2] = "def";    // Insert 2 with value def
                            m[3] = "ghi";    // Insert 3 with value ghi
                            cout << m[2];    // This is accessing value of map
                        </code>
                    </pre>
                </li>
                <li>Accessing : Using []
                    <pre>
                        <code>
                            cout << m[2];    // This is accessing value of map
                        </code>
                    </pre>
                </li>
                <li>Getting size:- size(): Returns the number of elements.</li>
                <li>empty(): Checks if the map is empty.</li>
                <li>clear(): Removes all elements.</li>
                <li>erase(key): To remove specific elements from a map</li>
                <li>count(key): Returns 1 if the key exists, otherwise 0.</li>
                <li>Loop through map : Map can be looped through auto
                    <pre>
                        <code>
                            map<.int, string> m;
                            for(auto i: m) {
                                cout << i.first << " " << i.second << endl;
                            }
                        </code>
                    </pre>
                </li>
            </ul>
        </li>
        <h1>Unordered Map :-</h1>
        <li> Unlike map, which is implemented as a balanced binary tree and keeps elements sorted by keys, unordered_map uses a hash table, so the elements are not stored in any specific order.</li>
        <li>Time complexity of variour operations :-
            <ul>
                <li>Insertion - O(1)</li>
                <li>Deletion - O(1)</li>
                <li>Accessing element - O(1)</li>
                <li>Clearing all elements - O(N)</li>
            </ul>
        </li>
        <li>Most of the methods are similar to ordere map. Example :-
            <pre>
                <code>
                    #include <.unordered_map>    // Include unordered_map header
                    unordered_map<.int, string> m;    // Create a unordered_map
                    m[1] = "abc";    // Insert 1 with value abc
                    m[2] = "def";    // Insert 2 with value def
                    m[3] = "ghi";    // Insert 3 with value ghi
                    cout << m[2];    // This is accessing value of map
                </code>
            </pre>
        </li>
        <h1>Set :-</h1>
        <li>Set is a container that stores unique elements following a specific order.</li>
        <li>Set is similar to map, only difference is it stores unique elements in it.</li>
        <li>In set you can't use []. You have to insert value using insert()</li>
        <li>To access element in map either iterate on set or use count()</li>
        <li>Similar, to map if you want to store elementin descending order use something like :-
            <pre>
                <code>
                    set<.int, greater<.int>> s;    // This will store elements in descending order
                </code>
            </pre>
        </li>
        <li>Methods and time complexity are same as map. Example :-
            <pre>
                <code>
                    #include <.set>    // Include set header
                    set<.int> s;    // Create a set
                    s.insert(1);    // Insert 1 in set
                    s.insert(2);    // Insert 2 in set
                    s.insert(3);    // Insert 3 in set
                    cout << s.count(2);    // This will print 1
                </code>
            </pre>
        </li>
        <li>Similary, we have unoredred set, which almost same as unordered map. Example :-
            <pre>
                <code>
                    #include <.unordered_set>    // Include unordered_set header
                    unordered_set<.int> s;    // Create a unordered_set
                    s.insert(1);    // Insert 1 in unordered_set
                    s.insert(2);    // Insert 2 in unordered_set
                    s.insert(3);    // Insert 3 in unordered_set
                    cout << s.count(2);    // This will print 1
                </code>
            </pre>
        </li>