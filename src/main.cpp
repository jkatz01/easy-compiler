#include "Lexer.cpp"

int main() {
	Lexer lexical(".\\tests\\example.txt", "Tokens.txt", "Lexical-Errors.txt");
	lexical.generateTokens();
	;;;
	return 0;
}