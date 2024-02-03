#include "definitions.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <chrono>

/// <summary>
/// Lexer class provides functions to perform lexical analysis on a file
/// and output tokens and errors
/// </summary>
class Lexer {
public: 
	int line_number = 0;
	int token_count = 0;
	int error_count = 0;
	/// <summary>
	/// Holds all tokens for future use
	/// </summary>
	std::vector<Token> v_tokens;
	std::vector<TokenError> error_log;

	/// <summary>
	/// Default constructor for Lexer class
	/// </summary>
	Lexer() {
		source_file_name = "src_file.txt";
		output_file_name = "out_file.txt";
		error_file_name = "error_file.txt";
	}

	/// <summary>
	/// Constructor for Lexer using filenames
	/// </summary>
	/// <param name="src_file">Input file to analyze</param>
	/// <param name="out_file">Output file for tokens</param>
	/// <param name="error_file">Output file for errors</param>
	Lexer(std::string src_file, std::string out_file, std::string error_file) {
		source_file_name = src_file;
		output_file_name = out_file;
		error_file_name = error_file;
	}

	/// <summary>
	/// Default destructor for Lexer class in case files are left open
	/// </summary>
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

	/// <summary>
	/// Main function of Lexer, this generates tokens and errors from the input file 
	/// for future processes to use
	/// </summary>
	/// <returns>Number of errors occurred</returns>
	int generateTokens() {
		source_file.open(source_file_name);
		if (!source_file.is_open()) {
			std::cout << "Failed to load file" << std::endl;
			exit(EXIT_FAILURE);
		}
		std::streamsize file_size = source_file.tellg();
		source_file.seekg(0, std::ios::beg);
		char buffer[PAGE_SIZE];
		error_log.reserve(PAGE_SIZE);

		// Time measuring
		std::cout << "starting: \n";
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

		// Main loop
		while (!source_file.eof()) {
			source_file.read(buffer, sizeof(buffer));
			bytes_read = source_file.gcount();
			std::string content(buffer, sizeof(char) * bytes_read);
			size_t res_size = (sizeof(char) * bytes_read) - (token_count % PAGE_SIZE);
			v_tokens.reserve(v_tokens.size() + res_size);
			if (error_count >= error_log.capacity() - 1) {
				error_log.reserve(error_log.size() + PAGE_SIZE);
			}

			tokenizeLine(content, bytes_read);
		}

		// Time measuring
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		double time_taken = (double)std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
		time_taken = time_taken / 1000;
		std::cout << "Line count: " << line_number + 1 << std::endl;
		std::cout << "Generated " << token_count << " tokens in: " << time_taken << "[ms]" << std::endl;

		output_file.open(output_file_name, std::ios::out | std::ios::trunc);
		error_file.open(error_file_name, std::ios::out | std::ios::trunc);

		std::cout << "Printing: " << std::endl;
		printTokens();
		printErrors();
		
		source_file.close();
		output_file.close();
		error_file.close();

		if (error_log.size() > 0) {
			return (int)error_log.size();
		}

		return EXIT_SUCCESS;
	}

	/// <summary>
	/// Prints all tokens from v_tokens into file
	/// </summary>
	/// <returns></returns>
	int printTokens() {
		for (Token i : v_tokens) {
			int tab_num;
			if ((tab_num = 3 - ((int)i.token_value.length() / 4)) < 0) {
				tab_num = 0;
			}

			if (!output_file.is_open()) {
				std::cout << "File not open" << std::endl;
				return EXIT_FAILURE;
			}

			output_file << i.token_value;
			for (int j = 0; j <= tab_num; j++) {
				output_file << "\t";
			}
			output_file << "-\t" << enum_names[i.token_type] << std::endl;
		}
		return 0;
	}

	/// <summary>
	/// Prints all errors from error_log into file
	/// </summary>
	/// <returns></returns>
	int printErrors() {
		for (TokenError i : error_log) {
			if (i.err_type == E_bad_token) {
				error_file << "Bad token \t" << i.value.data();
				int tab_num;
				if ((tab_num = 3 - ((int)i.value.length() / 4)) < 0) {
					tab_num = 0;
				}
				if (!error_file.is_open()) {
					std::cout << "File not open" << std::endl;
					return EXIT_FAILURE;
				}
				for (int j = 0; j <= tab_num; j++) {
					error_file << "\t";
				}
				error_file << "at line " << i.line << std::endl;
			}
			else if (i.err_type == E_bad_symbol) {
				error_file << "Bad symbol \t" << i.value.data() << "\tat line " << i.line << std::endl;
			}
		}
		return 0;
	}

private:
	int cursor_one = 0;
	int cursor_two = 0;
	int state = 0;
	size_t bytes_read = 0;
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
		{'+', T_plus},
		{'-', T_minus},
		{'*', T_star},
		{'/', T_slash},
		{'%', T_mod},
		{'(', T_open_par},
		{')', T_close_par},
		{',', T_comma}
	};
	const std::unordered_map<std::string, TokenType> keywords = {
		{"def", T_def},
		{"fed", T_fed},
		{"if", T_if},
		{"fi", T_fi},
		{"else", T_else},
		{"while", T_while},
		{"do", T_do},
		{"od", T_od},
		{"print", T_print},
		{"return", T_return},
		{"or", T_or},
		{"and", T_and},
		{"not", T_not},
		{"int", T_kw_int},
		{"double", T_kw_double},
	};
	const std::string enum_names[NUM_TOKEN_TYPES] = { 
		"T_semicolon","T_dot","T_comp","T_underscore","T_operator","T_plus",
		"T_minus","T_star","T_slash","T_mod","T_open_par","T_close_par",
		"T_comma","T_keyword","T_def","T_fed","T_if","T_fi","T_else","T_while",
		"T_do","T_od","T_print","T_return","T_or","T_and","T_not","T_kw_int",
		"T_kw_double","T_number","T_int","T_double","T_identifier",
		"T_exp","T_temp", "T_invalid", "T_null" 
	};

	/// <summary>
	/// Main function for tokenizing a block of text into tokens
	/// </summary>
	/// <param name="line">Block of text to analyze</param>
	/// <param name="size">Size of text</param>
	/// <returns></returns>
	int tokenizeLine(std::string& line, size_t size) {
		size_t line_len = size;
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
				else {
					state = S_first;
				}
				cursor_one = cursor_two + 1;
			}
			else if (std::isalpha(cur_char)) {
				if (state == S_number && cur_char == 'e') {
					// Bad identifier
					distance = cursor_two - cursor_one;
					success = addToken(line, true, cursor_one, distance, T_exp);
					cursor_one = cursor_two + 1;
				}
				else if (state == S_number) {
					state = S_bad;
				}
			}
			else if (std::isdigit(cur_char)) {
				;
			}
			else {
				auto search = symbols.find(cur_char);
				if (search != symbols.end()) {
					distance = cursor_two - cursor_one;
					if (cur_char == '_') {
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
					success = addToken(line, false, cursor_one, distance, T_invalid);
					cursor_one = cursor_two + 1;

					std::string s(1, cur_char);
					TokenError terr(s, line_number, E_bad_symbol);
					error_log.insert(error_log.begin() + error_count, terr);
					error_count++;
				}
			}
			cursor_two++;
		}
		return 0;
	}

	/// <summary>
	/// Adds appropriate tokens into v_tokens
	/// </summary>
	/// <param name="line">Input text</param>
	/// <param name="last_is_symbol">If the token was delimited by a symbol, set to true</param>
	/// <param name="start"></param>
	/// <param name="distance"></param>
	/// <param name="symbol_type">Type of symbol for the last character, if last_is_symbol == true</param>
	/// <returns></returns>
	int addToken(std::string& line, bool last_is_symbol, int start, int distance, TokenType symbol_type) {
		std::string token_value = line.substr(start, distance);
		char last_char = line[start + distance];
		if (token_value.compare("")) {
			TokenType t_val_type = findTokenType(token_value);
			if (t_val_type == T_invalid || state == S_bad) {
				TokenError terr(token_value, line_number, E_bad_token);
				error_log.insert(error_log.begin() + error_count, terr);
				error_count++;
				state = S_first;
				return -1;
			}
			Token current_token(t_val_type, token_value);
			v_tokens.insert(v_tokens.begin() + token_count, current_token);
			token_count++;
		}
		if (last_is_symbol == true) {
			std::string s(1, last_char);
			Token current_token(symbol_type, s);
			v_tokens.insert(v_tokens.begin() + token_count, current_token);
			token_count++;
		}
		state = S_first;
		return 0;
	}

	/// <summary>
	/// Finds the TokenType of a token, includes searching for keywords
	/// </summary>
	/// <param name="str"></param>
	/// <returns>Type of token</returns>
	TokenType findTokenType(std::string& str) {
		if (state == S_number) {
			return T_number;
		}
		auto search = keywords.find(str);
		if (search != keywords.end()) {
			return search->second;
		}
		else if (state == S_identifier) {
			return T_identifier;
		}
		else {
			return T_temp;
		}
	}

};
