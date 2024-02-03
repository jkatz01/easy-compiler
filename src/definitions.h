#pragma once

#include <iostream>

#define NUM_TOKEN_TYPES		T_null + 1
#define NUM_TERMINALS		NUM_TOKEN_TYPES
#define NUM_NONTERIMNALS	G_NUMBER - T_null
#define PAGE_SIZE			4096

enum TokenType {
	T_semicolon,
	T_dot,
	T_comp,
	T_underscore,
	T_operator,
	T_plus,
	T_minus,
	T_star,
	T_slash,
	T_mod,
	T_open_par,
	T_close_par,
	T_comma,
	T_keyword,
	T_def,
	T_fed,
	T_if,
	T_fi,
	T_else,
	T_while,
	T_do,
	T_od,
	T_print,
	T_return,
	T_or,
	T_and,
	T_not,
	T_kw_int,
	T_kw_double,
	T_number,
	T_int,
	T_double,
	T_identifier,
	T_exp,
	T_temp,
	T_invalid,
	T_null
};

enum NonTerminal {
	G_PROGRAM = NUM_TOKEN_TYPES, // Start at the end of TokenType so we can use both together
	G_FDECLS,
	G_FDEC,
	G_PARAMS,
	G_FNAME,
	G_DECLARATIONS,
	G_DECL,
	G_TYPE,
	G_VARLIST,
	G_STATEMENT_SEQ,
	G_STATEMENT,
	G_EXPR,
	G_P_EXPR,
	G_TERM,
	G_P_TERM,
	G_FACTOR,
	G_EXPRSEQ,
	G_BEXPR,
	G_P_BEXPR,
	G_BTERM,
	G_P_BTERM,
	G_BFACTOR,
	G_COMP,
	G_VAR,
	G_ID,
	G_DOUBLE,
	G_DECIMAL,
	G_NUMBER
};

enum States { 
	S_first,
	S_number,
	S_identifier,
	S_other,
	S_bad
};

enum ErrorType {
	E_bad_token,
	E_bad_symbol
};

struct TokenError {
	std::string value;
	int line;
	ErrorType err_type;
	TokenError() {
		value = "";
		line = -1;
		err_type = E_bad_symbol;
	}
	TokenError(std::string err_value, int err_line, ErrorType e_type) {
		value = err_value;
		line = err_line;
		err_type = e_type;
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
