#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <chrono>
#include <regex>

#define NUM_TOKEN_TYPES 14
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