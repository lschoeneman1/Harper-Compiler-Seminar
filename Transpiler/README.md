# MidLang to C++ Transpiler

## Overview

This project transpiles MidLang source code into C++ source code. Instead of interpreting the code directly, it generates equivalent C++ code that can be compiled and executed.

## Architecture

The transpiler follows a three-stage architecture:

1. **Lexer**: Converts MidLang source code into tokens
2. **Parser**: Builds an Abstract Syntax Tree (AST) from tokens
3. **CodeGenerator**: Traverses the AST and generates C++ code

## Building

### Using CMake (Recommended)

```bash
cd Transpiler
mkdir build
cd build
cmake ..
make
```

### Using g++ (GCC/Clang)

```bash
cd Transpiler
g++ -std=c++17 -Wall -o transpiler *.cpp
```

### Using Visual Studio (Windows)

```bash
cd Transpiler
cl /EHsc /std:c++17 *.cpp /Fe:transpiler.exe
```

## Usage

```bash
# Basic usage (outputs to program.cpp)
./transpiler program.mid

# Specify output file
./transpiler program.mid output.cpp
```

## Example

**Input (`example.mid`):**
```
var x = 10;
var y = 20;
if (x < y) {
    println(x);
} else {
    println(y);
}
```

**Generated C++ (`example.cpp`):**
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    int x = 10;
    int y = 20;
    if ((x < y)) {
        cout << x << endl;
    } else {
        cout << y << endl;
    }
    return 0;
}
```

**Compile and run:**
```bash
g++ example.cpp -o example
./example
```

## Features

The transpiler supports all MidLang Stage 4 features:
- Variable declarations (`var`)
- Variable assignments
- Arithmetic expressions (`+`, `-`, `*`, `/`)
- Print statements (`print`, `println`)
- If/else statements
- While loops
- Comparison operators (`==`, `!=`, `<`, `>`, `<=`, `>=`)
- Input functions (`inputInt()`)

## Files

- **Token.h**: Token definitions
- **Lexer.h/cpp**: Lexical analyzer
- **AST.h**: Abstract Syntax Tree nodes
- **Parser.h/cpp**: Parser
- **CodeGenerator.h/cpp**: C++ code generator
- **main.cpp**: Main entry point
- **CMakeLists.txt**: CMake build configuration

## Notes

- The generated C++ code includes a complete `main()` function
- All variables are declared as `int` (for now)
- Input handling (`inputInt()`) is simplified and may need enhancement
- The generated code is formatted with proper indentation


