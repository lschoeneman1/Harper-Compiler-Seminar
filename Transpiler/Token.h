#ifndef TOKEN_H
#define TOKEN_H

#include <string>

/**
 * TokenType - Types of tokens in MidLang Stage 1
 */
enum class TokenType {
    // Literals
    INTEGER,        // e.g., 42, -10
    IDENTIFIER,     // e.g., x, count, myVar

    // Operators
    PLUS,           // +
    MINUS,          // -
    MULTIPLY,       // *
    DIVIDE,         // /

    // Comparison Operators
    EQUAL_EQUAL,    // ==
    NOT_EQUAL,      // !=
    LESS,           // <
    GREATER,        // >
    LESS_EQUAL,     // <=
    GREATER_EQUAL,  // >=

    // Punctuation
    ASSIGN,         // =
    SEMICOLON,      // ;
    LEFT_PAREN,     // (
    RIGHT_PAREN,    // )
    LEFT_BRACE,     // {
    RIGHT_BRACE,    // }

    // Keywords
    VAR,            // var
    PRINT,          // print
    PRINTLN,        // println
    INPUT_INT,      // inputInt
    IF,             // if
    ELSE,           // else
    WHILE,          // while

    // Special
    EOF_TOKEN,      // End of file
    UNKNOWN         // Invalid token
};

/**
 * Token - Represents a token in the source code.
 * 
 * Tokens are the smallest meaningful units of the language.
 * Each token has:
 * - A type (what kind of token it is)
 * - A value (the actual text)
 * - Position information (line and column for error reporting)
 */
class Token {
public:
    TokenType type;
    std::string value;
    int line;
    int column;

    Token(TokenType t, const std::string& v, int l, int c)
        : type(t), value(v), line(l), column(c) {}
};

#endif // TOKEN_H

