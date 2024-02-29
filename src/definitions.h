#pragma once

#include <vector>
#include <string>

#define ARR_SIZE(X) (int)(sizeof(X) / sizeof(X[0]))

#define NUM_TOKEN_TYPES		T_null + 1
#define NUM_TERMINALS		NUM_TOKEN_TYPES
#define NUM_NONTERIMNALS	G_POSNUMBER - T_null
#define PAGE_SIZE		4096
#define TAB_SIZE		8

enum TokenType {
	T_semicolon,
	T_dot,
	T_eq,
	T_lt,
	T_gt,
	T_underscore,
	T_operator,
	T_plus,
	T_minus,
	T_star,
	T_slash,
	T_mod,
	T_open_par,
	T_close_par,
	T_open_brac,
	T_close_brac,
	T_comma,
	T_keyword,
	T_def,
	T_fed,
	T_if,
	T_fi,
	T_else,
	T_then,
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
	T_dollar,
	T_null
};

enum NonTerminal {
	G_PROGRAM = NUM_TOKEN_TYPES, // Start at the end of TokenType so we can use both together
	G_FDECLS,
	G_FDECLS_P,
	G_FDEC,			// Function declaration // def int func(int x, double y) body fed
	G_PARAMS,		// Paramters of function // (int x, double y) 
	G_PARAMS_P,
	G_FNAME,		// Defined name // x 
	G_DECLARATIONS,
	G_DECLARATIONS_P,
	G_DECL,			// Variable declaration // int x, y;
	G_TYPE,			// int // double
	G_VARLIST,
	G_VARLIST_P,
	G_STATEMENT_SEQ,	
	G_STATEMENT_SEQ_P,
	G_STATEMENT,		// x = y // if .. // while ... // print // return // null
	G_STREPLC_P,
	G_EXPR,			// binary operations // a + b // a - b
	G_EXPR_P,
	G_TERM,			// binary operations // a * b // a / b // a % b
	G_TERM_P,
	G_FACTOR,		// thing in operation 
	G_EXPRSEQ,
	G_EXPRSEQ_P,
	G_BEXPR,		// Boolean expression // x and y // x or y // not x
	G_BEXPR_P,
	G_BTERM,
	G_BTERM_P,
	G_BFACTOR,
	G_BFACTOR_P,
	G_COMP,			// Comparison // x 
	G_COMP_P,
	G_COMP_P_P,
	G_VAR,			// Variable  // x
	G_VAR_P,		// Array     // ..[expr]
	G_ID,			// Identifier
	G_ANYNUM,		// double or int
	G_DOUBLE,		// double
	G_DOUBLE_P,
	G_DECIMAL,
	G_NUMBER,		// int
	G_POSNUMBER
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
	int token_type;
	std::string token_value;
	
	Token() {
		token_type = T_temp;
		token_value = "";
	}
	Token(int type, std::string value) {
		token_type = type;
		token_value = value;
	}
};

struct Rule {
	const int size;
	const int* data;
};
