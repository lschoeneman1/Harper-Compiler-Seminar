#pragma once

#include <vector>
#include <memory>
#include "Token.h"
#include "AST.h"

using namespace std;

/**
 * Parser (Syntax Analyzer)
 * 
 * Purpose: Builds an Abstract Syntax Tree (AST) from tokens.
 * 
 * How it works:
 * 1. Takes a list of tokens from the lexer
 * 2. Uses recursive descent parsing
 * 3. Verifies syntax matches the grammar
 * 4. Builds AST nodes representing the program structure
 * 
 * Grammar (recall from EBNF):
 * Program = Statement { Statement }
 * Statement = AssignmentStatement | PrintStatement
 * AssignmentStatement = Identifier ASSIGN Expression SEMICOLON
 * PrintStatement = PRINT Expression SEMICOLON
 * Expression = Term { ("+" | "-") Term }
 * Term = Factor { ("*" | "/") Factor }
 * Factor = INTEGER | Identifier | "(" Expression ")"
 */
class Parser
{
	vector<Token> tokens;
	size_t current;

	// Helper methods
	bool match(TokenType type);
	bool match(TokenType type1, TokenType type2);
	bool match(TokenType type1, TokenType type2, TokenType type3, TokenType type4, TokenType type5, TokenType type6);
	bool check(TokenType type);
	Token advance();
	bool isAtEnd();
	Token peek();
	Token previous();
	Token consume(TokenType type, const string& message);

	// Parsing methods
	Statement* parseStatement();
	VarDeclarationStatement* parseVarDeclaration();
	AssignmentStatement* parseAssignmentStatement();
	PrintStatement* parsePrintStatement();
	PrintLineStatement* parsePrintLineStatement();
	IfStatement* parseIfStatement();
	WhileStatement* parseWhileStatement();
	Expression* parseExpression();
	Expression* parseTerm();
	Expression* parseFactor();
	BooleanExpression* parseBooleanExpression();

public:
	Parser(const vector<Token>& tokens);

	/**
	 * Parses the token stream and returns a Program AST node.
	 */
	ProgramNode* parse();
};
