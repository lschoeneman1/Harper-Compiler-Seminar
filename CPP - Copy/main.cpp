#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Lexer.h"
#include "Parser.h"
#include "Evaluator.h"

using namespace std;
/**
 * Main entry point for the MidLang Stage 4 interpreter.
 * 
 * This program demonstrates the three-stage interpreter architecture:
 * 1. Lexer: Converts source code to tokens
 * 2. Parser: Builds AST from tokens
 * 3. Evaluator: Executes AST
 */
int main(int argc, char* argv[])
{
	string sourceFile;
	if (argc < 2)
	{
		sourceFile = "Examples\\stage4_example1.mid";
	/*	cout << "Usage: midc <source_file.mid>" << '\n';
		cout << "Example: midc examples/program.mid" << '\n';
		return 1;*/
	}
	else
	{
		sourceFile = argv[1];
	}

	ifstream file(sourceFile);
	if (!file.is_open())
	{
		cerr << "Error: File not found: " << sourceFile << '\n';
		return 1;
	}

	try
	{
		// Read source code
		stringstream buffer;
		buffer << file.rdbuf();
		string sourceCode = buffer.str();
		file.close();

		cout << "=== Interpreting: " << sourceFile << " ===" << '\n' << '\n';

		// Stage 1: Lexical Analysis
		cout << "Stage 1: Lexical Analysis (Tokenization)" << '\n';
		Lexer lexer(sourceCode);
		auto tokens = lexer.tokenize();
		cout << "Generated " << tokens.size() << " tokens:" << '\n';
		for (const auto& token : tokens)
		{
			if (token.type != TokenType::EOF_TOKEN)
			{
				// Convert token type to string for readability
				string typeStr;
				switch (token.type)
				{
					case TokenType::INTEGER: typeStr = "INTEGER";
						break;
					case TokenType::IDENTIFIER: typeStr = "IDENTIFIER";
						break;
					case TokenType::PLUS: typeStr = "PLUS";
						break;
					case TokenType::MINUS: typeStr = "MINUS";
						break;
					case TokenType::MULTIPLY: typeStr = "MULTIPLY";
						break;
					case TokenType::DIVIDE: typeStr = "DIVIDE";
						break;
					case TokenType::ASSIGN: typeStr = "ASSIGN";
						break;
					case TokenType::SEMICOLON: typeStr = "SEMICOLON";
						break;
					case TokenType::LEFT_PAREN: typeStr = "LEFT_PAREN";
						break;
					case TokenType::RIGHT_PAREN: typeStr = "RIGHT_PAREN";
						break;
					case TokenType::VAR: typeStr = "VAR";
						break;
					case TokenType::PRINT: typeStr = "PRINT";
						break;
					case TokenType::INPUT_INT: typeStr = "INPUT_INT";
						break;
					default: typeStr = "UNKNOWN";
						break;
				}
				cout << "  " << typeStr << "(" << token.value << ")" << '\n';
			}
		}
		cout << '\n';

		// Stage 2: Parsing
		cout << "Stage 2: Parsing (Building AST)" << '\n';
		Parser parser(tokens);
		auto ast = parser.parse();
		cout << "Parsed " << ast->statements.size() << " statement(s)" << '\n';
		cout << '\n';

		// Stage 3: Evaluation
		cout << "Stage 3: Evaluation (Execution)" << '\n';
		cout << "Output:" << '\n';
		Evaluator evaluator;
		evaluator.evaluate(ast);
		cout << '\n';

		cout << "=== Program completed successfully ===" << '\n';
	}
	catch (const exception& ex)
	{
		cerr << "Error: " << ex.what() << '\n';
		return 1;
	}

	return 0;
}
