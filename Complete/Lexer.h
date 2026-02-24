#pragma once

#include <vector>
#include <string>
#include "Token.h"
using namespace std;

/**
 * Lexer (Lexical Analyzer / Tokenizer)
 * 
 * Purpose: Converts source code into a stream of tokens.
 * 
 * How it works:
 * 1. Reads source code character by character
 * 2. Groups characters into meaningful tokens
 * 3. Skips whitespace
 * 4. Returns tokens one at a time
 */
class Lexer
{
	string source;
	size_t position; // Current position in source
	int line; // Current line number
	int column; // Current column number

	// Helper methods
	char peek();
	char advance();
	bool isAtEnd() const;
	void skipWhitespace();
	Token readNumber();
	Token readIdentifier();
	Token nextToken();
	Token createToken(TokenType type) const;

public:
	Lexer(const string& source);

	/**
	 * Tokenizes the entire source code and returns all tokens.
	 */
	vector<Token> tokenize();
};
