#include "CodeGenerator.h"
#include <sstream>
#include <iostream>

using namespace std;

CodeGenerator::CodeGenerator(ostream& out)
	: output(out), indentLevel(0), labelCounter(0)
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

	// Declare all variables at the start (assembly-style)
	writeLine("// Variable declarations");
	for (auto* statement : program->statements)
	{
		if (VarDeclarationStatement* varDecl = dynamic_cast<VarDeclarationStatement*>(statement))
		{
			writeIndent();
			output << "int " << varDecl->variableName << ";" << endl;
		}
	}
	writeLine("");

	// Start label - entry point
	writeIndent();
	output << "L_START:" << endl;
	writeLine("");

	// Generate all statements sequentially
	for (size_t i = 0; i < program->statements.size(); i++)
	{
		Statement* stmt = program->statements[i];
		
		// Add label for this statement (for potential jumps)
		string label = generateLabel("L_STMT");
		statementLabels[stmt] = label;
		writeIndent();
		output << label << ":" << endl;

		generateStatement(stmt);
		writeLine("");
	}

	// End label
	writeIndent();
	output << "L_END:" << endl;
	writeIndent();
	output << "return 0;" << endl;

	indentLevel--;
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
	output << varDecl->variableName << " = " << generateExpression(varDecl->expression) << ";" << endl;
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
	// Assembly-style if: evaluate condition, branch to else or then
	string elseLabel = generateLabel("L_ELSE");
	string endLabel = generateLabel("L_IF_END");
	string conditionLabel = generateLabel("L_COND");

	// Evaluate condition and branch
	writeIndent();
	output << "// if condition" << endl;
	writeIndent();
	output << "if (!(" << generateBooleanExpression(ifStmt->condition) << ")) goto " << elseLabel << ";" << endl;
	writeLine("");

	// Then block
	writeIndent();
	output << "// then block" << endl;
	for (auto* stmt : ifStmt->thenStatements)
	{
		generateStatement(stmt);
	}
	writeIndent();
	output << "goto " << endLabel << ";" << endl;
	writeLine("");

	// Else block (if present)
	if (!ifStmt->elseStatements.empty())
	{
		writeIndent();
		output << elseLabel << ":" << endl;
		writeIndent();
		output << "// else block" << endl;
		for (auto* stmt : ifStmt->elseStatements)
		{
			generateStatement(stmt);
		}
	}
	else
	{
		writeIndent();
		output << elseLabel << ":" << endl;
	}

	writeIndent();
	output << endLabel << ":" << endl;
}

void CodeGenerator::generateWhileStatement(const WhileStatement* whileStmt)
{
	// Assembly-style while: loop label, condition check, body, goto loop
	string loopLabel = generateLabel("L_LOOP");
	string conditionLabel = generateLabel("L_COND");
	string endLabel = generateLabel("L_LOOP_END");

	writeIndent();
	output << "// while loop" << endl;
	writeIndent();
	output << loopLabel << ":" << endl;

	// Condition check
	writeIndent();
	output << "if (!(" << generateBooleanExpression(whileStmt->condition) << ")) goto " << endLabel << ";" << endl;
	writeLine("");

	// Body
	writeIndent();
	output << "// loop body" << endl;
	for (auto* stmt : whileStmt->bodyStatements)
	{
		generateStatement(stmt);
	}

	// Jump back to loop start
	writeIndent();
	output << "goto " << loopLabel << ";" << endl;
	writeLine("");

	// End label
	writeIndent();
	output << endLabel << ":" << endl;
}

string CodeGenerator::generateExpression(Expression* expression)
{
	if (IntegerLiteral* lit = dynamic_cast<IntegerLiteral*>(expression))
	{
		return to_string(lit->value);
	}
	if (InputIntExpression* input = dynamic_cast<InputIntExpression*>(expression))
	{
		return "([]() { int val; cin >> val; return val; })()";
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

string CodeGenerator::generateLabel(const string& prefix)
{
	return prefix + "_" + to_string(labelCounter++);
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

