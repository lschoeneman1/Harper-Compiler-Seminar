#pragma once

#include <string>
#include <ostream>
#include <map>
#include "AST.h"

/**
 * CodeGenerator (Assembly-style Transpiler)
 * 
 * Purpose: Generates C++ code with goto statements and labels,
 * treating C++ as an assembly language replacement.
 * 
 * How it works:
 * 1. Traverses the AST nodes
 * 2. Generates assembly-like C++ code with labels and gotos
 * 3. Uses explicit control flow (no structured if/while)
 */
class CodeGenerator
{
	std::ostream& output;
	int indentLevel;
	int labelCounter;
	std::map<const Statement*, std::string> statementLabels;

	// Helper methods
	void writeIndent();
	void writeLine(const std::string& line);
	void write(const std::string& text);
	std::string generateLabel(const std::string& prefix);

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
	 * Generates assembly-style C++ code from a program AST.
	 * Uses goto statements and labels instead of structured control flow.
	 */
	void generate(ProgramNode* program);
};


