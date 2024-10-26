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