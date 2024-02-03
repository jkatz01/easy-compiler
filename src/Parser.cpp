#include "definitions.h"

#include <iostream>

class LLTable;

struct Rule {
	const int size;
	const int* data;
};

class LLTable {
public:

	// First const int in rule is the left hand side
	const int r1[5] = { G_PROGRAM,			G_FDECLS, G_DECLARATIONS, G_STATEMENT_SEQ, T_dot };

	const int r2[3] = { G_FDECLS,			G_FDEC, T_semicolon };
	const int r3[4] = { G_FDECLS,			G_FDEC, T_semicolon, G_FDECLS };

	const int r4[10] = { G_FDEC,			T_def, G_TYPE, G_FNAME, T_open_par, G_PARAMS, T_close_par, G_DECLARATIONS, G_STATEMENT_SEQ, T_fed };

	const int r5[3] = { G_PARAMS,			G_TYPE, G_VAR };
	const int r6[5] = { G_PARAMS,			G_TYPE, G_VAR, T_comma, G_PARAMS };

	const int r7[2] = { G_FNAME,			G_ID };

	const int r8[3] = { G_DECLARATIONS,		G_DECL, T_semicolon };
	const int r9[4] = { G_DECLARATIONS,		G_DECL, T_semicolon, G_DECLARATIONS };

	const int r10[3] = { G_DECL,			G_TYPE, G_VARLIST };
	const int r11[2] = { G_TYPE,			T_kw_int };
	const int r12[2] = { G_TYPE,			T_kw_double };
	const int r13[4] = { G_VARLIST,			G_VAR, T_comma, G_VARLIST };
	const int r14[2] = { G_VARLIST,			G_VAR };
	const int r15[2] = { G_STATEMENT_SEQ,	G_STATEMENT };
	const int r16[4] = { G_STATEMENT_SEQ,	G_STATEMENT, T_semicolon, G_STATEMENT_SEQ };

	const int r17[4] = { G_STATEMENT,		G_VAR, T_eq, G_EXPR };
	const int r18[6] = { G_STATEMENT,		T_if, G_BEXPR, T_then, G_STATEMENT_SEQ, T_fi};
	const int r19[8] = { G_STATEMENT,		T_if, G_BEXPR, T_then, G_STATEMENT_SEQ, T_else, G_STATEMENT_SEQ, T_fi };
	const int r20[6] = { G_STATEMENT,		T_while, G_BEXPR, T_do, G_STATEMENT_SEQ, T_od };
	const int r21[3] = { G_STATEMENT,		T_print, G_EXPR };
	const int r22[3] = { G_STATEMENT,		T_return, G_EXPR };

	const int r23[3] = { G_EXPR,			G_TERM, G_P_EXPR };
	const int r24[4] = { G_P_EXPR,			T_plus, G_TERM, G_P_EXPR };
	const int r25[4] = { G_P_EXPR,			T_minus, G_TERM, G_P_EXPR };
	const int r27[2] = { G_P_EXPR,			T_null };

	const int r28[3] = { G_TERM,			G_FACTOR, G_P_TERM };
	const int r29[4] = { G_P_TERM,			T_star, G_FACTOR, G_P_TERM };
	const int r30[4] = { G_P_TERM,			T_slash, G_FACTOR, G_P_TERM };
	const int r31[4] = { G_P_TERM,			T_mod, G_FACTOR, G_P_TERM };
	const int r32[2] = { G_P_TERM,			T_null };


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
