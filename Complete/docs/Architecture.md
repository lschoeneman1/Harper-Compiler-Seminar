# Interpreter Architecture

This document explains the three-stage architecture of the MidLang interpreter.

## Overview

```
Source Code → [Lexer] → Tokens → [Parser] → AST → [Evaluator] → Output
```

## Stage 1: Lexer (Lexical Analyzer / Tokenizer)

**Purpose**: Break source code into a sequence of tokens.

**What it does:**
- Reads the source code character by character
- Groups characters into meaningful units (tokens)
- Removes whitespace and comments
- Identifies keywords, identifiers, operators, and literals

**Example:**
```
Input:  "x = 10 + 5;"
Output: [Identifier("x"), Assign, Integer(10), Plus, Integer(5), Semicolon]
```

**Key Concepts:**
- **Token**: A meaningful unit of the language (e.g., identifier, number, operator)
- **Token Type**: The category of token (e.g., INTEGER, IDENTIFIER, PLUS)
- **Token Value**: The actual content (e.g., "10", "x", "+")

## Stage 2: Parser (Syntax Analyzer)

**Purpose**: Build an Abstract Syntax Tree (AST) from tokens.

**What it does:**
- Takes a stream of tokens from the lexer
- Verifies the tokens form valid syntax according to the grammar
- Builds a tree structure representing the program's structure
- Reports syntax errors if the program is invalid

**Example:**
```
Input:  [Identifier("x"), Assign, Integer(10), Plus, Integer(5), Semicolon]
Output: AST:
        AssignmentStatement
          Identifier: "x"
          Expression:
            BinaryExpression
              Operator: +
              Left: Integer(10)
              Right: Integer(5)
```

**Key Concepts:**
- **AST (Abstract Syntax Tree)**: A tree representation of the program's structure
- **Parse Tree**: Shows how grammar rules were applied (more detailed than AST)
- **Recursive Descent**: A parsing technique that uses recursive functions

## Stage 3: Evaluator (Interpreter)

**Purpose**: Execute the AST to produce program output.

**What it does:**
- Traverses the AST
- Evaluates expressions (computes values)
- Manages variable storage (symbol table)
- Executes statements (assignments, prints)
- Produces output

**Example:**
```
Input:  AST (from above)
Process:
  1. Evaluate expression: 10 + 5 = 15
  2. Store in symbol table: x = 15
  3. (If print statement) Output: 15
```

**Key Concepts:**
- **Symbol Table**: A data structure storing variable names and their values
- **Evaluation**: Computing the value of an expression
- **Execution**: Performing the actions specified by statements

## Why This Separation?

1. **Modularity**: Each stage has a clear, single responsibility
2. **Testability**: Each stage can be tested independently
3. **Maintainability**: Changes to one stage don't affect others
4. **Educational**: Students can understand each concept separately

## Data Flow

```
Source File
    ↓
Lexer.readTokens()
    ↓
List<Token>
    ↓
Parser.parse()
    ↓
AST (Program node)
    ↓
Evaluator.evaluate()
    ↓
Output (console/result)
```

## Error Handling

Each stage handles different types of errors:

- **Lexer**: Invalid characters, unterminated strings
- **Parser**: Syntax errors, missing tokens, unexpected tokens
- **Evaluator**: Undefined variables, division by zero, type errors

