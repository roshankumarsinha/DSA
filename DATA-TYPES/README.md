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