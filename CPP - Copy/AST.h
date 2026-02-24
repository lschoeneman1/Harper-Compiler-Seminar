#pragma once

#include <vector>
#include <string>
#include <memory>

using namespace std;

/**
 * Abstract Syntax Tree (AST) nodes.
 * The AST represents the structure of the program.
 */

// Forward declarations
class Statement;
class Expression;

/**
 * Root node representing an entire program.
 */
class ProgramNode
{
public:
	vector<Statement*> statements;

	ProgramNode(vector<Statement*> stmts)
		: statements(stmts)
	{
	}
};

/**
 * Base class for all statements.
 */
class Statement
{
public:
	virtual ~Statement() = default;
};

/**
 * Variable declaration statement: var identifier = expression;
 */
class VarDeclarationStatement : public Statement
{
public:
	string variableName;
	Expression* expression;

	VarDeclarationStatement(const string& name, Expression* expr)
		: variableName(name), expression(expr)
	{
	}
};

/**
 * Assignment statement: identifier = expression;
 */
class AssignmentStatement : public Statement
{
public:
	string variableName;
	Expression* expression;

	AssignmentStatement(const string& name, Expression* expr)
		: variableName(name), expression(expr)
	{
	}
};

/**
 * Print statement: print(expression);
 */
class PrintStatement : public Statement
{
public:
	Expression* expression;

	PrintStatement(Expression* expr)
		: expression(expr)
	{
	}
};

/**
 * Base class for all expressions.
 */
class Expression
{
public:
	virtual ~Expression() = default;
};

/**
 * Integer literal: 42, -10
 */
class IntegerLiteral : public Expression
{
public:
	int value;

	IntegerLiteral(int v) : value(v)
	{
	}
};

/**
 * Variable reference: x, count
 */
class VariableReference : public Expression
{
public:
	string name;

	VariableReference(const string& n) : name(n)
	{
	}
};

/**
 * Binary expression: left operator right
 * Examples: a + b, x * 5, (10 + 5) / 2
 */
class BinaryExpression : public Expression
{
public:
	Expression* left;
	string op; // "+", "-", "*", "/"
	Expression* right;

	BinaryExpression(Expression* l, const string& o, Expression* r)
		: left(l), op(o), right(r)
	{
	}
};

/**
 * Input expression: inputInt()
 * Reads an integer from the console.
 */
class InputIntExpression : public Expression
{
public:
	InputIntExpression()
	{
	}
};

/**
 * Boolean expression: expression comparisonOperator expression
 * Examples: x == 5, y < 10, z != 0
 */
class BooleanExpression : public Expression
{
public:
	Expression* left;
	string op; // "==", "!=", "<", ">", "<=", ">="
	Expression* right;

	BooleanExpression(Expression* l, const string& o, Expression* r)
		: left(l), op(o), right(r)
	{
	}
};

/**
 * Print line statement: println(expression);
 */
class PrintLineStatement : public Statement
{
public:
	Expression* expression;

	PrintLineStatement(Expression* expr)
		: expression(expr)
	{
	}
};

/**
 * If statement: if (condition) { statements } [ else { statements } ]
 */
class IfStatement : public Statement
{
public:
	BooleanExpression* condition;
	vector<Statement*> thenStatements;
	vector<Statement*> elseStatements; // empty if no else clause

	IfStatement(BooleanExpression* cond, vector<Statement*> thenStmts, vector<Statement*> elseStmts = {})
		: condition(cond), thenStatements(thenStmts), elseStatements(elseStmts)
	{
	}
};

/**
 * While statement: while (condition) { statements }
 */
class WhileStatement : public Statement
{
public:
	BooleanExpression* condition;
	vector<Statement*> bodyStatements;

	WhileStatement(BooleanExpression* cond, vector<Statement*> bodyStmts)
		: condition(cond), bodyStatements(bodyStmts)
	{
	}
};