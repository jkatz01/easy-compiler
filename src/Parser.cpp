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
	int r02[4] = { G_FDECLS,		G_FDEC, T_semicolon, G_FDECLS };
	int r03[2] = { G_FDECLS,		T_null };
	int r04[10]= { G_FDEC,			T_def, G_TYPE, G_FNAME, T_open_par, G_PARAMS, T_close_par, G_DECLARATIONS, G_STATEMENT_SEQ, T_fed };
	int r05[4] = { G_PARAMS,		G_TYPE, G_VAR, G_PARAM_OPT };
	int r06[2] = { G_PARAMS,		T_null };
	int r07[3] = { G_PARAM_OPT,		T_comma, G_PARAMS };
	int r08[2] = { G_PARAM_OPT,		T_null };
	int r09[2] = { G_FNAME,			G_ID };
	int r00[4] = { G_DECLARATIONS,		 G_DECL, T_comma, G_DECLARATIONS };
	int r11[2] = { G_DECLARATIONS,		 T_null };
	int r12[3] = { G_DECL,			 G_TYPE, G_VARLIST };
	int r13[2] = { G_TYPE,			 T_kw_int };
	int r14[2] = { G_TYPE,			 T_kw_double };
	int r15[3] = { G_VARLIST,		 G_VAR, G_VARLIST_P };
	int r16[3] = { G_VARLIST_P,		 T_comma, G_VARLIST };
	int r17[2] = { G_VARLIST_P,		T_null };
	int r18[3] = { G_STATEMENT_SEQ,		 T_semicolon, G_STATEMENT_SEQ };
	int r19[2] = { G_STATEMENT_SEQ,		 T_null };
	int r20[4] = { G_STATEMENT,		 G_VAR, T_eq, G_EXPR };
	int r21[7] = { G_STATEMENT,		 T_if, G_EXPR, T_then, G_STATEMENT_SEQ, G_STREPLC_P, T_fi };
	int r22[6] = { G_STATEMENT,		 T_while, G_EXPR, T_do, G_STATEMENT_SEQ, T_od };
	int r23[3] = { G_STATEMENT,		 T_print, G_EXPR };
	int r24[3] = { G_STATEMENT,		T_return, G_EXPR };
	int r25[2] = { G_STATEMENT,		 T_null };
	int r26[3] = { G_STREPLC_P,		 T_else, G_STATEMENT_SEQ };
	int r27[2] = { G_STREPLC_P,		T_null };
	int r28[3] = { G_EXPR,			G_TERM, G_EXPR_P };
	int r29[4] = { G_EXPR_P,		 T_plus, G_TERM, G_EXPR_P };
	int r30[4] = { G_EXPR_P,		 T_minus, G_TERM, G_EXPR_P};
	int r31[4] = { G_EXPR_P,		T_or, G_TERM, G_EXPR_P};
	int r32[2] = { G_EXPR_P,		 T_null };
	int r33[3] = { G_TERM,			G_FACTOR, G_TERM_P };
	int r34[4] = { G_TERM_P,		T_star, G_FACTOR, G_TERM_P };
	int r35[4] = { G_TERM_P,		T_slash, G_FACTOR, G_TERM_P };
	int r36[4] = { G_TERM_P,		T_mod, G_FACTOR, G_TERM_P };
	int r37[4] = { G_TERM_P,		T_and, G_FACTOR, G_TERM_P };
	int r38[2] = { G_TERM_P,		 T_null };
	int r39[3] = { G_FACTOR,		G_ID, G_FUNCOPTS };
	int r40[2] = { G_FACTOR,		 G_NUMBER };
	int r41[4] = { G_FACTOR,		T_open_par, G_EXPR, T_close_par };
	int r42[4] = { G_FUNCOPTS,		 T_open_par, G_EXPRSEQ, T_close_par };
	int r43[2] = { G_FUNCOPTS,		 T_null };
	int r44[3] = { G_EXPRSEQ,		 G_EXPR, G_EXPRSEQ_P };
	int r45[2] = { G_EXPRSEQ,		 T_null };
	int r46[3] = { G_EXPRSEQ_P,		 T_comma, G_EXPRSEQ };
	int r47[2] = { G_EXPRSEQ_P,		T_null };
	int r48[3] = { G_COMP,			 T_gt, G_COMP_P_P };
	int r49[3] = { G_COMP,			 T_lt, G_COMP_P };
	int r50[3] = { G_COMP,			 T_eq, T_eq };
	int r51[2] = { G_COMP_P,		 T_null };
	int r52[2] = { G_COMP_P,		 T_eq };
	int r53[2] = { G_COMP_P,		 T_gt };
	int r54[2] = { G_COMP_P_P,		 T_null };
	int r55[2] = { G_COMP_P_P,		T_eq };
	int r56[3] = { G_VAR,			 G_ID, G_VAR_P };
	int r57[2] = { G_VAR_P,			T_null };
	int r58[2] = { G_ID,			 T_identifier };
	int r59[3] = { G_NUMBER,		 G_INT, G_DECIMAL };
	int r60[4] = { G_DECIMAL,		 T_dot, G_INT, G_EXOPT };
	int r61[2] = { G_DECIMAL,		 T_null };
	int r62[3] = { G_EXOPT,			 T_exp, G_NUMBER };
	int r63[2] = { G_EXOPT,			 T_null };
	int r64[2] = { G_INT,			 T_number };
	int r65[3] = { G_INT,			 T_minus, T_number };
	int r__[1] = { 0 };


	const int* table[NUM_NONTERIMNALS][NUM_TERMINALS] =
	{
	//	  .    ;   def   (    )    fed   ,   int  dbl  =    if  then  fi  whl   do   od   prt  ret  else  +   -   or    *     /    %   and  >     <   >    [    ]    id   exp  num  $ 
		{r01, r01, r01, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r03, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r11, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r19, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r61, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__}
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
		t_stack.push_back(Token(T_dollar, ""));

		// While we still have tokens left...
		// if current token matches top of stack -> pop 
		// else get the rule  from table[stack.top()][current_literal]
		// then pop the top non literal and replace it with the rule
		for (auto it = tokens->begin(); it != tokens->end(); ++it) {
			if (it->token_type == t_stack[t_stack.size()].token_type )  {
				// Matched symbols
				t_stack.pop_back();
			}
			else {
				Rule cur = table.getRule( t_stack[t_stack.size()].token_type, it->token_type); 

				t_stack.pop_back(); // I think every pop should add the next rule as the children 
						// of that node on the tree? We need to build the tree bottom up
				addRule(cur); 
			}
		}
		
		return 0;
	}

	int addRule(Rule rule) {
		// Pushes the elements of a rule on the stack
		// if rule_size is 0 do nothing
		// i stops at 1 because 0 is the first rule 0 -> 1 2 3 ...
		// push in reverse order
		if (rule.size <= 1) {
			return 1;
		}
		// need to handle null (push nothing?)
		for (int i = rule.size - 1; i > 1; i--) {
			if (rule.data[i] == T_null) {
				return 2;
			}
			Token nonlit(rule.data[i], "");
			t_stack.push_back(nonlit);	
		}
		return 0;
	}

};
