# MidLang Stage 1 - C++ Implementation

## Overview

This is the C++ implementation of MidLang Stage 1: Basic Integer Expressions.

## Files

- **Token.h/cpp**: Defines token types and the Token class
- **Lexer.h/cpp**: Converts source code into tokens
- **AST.h**: Defines Abstract Syntax Tree node classes
- **Parser.h/cpp**: Builds AST from tokens
- **Evaluator.h/cpp**: Executes the AST
- **main.cpp**: Main entry point

## Building

### Using g++ (GCC/Clang)

```bash
cd cpp/Stage1
g++ -std=c++17 -Wall -o interpreter *.cpp
```

### Using Visual Studio (Windows)

```bash
cd cpp/Stage1
cl /EHsc /std:c++17 *.cpp /Fe:interpreter.exe
```

### Using CMake (recommended for larger projects)

Create a `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.10)
project(MidLang)

set(CMAKE_CXX_STANDARD 17)

add_executable(interpreter
    main.cpp
    Lexer.cpp
    Parser.cpp
    Evaluator.cpp
)
```

Then:
```bash
mkdir build
cd build
cmake ..
make
```

## Running

```bash
# From cpp/Stage1 directory
./interpreter ../../examples/stage1_example1.mid

# Or on Windows
interpreter.exe ..\..\examples\stage1_example1.mid
```

## How It Works

1. **Lexer** reads the source file and breaks it into tokens
2. **Parser** builds an AST from the tokens
3. **Evaluator** executes the AST and produces output

See `../../docs/Architecture.md` for detailed explanations.

## Example

**Input file (`program.mid`):**
```
x = 10;
y = 20;
z = x + y;
print z;
```

**Output:**
```
=== Interpreting: program.mid ===

Stage 1: Lexical Analysis (Tokenization)
Generated 13 tokens:
  [tokens listed]

Stage 2: Parsing (Building AST)
Parsed 4 statement(s)

Stage 3: Evaluation (Execution)
Output:
30

=== Program completed successfully ===
```

## Notes for C++ Students

- Uses `std::unique_ptr` for memory management (modern C++)
- Uses `std::unordered_map` for the symbol table
- Uses `std::vector` for token and statement lists
- All classes are in header files with implementations in .cpp files
- Exception handling for error reporting

