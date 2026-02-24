#pragma once 

#include <unordered_map>
#include <string>
#include "AST.h"

/**
 * Evaluator (Interpreter)
 * 
 * Purpose: Executes the AST to produce program output.
 * 
 * How it works:
 * 1. Traverses the AST nodes
 * 2. Evaluates expressions (computes values)
 * 3. Manages variable storage (symbol table)
 * 4. Executes statements (assignments, prints)
 */
class Evaluator
{
	// Symbol table: stores variable names and their values
	// This is like a dictionary: variable name → value
	std::unordered_map<std::string, int> symbolTable;

	// Helper methods
	void evaluateStatement(Statement* statement);
	void evaluateVarDeclaration(const VarDeclarationStatement* varDecl);
	void evaluateAssignment(const AssignmentStatement* assign);
	void evaluatePrint(const PrintStatement* print);
	void evaluatePrintLine(const PrintLineStatement* println);
	void evaluateIfStatement(const IfStatement* ifStmt);
	void evaluateWhileStatement(const WhileStatement* whileStmt);
	int evaluateExpression(Expression* expression);
	bool evaluateBooleanExpression(const BooleanExpression* boolExpr);
	int evaluateInputInt();
	int evaluateVariable(const VariableReference* varRef);
	int evaluateBinaryExpression(const BinaryExpression* binExpr);

public:
	/**
	 * Evaluates a program by executing all its statements.
	 */
	void evaluate(ProgramNode* program);
};
