#pragma once

#include <vector>
#include <string>

#define ARR_SIZE(X) (int)(sizeof(X) / sizeof(X[0]))
#define A_S(X)	ARR_SIZE(X)

#define NUM_TOKEN_TYPES		T_null + 1
#define NUM_TERMINALS		NUM_TOKEN_TYPES
#define NUM_NONTERIMNALS	G_INT - T_null
#define PAGE_SIZE		4096
#define TAB_SIZE		8
#define FIRST_NONLITERAL	G_PROGRAM

enum TokenType {
	T_dot,
	T_semicolon,
	T_def,
	T_open_par,
	T_close_par,
	T_fed,
	T_comma,
	T_kw_int,
	T_kw_double,
	T_eq,
	T_if,
	T_then,
	T_fi,
	T_while,
	T_do,
	T_od,
	T_print,
	T_return,
	T_else,
	T_plus,
	T_minus,
	T_or,
	T_star,
	T_slash,
	T_mod,
	T_and,
	T_gt,
	T_lt,
	T_open_brac,
	T_close_brac,
	T_identifier,
	T_exp,
	T_number,
	T_dollar,

	T_underscore,
	T_operator,
	T_keyword,
	T_not,
	T_int,
	T_double,
	T_temp,
	T_invalid,
	T_null
};

enum NonTerminal {
	G_PROGRAM = NUM_TOKEN_TYPES, // Start at the end of TokenType so we can use both together
	G_FDECLS,
	G_FDEC,			// Function declaration // def int func(int x, double y) body fed
	G_PARAMS,		// Paramters of function // (int x, double y) 
	G_PARAM_OPT,
	G_FNAME,		// Defined name // x 
	G_DECLARATIONS,
	G_DECL,			// Variable declaration // int x, y;
	G_TYPE,			// int // double
	G_VARLIST,
	G_VARLIST_P,
	G_STATEMENT_SEQ,	
	G_STATEMENT,		// x = y // if .. // while ... // print // return // null
	G_STREPLC_P,
	G_EXPR,			// binary operations // a + b // a - b
	G_EXPR_P,
	G_TERM,			// binary operations // a * b // a / b // a % b
	G_TERM_P,
	G_FACTOR,		// thing in operation 
	G_FUNCOPTS,
	G_EXPRSEQ,
	G_EXPRSEQ_P,
	G_COMP,			// Comparison // x 
	G_COMP_P,
	G_COMP_P_P,
	G_VAR,			// Variable  // x
	G_VAR_P,		// Array     // ..[expr]
	G_ID,			// Identifier
	G_NUMBER,
	G_DECIMAL,		// if this exists a number is type double
	G_EXOPT,		// exponential in double
	G_INT
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
	int size;
	const int* data;
	Rule(int rsize, const int* rdata) {
		size = rsize;
		data = rdata;
	}
};
