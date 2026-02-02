# MidLang to C++ Assembly-Style Transpiler

## Overview

This project transpiles MidLang source code into C++ source code using **goto statements and labels**, treating C++ as an assembly language replacement. This demonstrates how high-level control structures (if/else, while loops) can be translated into low-level jump instructions.

## Architecture

The transpiler follows a three-stage architecture:

1. **Lexer**: Converts MidLang source code into tokens
2. **Parser**: Builds an Abstract Syntax Tree (AST) from tokens
3. **CodeGenerator**: Traverses the AST and generates assembly-style C++ code with gotos

## Key Differences from Standard Transpiler

- **No structured control flow**: All if/else and while loops are converted to goto statements
- **Explicit labels**: Every statement block gets a label
- **Assembly-like structure**: Code resembles assembly language with explicit jumps
- **Educational value**: Shows how compilers translate high-level constructs to low-level jumps

## Building

### Using CMake (Recommended)

```bash
cd TranspilerAssembly
mkdir build
cd build
cmake ..
make
```

### Using g++ (GCC/Clang)

```bash
cd TranspilerAssembly
g++ -std=c++17 -Wall -o transpiler_asm *.cpp
```

### Using Visual Studio (Windows)

```bash
cd TranspilerAssembly
cl /EHsc /std:c++17 *.cpp /Fe:transpiler_asm.exe
```

## Usage

```bash
# Basic usage (outputs to program.cpp)
./transpiler_asm program.mid

# Specify output file
./transpiler_asm program.mid output.cpp
```

## Example

**Input (`example.mid`):**
```
var x = 0;
while (x < 5) {
    println(x);
    x = x + 1;
}
```

**Generated C++ (`example.cpp`):**
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    // Variable declarations
    int x;
    
    // Program start
    goto L_START;
    
    L_STMT_0:
    x = 0;
    goto L_STMT_1;
    
    L_STMT_1:
    // while loop
    L_LOOP_2:
    if (!((x < 5))) goto L_LOOP_END_3;
    
    // loop body
    cout << x << endl;
    goto L_STMT_2;
    
    L_STMT_2:
    x = (x + 1);
    goto L_LOOP_2;
    
    L_LOOP_END_3:
    
    L_START:
    goto L_STMT_0;
    
    L_END:
    return 0;
}
```

## Features

The transpiler supports all MidLang Stage 4 features, translated to assembly-style:
- Variable declarations (declared at start, initialized later)
- Variable assignments
- Arithmetic expressions
- Print statements (`print`, `println`)
- If/else statements (converted to conditional gotos)
- While loops (converted to labels and gotos)
- Comparison operators

## How It Works

### If/Else Translation
```
if (condition) {
    then_block;
} else {
    else_block;
}
```

Becomes:
```cpp
if (!(condition)) goto L_ELSE;
// then_block
goto L_IF_END;
L_ELSE:
// else_block
L_IF_END:
```

### While Loop Translation
```
while (condition) {
    body;
}
```

Becomes:
```cpp
L_LOOP:
if (!(condition)) goto L_LOOP_END;
// body
goto L_LOOP;
L_LOOP_END:
```

## Files

- **Token.h**: Token definitions
- **Lexer.h/cpp**: Lexical analyzer
- **AST.h**: Abstract Syntax Tree nodes
- **Parser.h/cpp**: Parser
- **CodeGenerator.h/cpp**: Assembly-style C++ code generator
- **main.cpp**: Main entry point
- **CMakeLists.txt**: CMake build configuration

## Educational Value

This transpiler demonstrates:
- How high-level control structures map to low-level jumps
- The relationship between structured programming and assembly language
- How compilers translate control flow
- The concept of labels and gotos in C++

## Notes

- The generated code is intentionally verbose to show the assembly-like structure
- All variables are declared at the start (assembly-style)
- Labels are automatically generated to avoid conflicts
- The code is fully functional and compilable


