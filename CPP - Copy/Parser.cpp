#include "Parser.h"
#include <stdexcept>
#include <sstream>
using namespace std;

Parser::Parser(const vector<Token>& tokens)
	: tokens(tokens), current(0)
{
}

ProgramNode* Parser::parse()
{
	vector<Statement*> statements;

	while (!isAtEnd())
	{
		statements.push_back(parseStatement());
	}

	return new ProgramNode(statements);
}

Statement* Parser::parseStatement()
{
	if (match(TokenType::VAR))
	{
		return parseVarDeclaration();
	}
	if (match(TokenType::PRINT))
	{
		return parsePrintStatement();
	}
	if (match(TokenType::PRINTLN))
	{
		return parsePrintLineStatement();
	}
	if (match(TokenType::IF))
	{
		return parseIfStatement();
	}
	if (match(TokenType::WHILE))
	{
		return parseWhileStatement();
	}
	return parseAssignmentStatement();
}

VarDeclarationStatement* Parser::parseVarDeclaration()
{
	Token identifier = consume(TokenType::IDENTIFIER, "Expected variable name after 'var'");
	consume(TokenType::ASSIGN, "Expected '=' after variable name");
	auto expression = parseExpression();
	consume(TokenType::SEMICOLON, "Expected ';' after expression");

	return new VarDeclarationStatement(identifier.value, expression);
}

AssignmentStatement* Parser::parseAssignmentStatement()
{
	Token identifier = consume(TokenType::IDENTIFIER, "Expected variable name");
	consume(TokenType::ASSIGN, "Expected '=' after variable name");
	auto expression = parseExpression();
	consume(TokenType::SEMICOLON, "Expected ';' after expression");

	return new AssignmentStatement(identifier.value, expression);
}

PrintStatement* Parser::parsePrintStatement()
{
	consume(TokenType::LEFT_PAREN, "Expected '(' after 'print'");
	auto expression = parseExpression();
	consume(TokenType::RIGHT_PAREN, "Expected ')' after expression");
	consume(TokenType::SEMICOLON, "Expected ';' after ')'");

	return new PrintStatement(expression);
}

PrintLineStatement* Parser::parsePrintLineStatement()
{
	consume(TokenType::LEFT_PAREN, "Expected '(' after 'println'");
	auto expression = parseExpression();
	consume(TokenType::RIGHT_PAREN, "Expected ')' after expression");
	consume(TokenType::SEMICOLON, "Expected ';' after ')'");

	return new PrintLineStatement(expression);
}

IfStatement* Parser::parseIfStatement()
{
	consume(TokenType::LEFT_PAREN, "Expected '(' after 'if'");
	BooleanExpression* condition = parseBooleanExpression();
	consume(TokenType::RIGHT_PAREN, "Expected ')' after condition");
	consume(TokenType::LEFT_BRACE, "Expected '{' after ')'");

	// Parse then block
	vector<Statement*> thenStatements;
	while (!check(TokenType::RIGHT_BRACE) && !isAtEnd())
	{
		thenStatements.push_back(parseStatement());
	}
	consume(TokenType::RIGHT_BRACE, "Expected '}' after if block");

	// Parse else block (optional)
	vector<Statement*> elseStatements;
	if (match(TokenType::ELSE))
	{
		consume(TokenType::LEFT_BRACE, "Expected '{' after 'else'");
		while (!check(TokenType::RIGHT_BRACE) && !isAtEnd())
		{
			elseStatements.push_back(parseStatement());
		}
		consume(TokenType::RIGHT_BRACE, "Expected '}' after else block");
	}

	return new IfStatement(condition, thenStatements, elseStatements);
}

WhileStatement* Parser::parseWhileStatement()
{
	consume(TokenType::LEFT_PAREN, "Expected '(' after 'while'");
	BooleanExpression* condition = parseBooleanExpression();
	consume(TokenType::RIGHT_PAREN, "Expected ')' after condition");
	consume(TokenType::LEFT_BRACE, "Expected '{' after ')'");

	// Parse body block
	vector<Statement*> bodyStatements;
	while (!check(TokenType::RIGHT_BRACE) && !isAtEnd())
	{
		bodyStatements.push_back(parseStatement());
	}
	consume(TokenType::RIGHT_BRACE, "Expected '}' after while block");

	return new WhileStatement(condition, bodyStatements);
}

BooleanExpression* Parser::parseBooleanExpression()
{
	Expression* left = parseExpression();

	// Check for comparison operator
	if (!match(TokenType::EQUAL_EQUAL, TokenType::NOT_EQUAL, TokenType::LESS, TokenType::GREATER, TokenType::LESS_EQUAL, TokenType::GREATER_EQUAL))
	{
		stringstream ss;
		ss << "Expected comparison operator (==, !=, <, >, <=, >=) at line " << peek().line << ", column " << peek().column;
		throw runtime_error(ss.str());
	}

	string op = previous().value;
	Expression* right = parseExpression();

	return new BooleanExpression(left, op, right);
}

Expression* Parser::parseExpression()
{
	Expression* expr = parseTerm();

	while (match(TokenType::PLUS) || match(TokenType::MINUS))
	{
		string op = previous().value;
		auto right = parseTerm();
		expr = new BinaryExpression(expr, op, right);
	}

	return expr;
}

Expression* Parser::parseTerm()
{
	auto expr = parseFactor();

	while (match(TokenType::MULTIPLY) || match(TokenType::DIVIDE))
	{
		string op = previous().value;
		auto right = parseFactor();
		expr = new BinaryExpression(expr, op, right);
	}

	return expr;
}

Expression* Parser::parseFactor()
{
	if (match(TokenType::INTEGER))
	{
		int value = stoi(previous().value);
		return new IntegerLiteral(value);
	}

	if (match(TokenType::INPUT_INT))
	{
		consume(TokenType::LEFT_PAREN, "Expected '(' after 'inputInt'");
		consume(TokenType::RIGHT_PAREN, "Expected ')' after '('");
		return new InputIntExpression();
	}

	if (match(TokenType::IDENTIFIER))
	{
		return new VariableReference(previous().value);
	}

	if (match(TokenType::LEFT_PAREN))
	{
		auto expr = parseExpression();
		consume(TokenType::RIGHT_PAREN, "Expected ')' after expression");
		return expr;
	}

	stringstream ss;
	ss << "Unexpected token: " << static_cast<int>(peek().type)
		<< " at line " << peek().line << ", column " << peek().column;
	throw runtime_error(ss.str());
}

bool Parser::match(TokenType type)
{
	if (check(type))
	{
		advance();
		return true;
	}
	return false;
}

bool Parser::match(TokenType type1, TokenType type2)
{
	return match(type1) || match(type2);
}

bool Parser::match(TokenType type1, TokenType type2, TokenType type3, TokenType type4, TokenType type5, TokenType type6)
{
	return match(type1) || match(type2) || match(type3) || match(type4) || match(type5) || match(type6);
}

bool Parser::check(TokenType type)
{
	if (isAtEnd())
	{
		return false;
	}
	return peek().type == type;
}

Token Parser::advance()
{
	if (!isAtEnd())
	{
		current++;
	}
	return previous();
}

bool Parser::isAtEnd()
{
	return peek().type == TokenType::EOF_TOKEN;
}

Token Parser::peek()
{
	return tokens[current];
}

Token Parser::previous()
{
	return tokens[current - 1];
}

Token Parser::consume(TokenType type, const string& message)
{
	if (check(type))
	{
		return advance();
	}

	Token token = peek();
	stringstream ss;
	ss << message << " at line " << token.line << ", column " << token.column
		<< ". Found: " << static_cast<int>(token.type);
	throw runtime_error(ss.str());
}
