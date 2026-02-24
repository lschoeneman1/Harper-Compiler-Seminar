# Stage 1 Teaching Guide

## Overview

Stage 1 introduces students to the fundamental concepts of interpreters through a simple integer expression language.

## Learning Objectives

By the end of Stage 1, students should understand:

1. **Lexical Analysis**: How source code is broken into tokens
2. **Parsing**: How tokens form a syntax tree
3. **Evaluation**: How the tree is executed
4. **Separation of Concerns**: Why we separate lexer, parser, and evaluator

## Key Concepts

### 1. Tokens

**What are tokens?**
- Tokens are the smallest meaningful units of a language
- Examples: `42` (INTEGER), `x` (IDENTIFIER), `+` (PLUS), `print` (PRINT)

**Why tokens?**
- Simplifies parsing (we don't parse characters, we parse tokens)
- Handles whitespace automatically
- Makes error reporting easier

### 2. Abstract Syntax Tree (AST)

**What is an AST?**
- A tree representation of program structure
- Each node represents a language construct
- Leaves are literals or identifiers
- Internal nodes are operations

**Example:**
```
x = 10 + 5;
```

AST:
```
AssignmentStatement
  Variable: "x"
  Expression:
    BinaryExpression
      Operator: "+"
      Left: IntegerLiteral(10)
      Right: IntegerLiteral(5)
```

### 3. Symbol Table

**What is a symbol table?**
- A data structure that maps variable names to values
- Like a dictionary: `{ "x": 10, "y": 20 }`
- Used during evaluation to look up variable values

## Teaching Sequence

### Day 1: Introduction to Tokens

1. **Warm-up**: Show students a simple program
   ```
   x = 10;
   print x;
   ```

2. **Activity**: Have students manually tokenize
   - Break the program into tokens
   - Identify token types
   - Discuss whitespace handling

3. **Implementation**: Walk through Lexer.cs/cpp
   - Show how characters are grouped
   - Demonstrate state machine concept
   - Handle edge cases (identifiers vs keywords)

### Day 2: Parsing

1. **Review**: Tokenization from previous day

2. **Introduction**: Show how tokens form structure
   - Demonstrate operator precedence
   - Show parse tree vs AST

3. **Implementation**: Walk through Parser.cs/cpp
   - Explain recursive descent
   - Show how grammar rules map to functions
   - Handle parentheses

### Day 3: Evaluation

1. **Review**: Parsing from previous day

2. **Introduction**: Show how AST is executed
   - Expression evaluation
   - Variable storage
   - Statement execution

3. **Implementation**: Walk through Evaluator.cs/cpp
   - Show symbol table usage
   - Demonstrate tree traversal
   - Handle errors (undefined variables)

### Day 4: Integration and Testing

1. **Review**: All three stages

2. **Activity**: Students write test programs
   - Simple assignments
   - Complex expressions
   - Error cases

3. **Discussion**: Architecture benefits
   - Why separate stages?
   - How to extend the language?

## Common Student Questions

**Q: Why do we need three separate stages?**
A: Separation of concerns makes the code easier to understand, test, and extend. Each stage has one job.

**Q: What's the difference between a parse tree and an AST?**
A: A parse tree shows all grammar rules applied. An AST is simplified and only shows the essential structure.

**Q: How do we handle negative numbers?**
A: In Stage 1, we can write `0 - 10` for negative numbers. Later stages can add unary minus support.

**Q: Why do we need semicolons?**
A: Semicolons help the parser know where statements end. Some languages (like Python) use newlines instead.

## Extension Ideas

After Stage 1, students might want to add:
- Unary minus (negative numbers)
- More operators (modulo, exponentiation)
- Comments
- Multiple statements per line
- Better error messages

## Assessment

**Formative:**
- Tokenize a given program
- Draw the AST for an expression
- Trace execution of a program

**Summative:**
- Implement a new operator
- Add a new statement type
- Improve error handling

