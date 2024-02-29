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
		// Pushes the elemnts of a rule on the stack
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
	int r01[1] = { G_PROGRAM,		G_FDECLS, G_DECLARATIONS, G_STATEMENT_SEQ, T_dot };
	int r02[1] = { G_FDECLS,		G_FDEC, T_semicolon, G_FDECLS_P };
	int r03[1] = { G_FDECLS,		T_null };
	int r04[1] = { G_FDECLS_P,		G_FDECLS };
	int r05[1] = { G_FDECLS_P,		T_null };
	int r06[1]= { G_FDEC,			T_def, G_TYPE, G_FNAME, T_open_par, G_PARAMS, T_close_par, G_DECLARATIONS, G_STATEMENT_SEQ, T_fed };
	int r07[1] = { G_PARAMS,		G_TYPE, G_VAR, G_PARAMS_P};
	int r08[1] = { G_PARAMS,		T_null };
	int r09[1] = { G_PARAMS_P,		T_comma, G_PARAMS };
	int r10[1] = { G_PARAMS_P,		T_null };
	int r11[1] = { G_FNAME,			G_ID };
	int r12[1] = { G_DECLARATIONS,		G_DECL, T_semicolon, G_DECLARATIONS_P };
	int r13[1] = { G_DECLARATIONS,		T_null };
	int r14[1] = { G_DECLARATIONS_P,	G_DECLARATIONS };
	int r15[1] = { G_DECLARATIONS_P,	T_null };

	int r16[1] = { G_DECL,			G_TYPE, G_VARLIST };
	int r17[1] = { G_TYPE,			T_kw_int };
	int r18[1] = { G_TYPE,			T_kw_double };
	int r19[1] = { G_VARLIST,		G_VAR, G_VARLIST_P };
	int r20[1] = { G_VARLIST_P,		T_comma, G_VARLIST };
	int r21[1] = { G_VARLIST_P,		T_null };
	int r22[1] = { G_STATEMENT_SEQ,		G_STATEMENT, G_STATEMENT_SEQ_P };
	int r23[1] = { G_STATEMENT_SEQ_P,	T_semicolon, G_STATEMENT_SEQ };
	int r24[1] = { G_STATEMENT_SEQ_P,	T_null };

	int r25[1] = { G_STATEMENT,		G_VAR, T_eq, G_EXPR };
	int r26[1] = { G_STATEMENT,		T_if, G_BEXPR, T_then, G_STATEMENT_SEQ, G_STREPLC_P, T_fi};
	int r27[1] = { G_STATEMENT,		T_while, G_BEXPR, T_do, G_STATEMENT_SEQ, T_od };
	int r28[1] = { G_STATEMENT,		T_print, G_EXPR };
	int r29[1] = { G_STATEMENT,		T_return, G_EXPR };
	int r30[1] = { G_STATEMENT,		T_null };
	int r31[1] = { G_STREPLC_P,		T_else, G_STATEMENT_SEQ };
	int r32[1] = { G_STREPLC_P,		T_null};

	int r33[1] = { G_EXPR,			G_TERM, G_EXPR_P };
	int r34[1] = { G_EXPR_P,		T_plus, G_TERM, G_EXPR_P };
	int r35[1] = { G_EXPR_P,		T_minus, G_TERM, G_EXPR_P };
	int r36[1] = { G_EXPR_P,		T_null };

	int r37[1] = { G_TERM,			G_FACTOR, G_TERM_P };
	int r38[1] = { G_TERM_P,		T_star, G_FACTOR, G_TERM_P };
	int r39[1] = { G_TERM_P,		T_slash, G_FACTOR, G_TERM_P };
	int r40[1] = { G_TERM_P,		T_mod, G_FACTOR, G_TERM_P };
	int r41[1] = { G_TERM_P,		T_null };

	int r42[1] = { G_FACTOR,		G_VAR };
	int r43[1] = { G_FACTOR,		G_NUMBER };
	int r44[1] = { G_FACTOR,		T_open_par, G_EXPR, T_close_par };
	int r45[1] = { G_FACTOR,		G_FNAME, T_open_par, G_EXPRSEQ, T_close_par };

	int r46[1] = { G_EXPRSEQ,		G_EXPR, G_EXPRSEQ_P };
	int r47[1] = { G_EXPRSEQ,		T_null };
	int r48[1] = { G_EXPRSEQ_P,		T_comma, G_EXPRSEQ };
	int r49[1] = { G_EXPRSEQ_P,		T_null };

	int r50[1] = { G_BEXPR,			G_BTERM, G_BEXPR_P };
	int r51[1] = { G_BEXPR_P,		T_or, G_BTERM, G_BEXPR_P };
	int r52[1] = { G_BEXPR_P,		T_null };

	int r53[1] = { G_BTERM,			G_BFACTOR, G_P_BTERM };
	int r54[1] = { G_BTERM_P,		T_and, G_BFACTOR, G_BTERM_P };
	int r55[1] = { G_BTERM_P,		T_null };

	int r56[1] = { G_BFACTOR,		T_open_par, G_BFACTOR_P };
	int r57[1] = { G_BFACTOR,		T_not, G_BFACTOR };
	int r58[1] = { G_BFACTOR_P,		G_BEXPR, T_close_par };
	int r59[1] = { G_BFACTOR_P,		G_EXPR, G_COMP, G_EXPR, T_close_par };
	int r60[1] = { G_COMP,			T_gt, G_COMP_P_P };
	int r61[1] = { G_COMP,			T_lt, G_COMP_P };
	int r62[1] = { G_COMP,			T_eq, T_eq };
	int r63[1] = { G_COMP_P,		T_null };
	int r64[1] = { G_COMP_P,		T_eq };
	int r65[1] = { G_COMP_P,		T_gt };
	int r66[1] = { G_COMP_P_P,		T_null };
	int r67[1] = { G_COMP_P_P,		T_eq };
	
	int r68[1] = { G_VAR,			G_ID, G_VAR_P};
	int r69[1] = { G_VAR_P,			T_null};
	int r70[1] = { G_VAR_P,			T_open_brac, G_EXPR, T_close_brac};

	int r71[1] = { G_ID,			T_identifier };
	int r72[1] = { G_DOUBLE,		G_DECIMAL G_DOUBLE_P };
	int r73[1] = { G_DOUBLE,		G_NUMBER, T_exp, G_NUMBER };
	int r74[1] = { G_DOUBLE_P,		T_exp, G_NUMBER };
	int r75[1] = { G_DOUBLE_P,		T_null };
	int r76[1] = { G_DECIMAL,		G_NUMBER, T_dot, G_POSNUMBER };
	int r77[1] = { G_NUMBER,		T_number };
	int r78[1] = { G_NUMBER,		T_minus, T_number };
	int r79[1] = { G_POSNUMBER,		T_number };


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
