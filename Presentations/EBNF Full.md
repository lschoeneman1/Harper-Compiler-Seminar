# EBNF Grammar for MidLang

This document defines the formal grammar for MidLang using Extended Backus-Naur Form (EBNF).

## Stage 1: Basic Integer Expressions

### Tokens (Terminal Symbols)

```
DIGIT       = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
LETTER      = "a" | "b" | ... | "z" | "A" | "B" | ... | "Z"
IDENTIFIER  = LETTER { LETTER | DIGIT | "_" }
INTEGER     = ["-"] DIGIT { DIGIT }
OPERATOR   = "+" | "-" | "*" | "/"
ASSIGN      = "="
PRINT       = "print"
SEMICOLON   = ";"
NEWLINE     = "\n"
WHITESPACE  = " " | "\t"
```

### Grammar Rules (Non-Terminal Symbols)

```
Program     = Statement { Statement }

Statement   = AssignmentStatement
            | PrintStatement

AssignmentStatement = Identifier ASSIGN Expression SEMICOLON

PrintStatement = PRINT Expression SEMICOLON

Expression  = Term { ("+" | "-") Term }

Term        = Factor { ("*" | "/") Factor }

Factor      = INTEGER
            | Identifier
            | "(" Expression ")"

Identifier  = IDENTIFIER
```

### Operator Precedence

The grammar enforces operator precedence:
- **Highest**: Parentheses `()`
- **High**: Multiplication `*`, Division `/`
- **Low**: Addition `+`, Subtraction `-`

### Notes

- **Negative Numbers**: In Stage 1, negative numbers are not handled as literals. Use `0 - 10` to represent `-10`. Unary minus can be added in later stages.
- **Whitespace**: Spaces, tabs, and newlines are ignored except as separators.
- **Semicolons**: Required after each statement.

### Examples

**Valid Programs:**
```
x = 10;
print x;
```

```
a = 5;
b = 3;
c = a + b * 2;
print c;
```

```
x = (10 + 5) * 2;
print x;
```

```
// Negative number workaround
x = 0 - 10;
print x;
```

**Invalid Programs:**
```
x = ;           // Missing expression
print;          // Missing expression
x = 5 +;        // Incomplete expression
x = -10;        // Unary minus not supported in Stage 1
```

---

## Stage 3: If/Else Statements

### Additional Tokens

```
IF            = "if"
ELSE          = "else"
LEFT_BRACE    = "{"
RIGHT_BRACE   = "}"
EQUAL_EQUAL   = "=="
NOT_EQUAL     = "!="
LESS          = "<"
GREATER       = ">"
LESS_EQUAL    = "<="
GREATER_EQUAL = ">="
```

### Additional Grammar Rules

```
Statement   = AssignmentStatement
            | PrintStatement
            | PrintLineStatement
            | VarDeclarationStatement
            | IfStatement

IfStatement = IF LEFT_PAREN BooleanExpression RIGHT_PAREN LEFT_BRACE Statement { Statement } RIGHT_BRACE [ ELSE LEFT_BRACE Statement { Statement } RIGHT_BRACE ]

BooleanExpression = Expression ComparisonOperator Expression

ComparisonOperator = EQUAL_EQUAL      // ==
                   | NOT_EQUAL        // !=
                   | LESS             // <
                   | GREATER          // >
                   | LESS_EQUAL       // <=
                   | GREATER_EQUAL    // >=
```

### Notes

- **If Statement**: The condition must be a boolean expression (comparison between two expressions).
- **Else Clause**: Optional. If present, executes when the condition is false.
- **Block Statements**: Multiple statements can be grouped in braces `{}`.
- **Comparison Operators**: All comparison operators return a boolean value (true/false represented as 1/0 internally).

### Examples

**Valid Programs:**
```
var x = 10;
if (x > 5) {
    print("x is greater than 5");
}

var y = 3;
if (y == 3) {
    print("y equals 3");
} else {
    print("y does not equal 3");
}

var a = 10;
var b = 20;
if (a < b) {
    print("a is less than b");
} else {
    print("a is not less than b");
}
```

**Invalid Programs:**
```
if (x) { }              // Condition must be a comparison, not just a variable
if x > 5 { }            // Missing parentheses around condition
if (x > 5) print(x);    // Missing braces (single statement requires braces)
```

---

## Stage 4: While Loops

### Additional Tokens

```
WHILE         = "while"
```

### Additional Grammar Rules

```
Statement   = AssignmentStatement
            | PrintStatement
            | PrintLineStatement
            | VarDeclarationStatement
            | IfStatement
            | WhileStatement

WhileStatement = WHILE LEFT_PAREN BooleanExpression RIGHT_PAREN LEFT_BRACE Statement { Statement } RIGHT_BRACE
```

### Notes

- **While Loop**: Executes the block of statements repeatedly as long as the condition is true.
- **Condition**: Must be a boolean expression (comparison between two expressions).
- **Block Statements**: Multiple statements can be grouped in braces `{}`.
- **Loop Control**: The condition is evaluated before each iteration. If false initially, the loop body never executes.

### Examples

**Valid Programs:**
```
var x = 0;
while (x < 5) {
    println(x);
    x = x + 1;
}

var count = 10;
while (count > 0) {
    println(count);
    count = count - 1;
}

var i = 1;
var sum = 0;
while (i <= 10) {
    sum = sum + i;
    i = i + 1;
}
println(sum);
```

**Invalid Programs:**
```
while (x) { }           // Condition must be a comparison, not just a variable
while x < 5 { }         // Missing parentheses around condition
while (x < 5) print(x); // Missing braces (single statement requires braces)
```

