#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <chrono>
#include <regex>

#define NUM_TOKEN_TYPES 14

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

class Lexer {
	public: 
		int line_number;
		int token_count;
		std::vector<Token*> v_tokens;

		Lexer(std::string src_file, std::string out_file, std::string error_file) {
			source_file_name = src_file;
			output_file_name = out_file;
			error_file_name = error_file;
			line_number = 0;
			token_count = 0;
			cursor_one = 0;
			cursor_two = 0;
		}

		int generateTokens() {
			std::cout << "test" << std::endl;
			return 0;
		}

		int printTokens() {

		}

	private:
		int cursor_one;
		int cursor_two;
		std::string source_file_name;
		std::string output_file_name;
		std::string error_file_name;
		std::ifstream source_file;
		std::ofstream output_file;
		std::ofstream error_file;

		const std::unordered_map<char, TokenType> symbols = {
			{';', T_semicolon},
			{'.', T_dot},
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
			{',', T_comma}
		};
		const std::unordered_map<std::string, TokenType> keywords = {
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
		const std::string enum_names[NUM_TOKEN_TYPES] = { "T_semicolon","T_dot","T_comp","T_underscore","T_operator","T_open_par","T_close_par","T_comma","T_keyword","T_int","T_double","T_identifier","T_temp", "T_invalid" };

		int tokenizeLine(std::string& line) {

		}

		int addToken(std::string& line, bool last_is_symbol, int start, int distance, TokenType symbol_type) {

		}

		TokenType findTokenType(std::string& str) {

		}

};