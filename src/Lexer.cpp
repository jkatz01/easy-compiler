#include "definitions.h"

class Lexer {
	public: 
		int line_number;
		int token_count;
		std::vector<Token> v_tokens;

		Lexer() {
			source_file_name = "src_file.txt";
			output_file_name = "out_file.txt";
			error_file_name = "error_file.txt";
			line_number = 0;
			token_count = 0;
			cursor_one = 0;
			cursor_two = 0;
			bytes_read = 0;
		}

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

		~Lexer() {
			// Destructor
			if (source_file.is_open()) {
				source_file.close();
			}
			if (output_file.is_open()) {
				output_file.close();
			}
			if (error_file.is_open()) {
				error_file.close();
			}
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

			output_file.open(output_file_name, std::ios::out | std::ios::trunc);
			error_file.open(error_file_name, std::ios::out | std::ios::trunc);

			while (!source_file.eof()) {
				source_file.read(buffer, sizeof(buffer));
				bytes_read = source_file.gcount();
				std::string content(buffer, bytes_read);
				tokenizeLine(content, bytes_read);
			}

			printTokens();
			
			source_file.close();
			output_file.close();
			error_file.close();

			return 0;
		}

		int printTokens() {
			for (Token i : v_tokens) {
				std::cout << i.token_value << std::endl;
				int tab_num;
				if ((tab_num = 3 - (i.token_value.length() / 4)) < 0) {
					tab_num = 0;
				}

				if (!output_file.is_open()) {
					std::cout << "File not open" << std::endl;
					return EXIT_FAILURE;
				}
				output_file << "\t";
				output_file << i.token_value;
				std::cout << tab_num << std::endl;
				for (int j = 0; j <= tab_num; j++) {
					output_file << "\t";
				}
				output_file << "-\t" << enum_names[i.token_type] << std::endl;
			}
			return 0;
		}

	private:
		int cursor_one;
		int cursor_two;
		int state;
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
		enum States {S_first, S_number, S_identifier, S_other};

		int tokenizeLine(std::string& line, size_t size) {
			size_t line_len = size - 1;
			char cur_char;
			int distance;
			int success;
			cursor_two = 0;
			cursor_one = 0;
			state = S_first;

			while (cursor_two <= line_len) {
				cur_char = line[cursor_two];
				if (state == S_first) {
					// First check for identifier or number
					if (std::isalpha(cur_char) || cur_char == '_') state = S_identifier;
					else if (std::isdigit(cur_char)) state = S_number;
					else state = S_other;
				}

				if (std::isspace(cur_char) || cursor_two == line_len) {
					distance = cursor_two - cursor_one;
					if (cur_char == '\n') line_number++;
					if (distance > 0 && !std::isspace(line[cursor_one])) {
						success = addToken(line, false, cursor_one, distance, T_temp);
					}
					cursor_one = cursor_two + 1;
				}
				else if (std::isalpha(cur_char)) {
					if (state == S_number && cur_char != 'e') {
						// Bad identifier
						distance = cursor_two - cursor_one;
						success = addToken(line, true, cursor_one, distance, T_invalid);
						cursor_one = cursor_two + 1;
					}
				}
				else if (std::isdigit(cur_char)) {
					;
				}
				else {
					auto search = symbols.find(cur_char);
					if (search != symbols.end()) {
						distance = cursor_two - cursor_one;
						if (state == S_number && cur_char == '.') {
							;
						}
						else if (cur_char == '_') {
							;
						}
						else {
							success = addToken(line, true, cursor_one, distance, search->second);
							cursor_one = cursor_two + 1;
						}
					}
					else {
						// Invalid symbol found
						distance = cursor_two - cursor_one;
						success = addToken(line, true, cursor_one, distance, T_invalid);
						cursor_one = cursor_two + 1;
					}
				}
				cursor_two++;
			}
			return 0;
		}

		int addToken(std::string& line, bool last_is_symbol, int start, int distance, TokenType symbol_type) {
			std::string token_value = line.substr(start, distance);
			char last_char = line[start + distance];
			if (token_value.compare("")) {
				TokenType t_val_type = findTokenType(token_value);
				if (t_val_type == T_invalid) {
					error_file << "Bad token \t" << token_value << "\t\tat line " << line_number << std::endl;
					return -1;
				}
				Token current_token(t_val_type, token_value);
				v_tokens.push_back(current_token);
				token_count++;
			}
			if (last_is_symbol == true) {
				std::string s(1, last_char);
				Token current_token(symbol_type, s);
				v_tokens.push_back(current_token);
				token_count++;
			}
			state = S_first;
			return 0;
		}

		TokenType findTokenType(std::string& str) {
			return T_temp;
		}

};