#include "Lexer.cpp"

int main() {
	Lexer lexical("example.txt", "Tokens.txt", "Lexical-Errors.txt");
	lexical.generateTokens();
}