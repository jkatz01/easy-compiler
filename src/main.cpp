#include "Lexer.cpp"
int coolFunction(int n);
/// <summary>
/// Main
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
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
	coolFunction(5);
	return 0;
}

/// <summary>
/// This doesn't do anything i just dont know how to use doxygen
/// </summary>
/// <param name="n"></param>
/// <returns></returns>
int coolFunction(int n) {
	n = n + n;
	return n;
}