// Convert an infix expression to postfix.

// Infix notation (human-friendly):  A + B * C  (needs precedence rules)
// Postfix notation (machine-friendly): A B C * +  (evaluated left to right with a stack)

// Operator precedence:
// 1. ^ (highest) -> 3
// 2. * and /     -> 2
// 3. + and -     -> 1
// 4. rest        -> -1

// 🔧 Algorithm
// 1. Use a stack for operators and a string for the output.
// 2. Scan left to right:
//    a. Operand (A-Z, a-z, 0-9): add to output.
//    b. '(': push to stack.
//    c. ')': pop to output until '(' is found; discard '('.
//    d. Operator: while the stack top is an operator with >= precedence, pop it to output;
//       then push the current operator.
// 3. Pop any remaining operators to output.

// JavaScript note: a plain array is the operator stack; string concatenation builds the output.
// We test characters with a regex/char comparisons since there is no char type.
function prec(c) {
  if (c === "^") return 3;
  else if (c === "/" || c === "*") return 2;
  else if (c === "+" || c === "-") return 1;
  else return -1;
}

function isOperand(c) {
  return /[a-zA-Z0-9]/.test(c);
}

function infixToPostfix(s) {
  const st = [];
  let res = "";

  for (let i = 0; i < s.length; i++) {
    const c = s[i];

    if (isOperand(c)) {
      res += c;
    } else if (c === "(") {
      st.push("(");
    } else if (c === ")") {
      while (st.length > 0 && st[st.length - 1] !== "(") {
        res += st.pop();
      }
      st.pop(); // discard '('
    } else {
      // operator
      while (st.length > 0 && prec(c) <= prec(st[st.length - 1])) {
        res += st.pop();
      }
      st.push(c);
    }
  }

  while (st.length > 0) {
    res += st.pop();
  }

  return res;
}

console.log(infixToPostfix("a+b*(c^d-e)^(f+g*h)-i")); // abcd^e-fgh*+^*+i-
