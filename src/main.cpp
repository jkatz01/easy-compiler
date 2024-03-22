#include "Lexer.cpp"
#include "Parser.cpp"

#include <iostream>

int main(int argc, char* argv[]) {
	// Assert number of arguments
	if (argc != 2) {
		std::cout << "Incorrect number of arguments." << std::endl;
		return EXIT_FAILURE;
	}
	
	Lexer *lexical = new Lexer(argv[1], "Tokens.txt", "Lexical-Errors.txt");
	int lex_err_count = lexical->generateTokens();

	if (lex_err_count > 0) {
		std::cout << "Lexical analysis failed with " << lex_err_count << " errors" << std::endl;
	}
	;;;
	SyntaxTree* program_tree = new SyntaxTree();
	;;
	Parser *parser = new Parser(lexical->v_tokens, program_tree);
	parser->parse();
	
	delete parser;
	
	program_tree->buildSymbolTable(program_tree->getRoot(), false);

	std::cout << std::endl;
	std::cout << "Created Symbol Table" << std::endl << "---------------------" << std::endl;
	program_tree->printSymbolTable();

	std::cout << std::endl;
	std::cout << "Checking Symbols in Symbol Table" << std::endl << "---------------------" << std::endl;
	program_tree->checkSymbolReferences(program_tree->getRoot(), false);

	std::cout << std::endl;
	std::cout << "Type Checking" << std::endl << "---------------------" << std::endl;
	program_tree->typeCheckTree(program_tree->getRoot());

	return 0;
}
