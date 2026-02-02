cmake_minimum_required(VERSION 3.10)
project(MidLangTranspiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(transpiler
    main.cpp
    Lexer.cpp
    Parser.cpp
    CodeGenerator.cpp
)

# Set output directory
set_target_properties(transpiler PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)


