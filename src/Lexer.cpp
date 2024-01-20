#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <chrono>

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

int printToken(std::string line, bool last_is_symbol, int start, int distance, std::vector<Token> v_tokens) {
	std::string token_value = line.substr(start, distance);
	char last_char = line[start + distance];
	if (token_value.compare("")) {
		std::cout << token_value << std::endl;
	}
	if (last_is_symbol == true) {
		std::cout << last_char << std::endl;
	}
	return 0;
}

int tokenizeLine(std::string line, std::unordered_map<char, TokenType> symbol_tokens, std::vector<Token> v_tokens) {
	// add another parameter vector<Token> to append tokens to.
	// Return 0 on success, EXIT_FAILURE otherwise
	int cursor_one = 0;
	int cursor_two = 0;
	std::string token_value = "";
	char token_char = 0;
	int distance;
	int success;
	size_t line_length = line.length();

	while (cursor_two <= line_length) {
		if (std::isspace(line[cursor_two]) || cursor_two == line_length) {
			distance = cursor_two - cursor_one;
			if (distance > 0 && !std::isspace(line[cursor_one])) {
				success = printToken(line, false, cursor_one, distance, v_tokens);
			}
			cursor_one = cursor_two + 1;
		}
		else if (std::isalnum(line[cursor_two])) {
			//check keyword or identifier
		}
		else if (symbol_tokens.find(line[cursor_two]) != symbol_tokens.end()) {
			// special case for a dot: double
			distance = cursor_two - cursor_one;
			token_char = line[cursor_two];

			// print the previous token and the symbol
			if (token_char == '.' && cursor_two < line_length && std::isdigit(line[cursor_two + 1])) {
				;
			}
			else if (token_char == '_') {
				;
			}
			else {
				success = printToken(line, true, cursor_one, distance, v_tokens);
				cursor_one = cursor_two + 1;
			}
		}
		else {
			int distance = cursor_two - cursor_one;
			token_value = line.substr(cursor_one, distance);
			token_char = line[cursor_two];

			if (token_value.compare("") != 0) std::cout << token_value << std::endl;
			std::cout << "Bad character " << token_char << std::endl;
			cursor_one = cursor_two + 1;
		}
		cursor_two++;

	}

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
	// Measure time
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	// Read file
	std::string line;
	std::ifstream source_file;
	source_file.open(argv[1]); // add measuring time

	std::vector<Token> v_tokens;
	// Change this to read entire file/page with rdbuf
	// and make a method to feed lines into the function
	while (std::getline(source_file, line)) {
		tokenizeLine(line, symbol_tokens, v_tokens);
	}
	source_file.close();

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
	
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
