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
	;;;;;;;;;
	CodeGen_x86_64_fasm_w *generator = new CodeGen_x86_64_fasm_w();
	SyntaxTree* program_tree = new SyntaxTree(generator);
	
	Parser *parser = new Parser(lexical->v_tokens, program_tree); // Release fails here, maybe an unclosed file?
	parser->parse();

	if (parser->err_count > 0) {
		std::cout << "ERROR: PARSING FAILED WITH " << parser->err_count << " ERRORS" << std::endl;
	}
	std::cout << "\n\n\nAbstract Syntax Tree:" << std::endl;
	program_tree->print();
	
	delete parser; //TODO: memory leak here, LLTable does not get deleted
	delete lexical;
	
	std::cout << std::endl;
	std::cout << "Compiling tree" << std::endl << "---------------------" << std::endl;
	program_tree->compileTreeMaster();
	std::cout << std::endl;
	std::cout << "Variable table" << std::endl << "---------------------" << std::endl;
	program_tree->printSymbolTable();
	std::cout << "Function table" << std::endl << "---------------------" << std::endl;
	program_tree->printFunctionTable();

	return 0;
}
