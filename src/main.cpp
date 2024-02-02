#include "Lexer.cpp"

#include <iostream>

int main(int argc, char* argv[]) {
	// Assert number of arguments
	if (argc != 2) {
		std::cout << "Incorrect number of arguments." << std::endl;
		return EXIT_FAILURE;
	}
	
	Lexer lexical(argv[1], "Tokens.txt", "Lexical-Errors.txt");
	int lex_err_count = lexical.generateTokens();
	if (lex_err_count > 0) {
		std::cout << "Lexical analysis failed with " << lex_err_count << " errors" << std::endl;
	}
	return 0;
}
