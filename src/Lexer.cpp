#include "definitions.h"

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
			bytes_read = 0;
		}

		int generateTokens() {
			source_file.open(source_file_name);
			if (!source_file.is_open()) {
				std::cout << "Failed to load file" << std::endl;
				exit(EXIT_FAILURE);
			}
			std::streamsize file_size = source_file.tellg();
			source_file.seekg(0, std::ios::beg);
			char buffer[PAGE_SIZE];
			int read_count = 0;
			while (!source_file.eof()) {
				source_file.read(buffer, sizeof(buffer));
				bytes_read = source_file.gcount();
				std::string content(buffer, bytes_read);
				tokenizeLine(content, bytes_read);
			}
			
			
			return 0;
		}

		int printTokens() {

		}

	private:
		int cursor_one;
		int cursor_two;
		size_t bytes_read;
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

		int tokenizeLine(std::string& line, size_t size) {
			std::cout << line;
			return 0;
		}

		int addToken(std::string& line, bool last_is_symbol, int start, int distance, TokenType symbol_type) {

		}

		TokenType findTokenType(std::string& str) {

		}

};