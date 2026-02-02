#pragma once

#include <string>
#include <ostream>
#include "AST.h"

/**
 * CodeGenerator (Transpiler)
 * 
 * Purpose: Generates C++ source code from the AST.
 * 
 * How it works:
 * 1. Traverses the AST nodes
 * 2. Generates equivalent C++ code for each node
 * 3. Outputs to a stream (file or console)
 */
class CodeGenerator
{
	std::ostream& output;
	int indentLevel;

	// Helper methods
	void writeIndent();
	void writeLine(const std::string& line);
	void write(const std::string& text);

	// Generation methods
	void generateStatement(Statement* statement);
	void generateVarDeclaration(const VarDeclarationStatement* varDecl);
	void generateAssignment(const AssignmentStatement* assign);
	void generatePrint(const PrintStatement* print);
	void generatePrintLine(const PrintLineStatement* println);
	void generateIfStatement(const IfStatement* ifStmt);
	void generateWhileStatement(const WhileStatement* whileStmt);
	std::string generateExpression(Expression* expression);
	std::string generateBooleanExpression(const BooleanExpression* boolExpr);

public:
	CodeGenerator(std::ostream& out);

	/**
	 * Generates C++ code from a program AST.
	 * Wraps the generated code in a complete C++ program with main().
	 */
	void generate(ProgramNode* program);
};


