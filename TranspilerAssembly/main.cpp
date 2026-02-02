#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Lexer.h"
#include "Parser.h"
#include "CodeGenerator.h"

using namespace std;

/**
 * Main entry point for the MidLang to C++ assembly-style transpiler.
 * 
 * This program:
 * 1. Reads MidLang source code
 * 2. Tokenizes it (Lexer)
 * 3. Parses it into an AST (Parser)
 * 4. Generates assembly-style C++ code with gotos and labels (CodeGenerator)
 */
int main(int argc, char* argv[])
{
	string sourceFile;
	string outputFile;

	if (argc < 2)
	{
		cout << "Usage: transpiler_asm <input.mid> [output.cpp]" << endl;
		cout << "Example: transpiler_asm program.mid program.cpp" << endl;
		cout << endl;
		cout << "This transpiler generates C++ code using goto statements" << endl;
		cout << "and labels, treating C++ as an assembly language replacement." << endl;
		return 1;
	}

	sourceFile = argv[1];
	
	if (argc >= 3)
	{
		outputFile = argv[2];
	}
	else
	{
		// Default output: same name with .cpp extension
		outputFile = sourceFile;
		size_t lastDot = outputFile.find_last_of('.');
		if (lastDot != string::npos)
		{
			outputFile = outputFile.substr(0, lastDot) + ".cpp";
		}
		else
		{
			outputFile += ".cpp";
		}
	}

	ifstream file(sourceFile);
	if (!file.is_open())
	{
		cerr << "Error: File not found: " << sourceFile << endl;
		return 1;
	}

	try
	{
		// Read source code
		stringstream buffer;
		buffer << file.rdbuf();
		string sourceCode = buffer.str();
		file.close();

		cout << "=== Transpiling (Assembly-style): " << sourceFile << " ===" << endl;

		// Stage 1: Lexical Analysis
		cout << "Stage 1: Lexical Analysis (Tokenization)..." << endl;
		Lexer lexer(sourceCode);
		auto tokens = lexer.tokenize();
		cout << "Generated " << tokens.size() << " tokens" << endl;

		// Stage 2: Parsing
		cout << "Stage 2: Parsing (Building AST)..." << endl;
		Parser parser(tokens);
		auto ast = parser.parse();
		cout << "Parsed " << ast->statements.size() << " statement(s)" << endl;

		// Stage 3: Code Generation
		cout << "Stage 3: Code Generation (Assembly-style)..." << endl;
		ofstream outFile(outputFile);
		if (!outFile.is_open())
		{
			cerr << "Error: Cannot create output file: " << outputFile << endl;
			return 1;
		}

		CodeGenerator generator(outFile);
		generator.generate(ast);
		outFile.close();

		cout << "Generated assembly-style C++ code: " << outputFile << endl;
		cout << "=== Transpilation completed successfully ===" << endl;
	}
	catch (const exception& ex)
	{
		cerr << "Error: " << ex.what() << endl;
		return 1;
	}

	return 0;
}


