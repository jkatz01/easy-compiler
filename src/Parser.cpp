#include "definitions.h"
#include <iostream>

class LLTable;
class TokTree;

class Parser {
public:
	std::vector<Token> const* tokens;
	std::vector<Token> t_stack;

	Parser(std::vector<Token> const& token_list) {
		tokens = &token_list;
	}

	int parse() {
		std::cout << "implement this\n";
		return 0;
	}

	int pushRule(const int* rule) {
		std::cout << "implement this\n";
		return 0;
	}

};

class TokTree {
public:
	int depth;
	struct TokNode {
		std::vector<TokNode*> children;
		Token token;
	};

	void addNode(Token token) {
		std::cout << "implement this\n";
	}

	void printTree() {
		std::cout << "implement this\n";
	}

	~TokTree() {
		//free everythang
	}
};

/// <summary>
/// Class to manage the LL1 parsing table
/// Only instantiate once please
/// </summary>
class LLTable {
public:

	// First const int in rule is the left hand side
	const int r[5] = { G_PROGRAM,			G_FDECLS, G_DECLARATIONS, G_STATEMENT_SEQ, T_dot };
	const int r[3] = { G_FDECLS,			G_FDEC, T_semicolon };
	const int r[4] = { G_FDECLS,			G_FDEC, T_semicolon, G_FDECLS };
	const int r[10]= { G_FDEC,			T_def, G_TYPE, G_FNAME, T_open_par, G_PARAMS, T_close_par, G_DECLARATIONS, G_STATEMENT_SEQ, T_fed };
	const int r[3] = { G_PARAMS,			G_TYPE, G_VAR };
	const int r[5] = { G_PARAMS,			G_TYPE, G_VAR, T_comma, G_PARAMS };
	const int r[2] = { G_FNAME,			G_ID };
	const int r[3] = { G_DECLARATIONS,		G_DECL, T_semicolon };
	const int r[4] = { G_DECLARATIONS,		G_DECL, T_semicolon, G_DECLARATIONS };

	const int r[3] = { G_DECL,			G_TYPE, G_VARLIST };
	const int r[2] = { G_TYPE,			T_kw_int };
	const int r[2] = { G_TYPE,			T_kw_double };
	const int r[4] = { G_VARLIST,			G_VAR, T_comma, G_VARLIST };
	const int r[2] = { G_VARLIST,			G_VAR };
	const int r[2] = { G_STATEMENT_SEQ,		G_STATEMENT };
	const int r[4] = { G_STATEMENT_SEQ,		G_STATEMENT, T_semicolon, G_STATEMENT_SEQ };

	const int r[4] = { G_STATEMENT,			G_VAR, T_eq, G_EXPR };
	const int r[7] = { G_STATEMENT,			T_if, G_BEXPR, T_then, G_STATEMENT_SEQ, G_P_STREPLC, T_fi};
	const int r[3] = { G_P_STREPLC,			T_else, G_STATEMENT_SEQ };
	const int r[3] = { G_P_STREPLC,			T_null};
	const int r[6] = { G_STATEMENT,			T_while, G_BEXPR, T_do, G_STATEMENT_SEQ, T_od };
	const int r[3] = { G_STATEMENT,			T_print, G_EXPR };
	const int r[3] = { G_STATEMENT,			T_return, G_EXPR };

	const int r[3] = { G_EXPR,			G_TERM, G_P_EXPR };
	const int r[4] = { G_P_EXPR,			T_plus, G_TERM, G_P_EXPR };
	const int r[4] = { G_P_EXPR,			T_minus, G_TERM, G_P_EXPR };
	const int r[2] = { G_P_EXPR,			T_null };

	const int r[3] = { G_TERM,			G_FACTOR, G_P_TERM };
	const int r[4] = { G_P_TERM,			T_star, G_FACTOR, G_P_TERM };
	const int r[4] = { G_P_TERM,			T_slash, G_FACTOR, G_P_TERM };
	const int r[4] = { G_P_TERM,			T_mod, G_FACTOR, G_P_TERM };
	const int r[2] = { G_P_TERM,			T_null };

	const int r[2] = { G_FACTOR,			G_VAR };
	const int r[2] = { G_FACTOR,			G_NUMBER };
	const int r[4] = { G_FACTOR,			T_open_par, G_EXPR, T_close_par };
	const int r[5] = { G_FACTOR,			G_FNAME, T_open_par, G_EXPRSEQ, T_close_par };

	const int r[4] = { G_EXPRSEQ,			G_EXPR, T_comma, G_EXPRSEQ };
	const int r[2] = { G_EXPRSEQ,			G_EXPR };

	const int r[3] = { G_BEXPR,			G_BTERM, G_P_BEXPR };
	const int r[4] = { G_P_BEXPR,			T_or, G_BTERM, G_P_BEXPR };
	const int r[2] = { G_P_BEXPR,			T_null };

	const int r[3] = { G_BTERM,			G_BFACTOR, G_P_BTERM };
	const int r[4] = { G_P_BTERM,			T_and, G_BFACTOR, G_P_BTERM };
	const int r[2] = { G_P_BTERM,			T_null };

	const int r[4] = { G_BFACTOR,			T_open_par, G_BEXPR, T_close_par };
	const int r[3] = { G_BFACTOR,			T_not, G_BFACTOR };
	const int r[6] = { G_BFACTOR,			T_open_par, G_EXPR, G_COMP, G_EXPR, T_close_par };
	const int r[2] = { G_COMP,			T_lt };
	const int r[2] = { G_COMP,			T_gt };
	const int r[3] = { G_COMP,			T_eq, T_eq };
	const int r[3] = { G_COMP,			T_lt, T_eq };
	const int r[3] = { G_COMP,			T_gt, T_eq };
	const int r[3] = { G_COMP,			T_lt, T_gt };
	
	// G_VAR can be an array???
	// const r5
	
	const int r[2] = { G_ID,			T_identifier };
	const int r[4] = { G_DOUBLE,			G_NUMBER, T_exp, G_NUMBER };
	const int r[4] = { G_DOUBLE,			G_DECIMAL, T_exp, G_NUMBER };
	const int r[2] = { G_DOUBLE,			G_DECIMAL };
	const int r[4] = { G_DECIMAL,			G_NUMBER, T_dot, G_POSNUMBER };
	const int r[2] = { G_NUMBER,			T_number };
	const int r[3] = { G_NUMBER,			T_minus, T_number };
	const int r[2] = { G_POSNUMBER,			T_number };


	const int* table[NUM_NONTERIMNALS][NUM_TERMINALS] =
	{
		{r1, r2},
		{r3, r5}
	};

	const int table_sizes[NUM_NONTERIMNALS][NUM_TERMINALS] =
	{
		{ARR_SIZE(r1), ARR_SIZE(r2)},
		{ARR_SIZE(r3), ARR_SIZE(r5)}
	};

	const Rule getRule(int i, int j) {
		const struct Rule rule = { table_sizes[i][j], table[i][j] };
		return rule;
	}
};
