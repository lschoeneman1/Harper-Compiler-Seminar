#pragma once

#include <vector>
#include <string>
#include "Token.h"

/**
 * Lexer (Lexical Analyzer / Tokenizer)
 * 
 * Purpose: Converts source code into a stream of tokens.
 * 
 * How it works:
 * 1. Reads the source code character by character
 * 2. Groups characters into tokens (keywords, identifiers, operators, etc.)
 * 3. Returns a list of tokens for the parser to use
 */
class Lexer
{
	std::string source;
	size_t position;
	int line;
	int column;

	// Helper methods
	char peek();
	char advance();
	bool isAtEnd() const;
	Token createToken(TokenType type) const;
	void skipWhitespace();

	// Token reading methods
	Token nextToken();
	Token readNumber();
	Token readIdentifier();

public:
	Lexer(const std::string& source);

	/**
	 * Tokenizes the source code and returns a list of tokens.
	 */
	std::vector<Token> tokenize();
};
