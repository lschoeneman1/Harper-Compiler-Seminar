#include "Evaluator.h"
#include <iostream>
#include <stdexcept>
#include <sstream>

using namespace std;

void Evaluator::evaluate(ProgramNode* program)
{
	for (auto& statement : program->statements)
	{
		evaluateStatement(statement);
	}
}

void Evaluator::evaluateStatement(Statement* statement)
{
	if (VarDeclarationStatement* varDecl = dynamic_cast<VarDeclarationStatement*>(statement))
	{
		evaluateVarDeclaration(varDecl);
	}
	else if (AssignmentStatement* assign = dynamic_cast<AssignmentStatement*>(statement))
	{
		evaluateAssignment(assign);
	}
	else if (PrintStatement* print = dynamic_cast<PrintStatement*>(statement))
	{
		evaluatePrint(print);
	}
	else if (PrintLineStatement* println = dynamic_cast<PrintLineStatement*>(statement))
	{
		evaluatePrintLine(println);
	}
	else if (IfStatement* ifStmt = dynamic_cast<IfStatement*>(statement))
	{
		evaluateIfStatement(ifStmt);
	}
	else if (WhileStatement* whileStmt = dynamic_cast<WhileStatement*>(statement))
	{
		evaluateWhileStatement(whileStmt);
	}
	else
	{
		throw runtime_error("Unknown statement type");
	}
}

void Evaluator::evaluateVarDeclaration(const VarDeclarationStatement* varDecl)
{
	int value = evaluateExpression(varDecl->expression);
	symbolTable[varDecl->variableName] = value;
}

void Evaluator::evaluateAssignment(const AssignmentStatement* assign)
{
	int value = evaluateExpression(assign->expression);
	symbolTable[assign->variableName] = value;
}

void Evaluator::evaluatePrint(const PrintStatement* print)
{
	int value = evaluateExpression(print->expression);
	cout << value;  // No newline for print
}

void Evaluator::evaluatePrintLine(const PrintLineStatement* println)
{
	int value = evaluateExpression(println->expression);
	cout << value << '\n';  // Newline for println
}

int Evaluator::evaluateExpression(Expression* expression)
{
	if (IntegerLiteral* lit = dynamic_cast<IntegerLiteral*>(expression))
	{
		return lit->value;
	}
	if (InputIntExpression* input = dynamic_cast<InputIntExpression*>(expression))
	{
		return evaluateInputInt();
	}
	if (VariableReference* varRef = dynamic_cast<VariableReference*>(expression))
	{
		return evaluateVariable(varRef);
	}
	if (BinaryExpression* binExpr = dynamic_cast<BinaryExpression*>(expression))
	{
		return evaluateBinaryExpression(binExpr);
	}
	if (BooleanExpression* boolExpr = dynamic_cast<BooleanExpression*>(expression))
	{
		return evaluateBooleanExpression(boolExpr) ? 1 : 0;
	}
	throw runtime_error("Unknown expression type");
}

int Evaluator::evaluateInputInt()
{
	string input;
	getline(cin, input);
	try
	{
		return stoi(input);
	}
	catch (const exception&)
	{
		throw runtime_error("Invalid integer input: " + input);
	}
}

int Evaluator::evaluateVariable(const VariableReference* varRef)
{
	auto it = symbolTable.find(varRef->name);
	if (it == symbolTable.end())
	{
		stringstream ss;
		ss << "Undefined variable: " << varRef->name;
		throw runtime_error(ss.str());
	}
	return it->second;
}

int Evaluator::evaluateBinaryExpression(const BinaryExpression* binExpr)
{
	int left = evaluateExpression(binExpr->left);
	int right = evaluateExpression(binExpr->right);

	if (binExpr->op == "+")
	{
		return left + right;
	}
	if (binExpr->op == "-")
	{
		return left - right;
	}
	if (binExpr->op == "*")
	{
		return left * right;
	}
	if (binExpr->op == "/")
	{
		if (right == 0)
		{
			throw runtime_error("Division by zero");
		}
		return left / right;
	}
	stringstream ss;
	ss << "Unknown operator: " << binExpr->op;
	throw runtime_error(ss.str());
}

bool Evaluator::evaluateBooleanExpression(const BooleanExpression* boolExpr)
{
	int left = evaluateExpression(boolExpr->left);
	int right = evaluateExpression(boolExpr->right);

	if (boolExpr->op == "==")
	{
		return left == right;
	}
	if (boolExpr->op == "!=")
	{
		return left != right;
	}
	if (boolExpr->op == "<")
	{
		return left < right;
	}
	if (boolExpr->op == ">")
	{
		return left > right;
	}
	if (boolExpr->op == "<=")
	{
		return left <= right;
	}
	if (boolExpr->op == ">=")
	{
		return left >= right;
	}
	stringstream ss;
	ss << "Unknown comparison operator: " << boolExpr->op;
	throw runtime_error(ss.str());
}

void Evaluator::evaluateIfStatement(const IfStatement* ifStmt)
{
	bool condition = evaluateBooleanExpression(ifStmt->condition);

	if (condition)
	{
		// Execute then block
		for (auto* stmt : ifStmt->thenStatements)
		{
			evaluateStatement(stmt);
		}
	}
	else if (!ifStmt->elseStatements.empty())
	{
		// Execute else block
		for (auto* stmt : ifStmt->elseStatements)
		{
			evaluateStatement(stmt);
		}
	}
}

void Evaluator::evaluateWhileStatement(const WhileStatement* whileStmt)
{
	while (evaluateBooleanExpression(whileStmt->condition))
	{
		// Execute body block
		for (auto* stmt : whileStmt->bodyStatements)
		{
			evaluateStatement(stmt);
		}
	}
}
