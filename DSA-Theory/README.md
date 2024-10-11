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
<h1>To Execute C++ code in VS code use ```g++ filename.cpp && ./a.out```</h1>
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
                ```cpp
                int a = 5, b = 3;
                a = a ^ b;  // a becomes 6 (5 ^ 3)
                b = a ^ b;  // b becomes 5 (6 ^ 3)
                a = a ^ b;  // a becomes 3 (6 ^ 5)
                // Now a = 3, b = 5
                </li>
                <li><b>Checking if a Number is Even or Odd:</b>Use bitwise AND with 1 to check if the least significant bit is 1 (odd) or 0 (even):
                ```cpp
                if (num & 1) {
                    cout << "Odd" << endl;
                } else {
                    cout << "Even" << endl;
                }               
                </li>
                <li><b>Efficient Multiplication/Division by Powers of 2:</b>You can multiply a number by 2^k using a left shift (<< k) and divide it by 2^k using a right shift (>> k):
                ```cpp
                int x = 4;
                int multiply = x << 3;  // Equivalent to 4 * 2^3 = 32
                int divide = x >> 1;    // Equivalent to 4 / 2^1 = 2 
                </li>
            </ol>
        </li>