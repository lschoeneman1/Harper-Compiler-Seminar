#include "Lexer.h"
#include <cctype>
#include <sstream>

using namespace std;
Lexer::Lexer(const string& source) 	: source(source), position(0), line(1), column(1)
{
}

vector<Token> Lexer::tokenize()
{
	vector<Token> tokens;

	while (!isAtEnd())
	{
		skipWhitespace();
		if (isAtEnd()) break;

		Token token = nextToken();
		tokens.push_back(token);

		// Stop if we hit an error token
		if (token.type == TokenType::UNKNOWN)
		{
			break;
		}
	}

	// Add EOF token at the end
	tokens.emplace_back(TokenType::EOF_TOKEN, "", line, column);
	return tokens;
}

Token Lexer::nextToken()
{
	char current = advance();

	// Two-character operators (check these first)
	switch (current)
	{
		case '=':
			if (peek() == '=')
			{
				advance(); // consume the second '='
				return Token(TokenType::EQUAL_EQUAL, "==", line, column - 2);
			}
			return createToken(TokenType::ASSIGN);
		case '!':
			if (peek() == '=')
			{
				advance(); // consume the '='
				return Token(TokenType::NOT_EQUAL, "!=", line, column - 2);
			}
			return Token(TokenType::UNKNOWN, string(1, current), line, column - 1);
		case '<':
			if (peek() == '=')
			{
				advance(); // consume the '='
				return Token(TokenType::LESS_EQUAL, "<=", line, column - 2);
			}
			return createToken(TokenType::LESS);
		case '>':
			if (peek() == '=')
			{
				advance(); // consume the '='
				return Token(TokenType::GREATER_EQUAL, ">=", line, column - 2);
			}
			return createToken(TokenType::GREATER);
		case '+': return createToken(TokenType::PLUS);
		case '-': return createToken(TokenType::MINUS);
		case '*': return createToken(TokenType::MULTIPLY);
		case '/': return createToken(TokenType::DIVIDE);
		case ';': return createToken(TokenType::SEMICOLON);
		case '(': return createToken(TokenType::LEFT_PAREN);
		case ')': return createToken(TokenType::RIGHT_PAREN);
		case '{': return createToken(TokenType::LEFT_BRACE);
		case '}': return createToken(TokenType::RIGHT_BRACE);
	}

	// Numbers (integers)
	if (isdigit(current))
	{
		return readNumber();
	}

	// Identifiers and keywords
	if (isalpha(current) || current == '_')
	{
		return readIdentifier();
	}

	// Unknown character
	return Token(TokenType::UNKNOWN, string(1, current), line, column);
}

Token Lexer::readNumber()
{
	int startColumn = column - 1;
	stringstream number;

	// Read digits (we've already consumed the first digit)
	number << source[position - 1];

	// Read remaining digits
	while (!isAtEnd() && isdigit(peek()))
	{
		number << advance();
	}

	return Token(TokenType::INTEGER, number.str(), line, startColumn);
}

Token Lexer::readIdentifier()
{
	int startColumn = column - 1;
	stringstream identifier;

	// Read first character (already consumed)
	identifier << source[position - 1];

	// Read remaining letters, digits, and underscores
	while (!isAtEnd() && (isalnum(peek()) || peek() == '_'))
	{
		identifier << advance();
	}

	string value = identifier.str();

	// Check if it's a keyword
	TokenType type;
	if (value == "var")
	{
		type = TokenType::VAR;
	}
	else if (value == "print")
	{
		type = TokenType::PRINT;
	}
	else if (value == "println")
	{
		type = TokenType::PRINTLN;
	}
	else if (value == "inputInt")
	{
		type = TokenType::INPUT_INT;
	}
	else if (value == "if")
	{
		type = TokenType::IF;
	}
	else if (value == "else")
	{
		type = TokenType::ELSE;
	}
	else if (value == "while")
	{
		type = TokenType::WHILE;
	}
	else
	{
		type = TokenType::IDENTIFIER;
	}

	return Token(type, value, line, startColumn);
}

void Lexer::skipWhitespace()
{
	while (!isAtEnd())
	{
		char c = peek();
		if (c == ' ' || c == '\t')
		{
			advance();
		}
		else if (c == '\r')
		{
			// Handle Windows line endings (\r\n)
			advance();
			if (!isAtEnd() && peek() == '\n')
			{
				advance(); // Skip the \n after \r
			}
			line++;
			column = 1;
		}
		else if (c == '\n')
		{
			// Handle Unix line endings (\n)
			advance();
			line++;
			column = 1;
		}
		else
		{
			break;
		}
	}
}

char Lexer::peek()
{
	if (isAtEnd())
	{
		return '\0';
	}
	return source[position];
}

char Lexer::advance()
{
	if (isAtEnd())
	{
		return '\0';
	}
	column++;
	return source[position++];
}

bool Lexer::isAtEnd() const
{
	return position >= source.length();
}

Token Lexer::createToken(TokenType type) const
{
	string value(1, source[position - 1]);
	return Token(type, value, line, column - 1);
}
