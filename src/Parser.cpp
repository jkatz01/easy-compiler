#include "definitions.h"
#include <iostream>
#include <string>

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

class LLTable {
public:

	// First const int in rule is the left hand side
	int r01[5] = { G_PROGRAM,		G_FDECLS, G_DECLARATIONS, G_STATEMENT_SEQ, T_dot };
	int r02[4] = { G_FDECLS,		G_FDEC, T_semicolon, G_FDECLS_P };
	int r03[2] = { G_FDECLS,		T_null };
	int r04[2] = { G_FDECLS_P,		G_FDECLS };
	int r05[2] = { G_FDECLS_P,		T_null };
	int r06[10]= { G_FDEC,			T_def, G_TYPE, G_FNAME, T_open_par, G_PARAMS, T_close_par, G_DECLARATIONS, G_STATEMENT_SEQ, T_fed };
	int r07[4] = { G_PARAMS,		G_TYPE, G_VAR, G_PARAMS_P};
	int r08[2] = { G_PARAMS,		T_null };
	int r09[3] = { G_PARAMS_P,		T_comma, G_PARAMS };
	int r10[2] = { G_PARAMS_P,		T_null };
	int r11[2] = { G_FNAME,			G_ID };
	int r12[4] = { G_DECLARATIONS,		G_DECL, T_semicolon, G_DECLARATIONS_P };
	int r13[2] = { G_DECLARATIONS,		T_null };
	int r14[2] = { G_DECLARATIONS_P,	G_DECLARATIONS };
	int r15[2] = { G_DECLARATIONS_P,	T_null };

	int r16[3] = { G_DECL,			G_TYPE, G_VARLIST };
	int r17[2] = { G_TYPE,			T_kw_int };
	int r18[2] = { G_TYPE,			T_kw_double };
	int r19[3] = { G_VARLIST,		G_VAR, G_VARLIST_P };
	int r20[3] = { G_VARLIST_P,		T_comma, G_VARLIST };
	int r21[2] = { G_VARLIST_P,		T_null };
	int r22[3] = { G_STATEMENT_SEQ,		G_STATEMENT, G_STATEMENT_SEQ_P };
	int r23[3] = { G_STATEMENT_SEQ_P,	T_semicolon, G_STATEMENT_SEQ };
	int r24[2] = { G_STATEMENT_SEQ_P,	T_null };

	int r25[4] = { G_STATEMENT,		G_VAR, T_eq, G_EXPR };
	int r26[7] = { G_STATEMENT,		T_if, G_BEXPR, T_then, G_STATEMENT_SEQ, G_STREPLC_P, T_fi};
	int r27[6] = { G_STATEMENT,		T_while, G_BEXPR, T_do, G_STATEMENT_SEQ, T_od };
	int r28[3] = { G_STATEMENT,		T_print, G_EXPR };
	int r29[3] = { G_STATEMENT,		T_return, G_EXPR };
	int r30[2] = { G_STATEMENT,		T_null };
	int r31[3] = { G_STREPLC_P,		T_else, G_STATEMENT_SEQ };
	int r32[2] = { G_STREPLC_P,		T_null};

	int r33[3] = { G_EXPR,			G_TERM, G_EXPR_P };
	int r34[4] = { G_EXPR_P,		T_plus, G_TERM, G_EXPR_P };
	int r35[4] = { G_EXPR_P,		T_minus, G_TERM, G_EXPR_P };
	int r36[2] = { G_EXPR_P,		T_null };

	int r37[3] = { G_TERM,			G_FACTOR, G_TERM_P };
	int r38[4] = { G_TERM_P,		T_star, G_FACTOR, G_TERM_P };
	int r39[4] = { G_TERM_P,		T_slash, G_FACTOR, G_TERM_P };
	int r40[4] = { G_TERM_P,		T_mod, G_FACTOR, G_TERM_P };
	int r41[2] = { G_TERM_P,		T_null };

	int r42[2] = { G_FACTOR,		G_VAR };
	int r43[2] = { G_FACTOR,		G_NUMBER };
	int r44[4] = { G_FACTOR,		T_open_par, G_EXPR, T_close_par };
	int r45[5] = { G_FACTOR,		G_FNAME, T_open_par, G_EXPRSEQ, T_close_par };

	int r46[3] = { G_EXPRSEQ,		G_EXPR, G_EXPRSEQ_P };
	int r47[2] = { G_EXPRSEQ,		T_null };
	int r48[3] = { G_EXPRSEQ_P,		T_comma, G_EXPRSEQ };
	int r49[2] = { G_EXPRSEQ_P,		T_null };

	int r50[3] = { G_BEXPR,			G_BTERM, G_BEXPR_P };
	int r51[4] = { G_BEXPR_P,		T_or, G_BTERM, G_BEXPR_P };
	int r52[2] = { G_BEXPR_P,		T_null };

	int r53[3] = { G_BTERM,			G_BFACTOR, G_BTERM_P };
	int r54[4] = { G_BTERM_P,		T_and, G_BFACTOR, G_BTERM_P };
	int r55[2] = { G_BTERM_P,		T_null };

	int r56[3] = { G_BFACTOR,		T_open_par, G_BFACTOR_P };
	int r57[3] = { G_BFACTOR,		T_not, G_BFACTOR };
	int r58[3] = { G_BFACTOR_P,		G_BEXPR, T_close_par };
	int r59[5] = { G_BFACTOR_P,		G_EXPR, G_COMP, G_EXPR, T_close_par };
	int r60[3] = { G_COMP,			T_gt, G_COMP_P_P };
	int r61[3] = { G_COMP,			T_lt, G_COMP_P };
	int r62[3] = { G_COMP,			T_eq, T_eq };
	int r63[2] = { G_COMP_P,		T_null };
	int r64[2] = { G_COMP_P,		T_eq };
	int r65[2] = { G_COMP_P,		T_gt };
	int r66[2] = { G_COMP_P_P,		T_null };
	int r67[2] = { G_COMP_P_P,		T_eq };
	
	int r68[3] = { G_VAR,			G_ID, G_VAR_P};
	int r69[2] = { G_VAR_P,			T_null};
	int r70[4] = { G_VAR_P,			T_open_brac, G_EXPR, T_close_brac};

	int r71[2] = { G_ID,			T_identifier };
	int r72[3] = { G_DOUBLE,		G_DECIMAL, G_DOUBLE_P };
	int r73[4] = { G_DOUBLE,		G_NUMBER, T_exp, G_NUMBER };
	int r74[3] = { G_DOUBLE_P,		T_exp, G_NUMBER };
	int r75[2] = { G_DOUBLE_P,		T_null };
	int r76[4] = { G_DECIMAL,		G_NUMBER, T_dot, G_POSNUMBER };
	int r77[2] = { G_NUMBER,		T_number };
	int r78[3] = { G_NUMBER,		T_minus, T_number };
	int r79[2] = { G_POSNUMBER,		T_number };
	int r80[2] = { G_ANYNUM,		G_DOUBLE };
	int r81[2] = { G_ANYNUM,		G_NUMBER };
	int rxx[0];


	const int* table[NUM_NONTERIMNALS][NUM_TERMINALS] =
	{
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx},
		{rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx, rxx}
	};

	const int table_sizes[NUM_NONTERIMNALS][NUM_TERMINALS] =
	{
		//{ARR_SIZE(r3), ARR_SIZE(r5)},
	};

	const Rule getRule(int i, int j) {
		const struct Rule rule = { table_sizes[i][j], table[i][j] };
		return rule;
	}
};


class Parser {
public:
	std::vector<Token> const* tokens;
	std::vector<Token> t_stack;
	LLTable table;
	Parser(std::vector<Token> const& token_list) {
		tokens = &token_list;
	}

	int parse() {
		// std::cout << "implement this\n";
		Token test(T_temp, "testvalue");
		// While ....
		if (test.token_type == t_stack[t_stack.capacity()].token_type )  {
			// Matched symbols
			t_stack.pop_back();
		}
		else {
			Rule cur = table.getRule( t_stack[t_stack.capacity()].token_type, test.token_type); 
			t_stack.pop_back();
			addRule(cur);
		}
		
		return 0;
	}

	int addRule(Rule rule) {
		// Pushes the elemnts of a rule on the stack
		// if rule_size is 0 do nothing
		// i stops at 1 because 0 is the first rule 0 -> 1 2 3 ...
		// push in reverse order
		if (rule.size <= 1) {
			return 0;
		}
		for (int i = rule.size - 1; i > 1; i--) {
			Token nonlit(rule.data[i], "");
			t_stack.push_back(nonlit);	
		}
		return 0;
	}

};
