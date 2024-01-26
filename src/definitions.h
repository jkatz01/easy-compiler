#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <chrono>
#include <regex>

#define NUM_TOKEN_TYPES 15
#define PAGE_SIZE 4096

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
	T_number,
	T_int,
	T_double,
	T_identifier,
	T_temp,
	T_invalid
};

enum States { 
	S_first,
	S_number,
	S_identifier,
	S_other,
	S_bad
};

struct TokenError {
	std::string value;
	int line;
	TokenError() {
		value = "";
		line = -1;
	}
	TokenError(std::string err_value, int err_line) {
		value = err_value;
		line = err_line;
	}
};

struct Token {
	TokenType token_type;
	std::string token_value;
	Token() {
		token_type = T_temp;
		token_value = "";
	}
	Token(TokenType type, std::string value) {
		token_type = type;
		token_value = value;
	}
};