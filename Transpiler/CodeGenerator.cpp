#include "CodeGenerator.h"
#include <sstream>
#include <iostream>

using namespace std;

CodeGenerator::CodeGenerator(ostream& out)
	: output(out), indentLevel(0)
{
}

void CodeGenerator::generate(ProgramNode* program)
{
	// Write C++ header
	writeLine("#include <iostream>");
	writeLine("#include <string>");
	writeLine("using namespace std;");
	writeLine("");
	writeLine("int main() {");
	indentLevel++;

	// Generate all statements
	for (auto* statement : program->statements)
	{
		generateStatement(statement);
	}

	indentLevel--;
	writeLine("    return 0;");
	writeLine("}");
}

void CodeGenerator::generateStatement(Statement* statement)
{
	if (VarDeclarationStatement* varDecl = dynamic_cast<VarDeclarationStatement*>(statement))
	{
		generateVarDeclaration(varDecl);
	}
	else if (AssignmentStatement* assign = dynamic_cast<AssignmentStatement*>(statement))
	{
		generateAssignment(assign);
	}
	else if (PrintStatement* print = dynamic_cast<PrintStatement*>(statement))
	{
		generatePrint(print);
	}
	else if (PrintLineStatement* println = dynamic_cast<PrintLineStatement*>(statement))
	{
		generatePrintLine(println);
	}
	else if (IfStatement* ifStmt = dynamic_cast<IfStatement*>(statement))
	{
		generateIfStatement(ifStmt);
	}
	else if (WhileStatement* whileStmt = dynamic_cast<WhileStatement*>(statement))
	{
		generateWhileStatement(whileStmt);
	}
}

void CodeGenerator::generateVarDeclaration(const VarDeclarationStatement* varDecl)
{
	writeIndent();
	output << "int " << varDecl->variableName << " = " << generateExpression(varDecl->expression) << ";" << endl;
}

void CodeGenerator::generateAssignment(const AssignmentStatement* assign)
{
	writeIndent();
	output << assign->variableName << " = " << generateExpression(assign->expression) << ";" << endl;
}

void CodeGenerator::generatePrint(const PrintStatement* print)
{
	writeIndent();
	output << "cout << " << generateExpression(print->expression) << ";" << endl;
}

void CodeGenerator::generatePrintLine(const PrintLineStatement* println)
{
	writeIndent();
	output << "cout << " << generateExpression(println->expression) << " << endl;" << endl;
}

void CodeGenerator::generateIfStatement(const IfStatement* ifStmt)
{
	writeIndent();
	output << "if (" << generateBooleanExpression(ifStmt->condition) << ") {" << endl;
	indentLevel++;

	// Generate then block
	for (auto* stmt : ifStmt->thenStatements)
	{
		generateStatement(stmt);
	}

	indentLevel--;
	writeIndent();
	output << "}";

	// Generate else block if present
	if (!ifStmt->elseStatements.empty())
	{
		output << " else {" << endl;
		indentLevel++;

		for (auto* stmt : ifStmt->elseStatements)
		{
			generateStatement(stmt);
		}

		indentLevel--;
		writeIndent();
		output << "}";
	}

	output << endl;
}

void CodeGenerator::generateWhileStatement(const WhileStatement* whileStmt)
{
	writeIndent();
	output << "while (" << generateBooleanExpression(whileStmt->condition) << ") {" << endl;
	indentLevel++;

	// Generate body block
	for (auto* stmt : whileStmt->bodyStatements)
	{
		generateStatement(stmt);
	}

	indentLevel--;
	writeIndent();
	output << "}" << endl;
}

string CodeGenerator::generateExpression(Expression* expression)
{
	if (IntegerLiteral* lit = dynamic_cast<IntegerLiteral*>(expression))
	{
		return to_string(lit->value);
	}
	if (InputIntExpression* input = dynamic_cast<InputIntExpression*>(expression))
	{
		return "stoi(cin.getline())";  // Simplified - would need proper input handling
	}
	if (VariableReference* varRef = dynamic_cast<VariableReference*>(expression))
	{
		return varRef->name;
	}
	if (BinaryExpression* binExpr = dynamic_cast<BinaryExpression*>(expression))
	{
		string left = generateExpression(binExpr->left);
		string right = generateExpression(binExpr->right);
		return "(" + left + " " + binExpr->op + " " + right + ")";
	}
	if (BooleanExpression* boolExpr = dynamic_cast<BooleanExpression*>(expression))
	{
		return generateBooleanExpression(boolExpr);
	}
	return "/* unknown expression */";
}

string CodeGenerator::generateBooleanExpression(const BooleanExpression* boolExpr)
{
	string left = generateExpression(boolExpr->left);
	string right = generateExpression(boolExpr->right);
	return "(" + left + " " + boolExpr->op + " " + right + ")";
}

void CodeGenerator::writeIndent()
{
	for (int i = 0; i < indentLevel; i++)
	{
		output << "    ";
	}
}

void CodeGenerator::writeLine(const string& line)
{
	writeIndent();
	output << line << endl;
}

void CodeGenerator::write(const string& text)
{
	output << text;
}


