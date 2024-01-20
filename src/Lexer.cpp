#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <chrono>
#include <regex>

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
	T_identifier,
	T_temp,
	T_invalid
};

typedef struct Token {
	TokenType token_type;
	std::string token_value;
} Token;


TokenType findTokenType(std::string str, std::unordered_map<std::string, TokenType> &keywords) {
	std::regex r_identifier("[a-zA-Z_][a-zA-z0-9]*");
	std::regex r_double("[0-9]+\\.[0-9]+");
	std::regex r_int("[0-9]+");
	auto search = keywords.find(str);
	if (search != keywords.end()) {
		return T_keyword;
	}
	else if (std::regex_match(str, r_identifier)) {
		return T_identifier;
	}
	else if (std::regex_match(str, r_int)) {
		return T_int;
	}
	else if (std::regex_match(str, r_double)) {
		return T_double;
	}
	else {
		return T_invalid;
	}
	
}

int addToken(std::string line, bool last_is_symbol, int start, int distance, std::vector<Token*> &v_tokens, std::unordered_map<std::string, TokenType> &keywords, TokenType symbol_type) {
	std::string token_value = line.substr(start, distance);
	char last_char = line[start + distance];

	if (token_value.compare("")) {
		TokenType t_val_type = findTokenType(token_value, keywords);

		Token* current_token = new Token;
		current_token->token_type = t_val_type;
		current_token->token_value = token_value;
		v_tokens.push_back(current_token);
	}
	if (last_is_symbol == true) {
		std::string s(1, last_char);
		TokenType char_val_type = symbol_type;

		Token* current_token = new Token;
		current_token->token_type = char_val_type;
		current_token->token_value = s;
		v_tokens.push_back(current_token);
	}
	return 0;
}

int tokenizeLine(std::string line, std::vector<Token*> &v_tokens, std::unordered_map<char, TokenType> &symbols, std::unordered_map<std::string, TokenType> &keywords, int line_num) {
	// add another parameter vector<Token> to append tokens to.
	// Return 0 on success, EXIT_FAILURE otherwise
	int cursor_one = 0;
	int cursor_two = 0;
	std::string token_value = "";
	char token_char = 0;
	int token_count = 0;
	int distance;
	int success;
	size_t line_length = line.length();

	while (cursor_two <= line_length) {
		auto search = symbols.find(line[cursor_two]);
		if (std::isspace(line[cursor_two]) || cursor_two == line_length) {
			distance = cursor_two - cursor_one;
			if (distance > 0 && !std::isspace(line[cursor_one])) {
				success = addToken(line, false, cursor_one, distance, v_tokens, keywords, T_temp);
				token_count++;
			}
			cursor_one = cursor_two + 1;
		}
		else if (std::isalnum(line[cursor_two])) {
			//check keyword or identifier
		}
		else if (search != symbols.end()) {
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
				success = addToken(line, true, cursor_one, distance, v_tokens, keywords, search->second);
				token_count += 2;

				cursor_one = cursor_two + 1;
			}
		}
		else {
			int distance = cursor_two - cursor_one;
			token_char = line[cursor_two];
			addToken(line, false, cursor_one, distance, v_tokens, keywords, T_invalid);
			token_count++;
			std::cout << "Bad character " << token_char <<  " at line " << line_num << std::endl;
			cursor_one = cursor_two + 1;
		}
		cursor_two++;

	}

	return token_count;
}

int main(int argc, char* argv[]) {
	// Check number of arguments
	if (argc != 2) {
		std::cout << "Incorrect number of arguments." << std::endl;
		return EXIT_FAILURE;
	}

	// Define a hashmap with all the tokens
	std::unordered_map<char, TokenType> symbols = {
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

	std::unordered_map<std::string, TokenType> keywords = {
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
	std::string enum_names[] = { "T_semicolon","T_dot","T_comp","T_underscore","T_operator","T_open_par","T_close_par","T_comma","T_keyword","T_int","T_double","T_identifier","T_temp", "T_invalid"};
	// Measure time
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	// Read file
	std::string line;
	std::ifstream source_file;
	source_file.open(argv[1]); // add measuring time
	if (!source_file.is_open()) {
		std::cout << "Failed to open file.\n";
	}

	std::vector<Token*> v_tokens;
	// Change this to read entire file/page with rdbuf
	// and make a method to feed lines into the function
	int token_count = 0;
	int line_num = 0;
	while (std::getline(source_file, line)) {
		token_count += tokenizeLine(line, v_tokens, symbols, keywords, line_num);
		line_num++;
	}
	source_file.close();

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	double time_taken = (double)std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
	time_taken = time_taken / 1000;

	std::cout << "Generated " << token_count << " tokens in : " << time_taken << "[ms]" << std::endl;

	for (Token* i : v_tokens) {
		std::cout << "\t" << i->token_value << "\t\t-\t" << enum_names[i->token_type] << std::endl;
	}
	
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
