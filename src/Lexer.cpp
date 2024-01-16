#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

enum TokenType {
	T_semicolon,
	T_dot,
	T_comp,
	T_underscore,
	T_operator,
	T_open_par,
	T_close_par,
	T_comma,
	T_keyword,
	T_int,
	T_double,
	T_identifier
};

typedef struct Token {
	TokenType token_type;
	std::string token_value;
} Token;

int tokenizeLine(std::string line, std::unordered_map<char, TokenType> symbol_tokens) {
	// add another parameter vector<Token> to append tokens to.
	// Return 0 on success, EXIT_FAILURE otherwise
	int cursor_one = 0;
	int cursor_two = 0;
	std::string token_value = "";
	char token_char = 0;
	int line_length = line.length();
	/* cursor two continues until it finds a token that isnt a digit / letter
	* identify digits first to check for number */

	while (cursor_two <= line_length) {
		if (std::isspace(line[cursor_two]) || cursor_two == line_length) {
			int distance = cursor_two - cursor_one;
			if (distance > 0 && !std::isspace(line[cursor_one])) {
				token_value = line.substr(cursor_one, distance);
				std::cout << token_value << "- \n";
				// Send this token to check if it is a keyword, number, identifier, etc.
			}
			cursor_one = cursor_two + 1;
		}
		else if (std::isalpha(line[cursor_two])) {
			//check keyword or identifier
		}
		else if (symbol_tokens.find(line[cursor_two]) != symbol_tokens.end()) {
			//std::cout << std::endl << "Found symbol " << line[cursor_two] << std::endl;
			int distance = cursor_two - cursor_one;
			token_value = line.substr(cursor_one, distance);
			token_char = line[cursor_two];
			// print the previous token and the symbol
			if (!std::isspace(token_value[0])) {
				std::cout << token_value << "- \n"; //check that this isnt empty
			}
			std::cout << token_char << "- \n";

			cursor_one = cursor_two + 1;

		}
		else {
			//std::cout << "bad character: " << line[cursor_two] << " not allowed\n";
			//return -1;
		}
		cursor_two++;

	}
	//std::cout << std::endl;

	return 0;
}

int main(int argc, char* argv[]) {
	// Check number of arguments
	if (argc != 2) {
		std::cout << "Incorrect number of arguments." << std::endl;
		return EXIT_FAILURE;
	}

	// Define a hashmap with all the tokens
	std::unordered_map<char, TokenType> symbol_tokens = {
		{';', T_semicolon},
		{'.', T_semicolon},
		{'_', T_underscore},
		{'=', T_comp},
		{'<', T_comp},
		{'>', T_comp},
		{'+', T_operator},
		{'-', T_operator},
		{'*', T_operator},
		{'/', T_operator},
		{'%', T_operator},
		{'(', T_open_par},
		{')', T_close_par},
		{',', T_comma},
	};

	std::unordered_map<std::string, TokenType> key_words = {
		{"def", T_keyword},
		{"fed", T_keyword},
		{"if", T_keyword},
		{"else", T_keyword},
		{"fi", T_keyword},
		{"while", T_keyword},
		{"do", T_keyword},
		{"od", T_keyword},
		{"print", T_keyword},
		{"return", T_keyword},
		{"or", T_keyword},
		{"and", T_keyword},
		{"not", T_keyword},
		{"int", T_keyword},
		{"double", T_keyword},
	};

	// Read file
	std::string line;
	std::ifstream source_file;
	source_file.open(argv[1]); // add measuring time
	while (std::getline(source_file, line)) {
		tokenizeLine(line, symbol_tokens);
	}
	source_file.close();

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
