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
	int r10[4] = { G_DECLARATIONS,		G_DECL, T_semicolon, G_DECLARATIONS };
	int r11[2] = { G_DECLARATIONS,		T_null };
	int r12[3] = { G_DECL,			G_TYPE, G_VARLIST };
	int r13[2] = { G_TYPE,			T_kw_int };
	int r14[2] = { G_TYPE,			T_kw_double };
	int r15[3] = { G_VARLIST,		G_VAR, G_VARLIST_P };
	int r16[3] = { G_VARLIST_P,		T_comma, G_VARLIST };
	int r17[2] = { G_VARLIST_P,		T_null };
	int r18[4] = { G_STATEMENT_SEQ,		G_STATEMENT, T_semicolon, G_STATEMENT_SEQ };
	int r19[2] = { G_STATEMENT_SEQ,		T_null };
	int r20[4] = { G_STATEMENT,		G_VAR, T_eq, G_EXPR };
	int r21[7] = { G_STATEMENT,		T_if, G_EXPR, T_then, G_STATEMENT_SEQ, G_STREPLC_P, T_fi };
	int r22[6] = { G_STATEMENT,		T_while, G_EXPR, T_do, G_STATEMENT_SEQ, T_od };
	int r23[3] = { G_STATEMENT,		T_print, G_EXPR };
	int r24[3] = { G_STATEMENT,		T_return, G_EXPR };
	int r25[2] = { G_STATEMENT,		T_null };
	int r26[3] = { G_STREPLC_P,		T_else, G_STATEMENT_SEQ };
	int r27[2] = { G_STREPLC_P,		T_null };
	int r28[3] = { G_EXPR,			G_TERM, G_EXPR_P };
	int r29[4] = { G_EXPR_P,		T_plus, G_TERM, G_EXPR_P };
	int r30[4] = { G_EXPR_P,		T_minus, G_TERM, G_EXPR_P};
	int r31[4] = { G_EXPR_P,		T_or, G_TERM, G_EXPR_P};
	int r32[2] = { G_EXPR_P,		T_null };
	int r33[3] = { G_TERM,			G_FACTOR, G_TERM_P };
	int r34[4] = { G_TERM_P,		T_star, G_FACTOR, G_TERM_P };
	int r35[4] = { G_TERM_P,		T_slash, G_FACTOR, G_TERM_P };
	int r36[4] = { G_TERM_P,		T_mod, G_FACTOR, G_TERM_P };
	int r37[4] = { G_TERM_P,		T_and, G_FACTOR, G_TERM_P };
	int r38[2] = { G_TERM_P,		T_null };
	int r39[3] = { G_FACTOR,		G_ID, G_FUNCOPTS };
	int r40[2] = { G_FACTOR,		G_NUMBER };
	int r41[4] = { G_FACTOR,		T_open_par, G_EXPR, T_close_par };
	int r42[4] = { G_FUNCOPTS,		T_open_par, G_EXPRSEQ, T_close_par };
	int r43[2] = { G_FUNCOPTS,		T_null };
	int r44[3] = { G_EXPRSEQ,		G_EXPR, G_EXPRSEQ_P };
	int r45[2] = { G_EXPRSEQ,		T_null };
	int r46[3] = { G_EXPRSEQ_P,		T_comma, G_EXPRSEQ };
	int r47[2] = { G_EXPRSEQ_P,		T_null };
	int r48[3] = { G_COMP,			T_gt, G_COMP_P_P };
	int r49[3] = { G_COMP,			T_lt, G_COMP_P };
	int r50[3] = { G_COMP,			T_eq, T_eq };
	int r51[2] = { G_COMP_P,		T_null };
	int r52[2] = { G_COMP_P,		T_eq };
	int r53[2] = { G_COMP_P,		T_gt };
	int r54[2] = { G_COMP_P_P,		T_null };
	int r55[2] = { G_COMP_P_P,		T_eq };
	int r56[3] = { G_VAR,			G_ID, G_VAR_P };
	int r57[2] = { G_VAR_P,			T_null };
	int r58[4] = { G_VAR_P,			T_open_brac, G_EXPR, T_close_brac};
	int r59[2] = { G_ID,			T_identifier };
	int r60[3] = { G_NUMBER,		G_INT, G_DECIMAL };
	int r61[4] = { G_DECIMAL,		T_dot, G_INT, G_EXOPT };
	int r62[2] = { G_DECIMAL,		T_null };
	int r63[3] = { G_EXOPT,			T_exp, G_NUMBER };
	int r64[2] = { G_EXOPT,			T_null };
	int r65[2] = { G_INT,			T_number };
	int r66[3] = { G_INT,			T_minus, T_number };
	int r__[1] = { 0 };


	const int* table[NUM_NONTERIMNALS][34] =
	{
	//	  .    ;   def   (    )    fed   ,   int  dbl  =    if  then  fi  whl   do   od   prt  ret  else  +   -   or    *     /    %   and  >     <   [    ]    id   exp  num  $ 
		{r01, r01, r01, r__, r__, r__, r__, r01, r01, r__, r01, r__, r__, r01, r__, r__, r01, r01, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r01, r__, r__, r01},
		{r03, r03, r02, r__, r__, r__, r__, r03, r03, r__, r03, r__, r__, r03, r__, r__, r03, r03, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r03, r__, r__, r03},
		{r__, r__, r04, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r11},
		{r__, r__, r__, r__, r06, r__, r__, r05, r05, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r08, r__, r07, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r09, r__, r__, r__},
		{r11, r11, r__, r__, r__, r11, r__, r10, r10, r__, r11, r__, r__, r11, r__, r__, r11, r11, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r11, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r12, r12, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r13, r14, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r15, r__, r__, r__},
		{r__, r17, r__, r__, r__, r__, r16, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r19, r19, r__, r__, r__, r19, r__, r__, r__, r__, r18, r__, r19, r18, r__, r19, r18, r18, r18, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r18, r__, r__, r__},
		{r__, r25, r__, r__, r__, r__, r__, r__, r__, r__, r21, r__, r__, r22, r__, r__, r23, r24, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r20, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r27, r__, r__, r__, r__, r__, r26, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r28, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r28, r__, r__, r__, r__, r__, r__, r__, r__, r__, r28, r__, r28, r__},
		{r__, r32, r__, r__, r32, r__, r32, r__, r__, r__, r__, r32, r__, r__, r32, r__, r__, r__, r__, r29, r30, r31, r__, r__, r__, r__, r__, r__, r__, r32, r__, r__, r__, r__},
		{r__, r__, r__, r33, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r33, r__, r__, r__, r__, r__, r__, r__, r__, r__, r33, r__, r33, r__},
		{r__, r38, r__, r__, r38, r__, r38, r__, r__, r__, r__, r38, r__, r__, r38, r__, r__, r__, r__, r38, r38, r38, r34, r35, r36, r37, r__, r__, r__, r38, r__, r__, r__, r__},
		{r__, r__, r__, r41, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r40, r__, r__, r__, r__, r__, r__, r__, r__, r__, r39, r__, r40, r__},
		{r__, r43, r__, r42, r43, r__, r43, r__, r__, r__, r__, r43, r__, r__, r43, r__, r__, r__, r__, r43, r43, r43, r43, r43, r43, r43, r__, r__, r__, r43, r__, r__, r__, r__},
		{r__, r__, r__, r44, r45, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r44, r__, r__, r__, r__, r__, r__, r__, r__, r__, r44, r__, r44, r__},
		{r__, r__, r__, r__, r47, r__, r46, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r50, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r48, r49, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r52, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r53, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r55, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r56, r__, r__, r__},
		{r__, r57, r__, r__, r57, r__, r57, r__, r__, r57, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r58, r__, r__, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r59, r__, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r60, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r60, r__},
		{r61, r62, r__, r__, r62, r__, r62, r__, r__, r__, r__, r62, r__, r__, r62, r__, r__, r__, r__, r62, r62, r62, r62, r62, r62, r62, r__, r__, r__, r62, r__, r__, r__, r__},
		{r__, r64, r__, r__, r64, r__, r64, r__, r__, r__, r__, r64, r__, r__, r64, r__, r__, r__, r__, r64, r64, r64, r64, r64, r64, r64, r__, r__, r__, r64, r__, r63, r__, r__},
		{r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r66, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r__, r56, r__}
	};

	const int table_sizes[NUM_NONTERIMNALS][34] =
	{
		{A_S(r01), A_S(r01), A_S(r01), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r01), A_S(r01), A_S(r__), A_S(r01), A_S(r__), A_S(r__), A_S(r01), A_S(r__), A_S(r__), A_S(r01), A_S(r01), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r01), A_S(r__), A_S(r__), A_S(r01)},
		{A_S(r03), A_S(r03), A_S(r02), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r03), A_S(r03), A_S(r__), A_S(r03), A_S(r__), A_S(r__), A_S(r03), A_S(r__), A_S(r__), A_S(r03), A_S(r03), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r03), A_S(r__), A_S(r__), A_S(r03)},
		{A_S(r__), A_S(r__), A_S(r04), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r11)},
		{A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r06), A_S(r__), A_S(r__), A_S(r05), A_S(r05), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__)},
		{A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r08), A_S(r__), A_S(r07), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__)},
		{A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r09), A_S(r__), A_S(r__), A_S(r__)},
		{A_S(r11), A_S(r11), A_S(r__), A_S(r__), A_S(r__), A_S(r11), A_S(r__), A_S(r10), A_S(r10), A_S(r__), A_S(r11), A_S(r__), A_S(r__), A_S(r11), A_S(r__), A_S(r__), A_S(r11), A_S(r11), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r11), A_S(r__), A_S(r__), A_S(r__)},
		{A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r12), A_S(r12), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__)},
		{A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r13), A_S(r14), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__)},
		{A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r15), A_S(r__), A_S(r__), A_S(r__)},
		{A_S(r__), A_S(r17), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r16), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__)},
		{A_S(r19), A_S(r19), A_S(r__), A_S(r__), A_S(r__), A_S(r19), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r18), A_S(r__), A_S(r19), A_S(r18), A_S(r__), A_S(r19), A_S(r18), A_S(r18), A_S(r18), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r18), A_S(r__), A_S(r__), A_S(r__)},
		{A_S(r__), A_S(r25), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r21), A_S(r__), A_S(r__), A_S(r22), A_S(r__), A_S(r__), A_S(r23), A_S(r24), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r20), A_S(r__), A_S(r__), A_S(r__)},
		{A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r27), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r26), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__)},
		{A_S(r__), A_S(r__), A_S(r__), A_S(r28), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r28), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r28), A_S(r__), A_S(r28), A_S(r__)},
		{A_S(r__), A_S(r32), A_S(r__), A_S(r__), A_S(r32), A_S(r__), A_S(r32), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r32), A_S(r__), A_S(r__), A_S(r32), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r29), A_S(r30), A_S(r31), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r32), A_S(r__), A_S(r__), A_S(r__), A_S(r__)},
		{A_S(r__), A_S(r__), A_S(r__), A_S(r33), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r33), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r33), A_S(r__), A_S(r33), A_S(r__)},
		{A_S(r__), A_S(r38), A_S(r__), A_S(r__), A_S(r38), A_S(r__), A_S(r38), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r38), A_S(r__), A_S(r__), A_S(r38), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r38), A_S(r38), A_S(r38), A_S(r34), A_S(r35), A_S(r36), A_S(r37), A_S(r__), A_S(r__), A_S(r__), A_S(r38), A_S(r__), A_S(r__), A_S(r__), A_S(r__)},
		{A_S(r__), A_S(r__), A_S(r__), A_S(r41), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r40), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r39), A_S(r__), A_S(r40), A_S(r__)},
		{A_S(r__), A_S(r43), A_S(r__), A_S(r42), A_S(r43), A_S(r__), A_S(r43), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r43), A_S(r__), A_S(r__), A_S(r43), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r43), A_S(r43), A_S(r43), A_S(r43), A_S(r43), A_S(r43), A_S(r43), A_S(r__), A_S(r__), A_S(r__), A_S(r43), A_S(r__), A_S(r__), A_S(r__), A_S(r__)},
		{A_S(r__), A_S(r__), A_S(r__), A_S(r44), A_S(r45), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r44), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r44), A_S(r__), A_S(r44), A_S(r__)},
		{A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r47), A_S(r__), A_S(r46), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__)},
		{A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r50), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r48), A_S(r49), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__)},
		{A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r52), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r53), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__)},
		{A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r55), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__)},
		{A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r56), A_S(r__), A_S(r__), A_S(r__)},
		{A_S(r__), A_S(r57), A_S(r__), A_S(r__), A_S(r57), A_S(r__), A_S(r57), A_S(r__), A_S(r__), A_S(r57), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r58), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__)},
		{A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r59), A_S(r__), A_S(r__), A_S(r__)},
		{A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r60), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r60), A_S(r__)},
		{A_S(r61), A_S(r62), A_S(r__), A_S(r__), A_S(r62), A_S(r__), A_S(r62), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r62), A_S(r__), A_S(r__), A_S(r62), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r62), A_S(r62), A_S(r62), A_S(r62), A_S(r62), A_S(r62), A_S(r62), A_S(r__), A_S(r__), A_S(r__), A_S(r62), A_S(r__), A_S(r__), A_S(r__), A_S(r__)},
		{A_S(r__), A_S(r64), A_S(r__), A_S(r__), A_S(r64), A_S(r__), A_S(r64), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r64), A_S(r__), A_S(r__), A_S(r64), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r64), A_S(r64), A_S(r64), A_S(r64), A_S(r64), A_S(r64), A_S(r64), A_S(r__), A_S(r__), A_S(r__), A_S(r64), A_S(r__), A_S(r63), A_S(r__), A_S(r__)},
		{A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r66), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r__), A_S(r56), A_S(r__)}
	};

	const Rule getRule(int i, int j) {
		const struct Rule rule = { table_sizes[i][j], table[i][j] };
		//std::cout << "getRule size: " << table_sizes[i][j] << std::endl;
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
		t_stack.push_back(Token(G_PROGRAM, ""));

		// While we still have tokens left...
		// if current token matches top of stack -> pop 
		// else get the rule  from table[stack.top()][current_literal]
		// then pop the top non literal and replace it with the rule
		
		//for (auto it = tokens->begin(); it != tokens->end(); ++it) {
		int finished = 0;
		auto it = tokens->begin();
		while (it != tokens->end()) {
			int top_type = t_stack.back().token_type;
			//std::cout << "Parsing\n";
			

			if ( top_type < NUM_TERMINALS || top_type == T_dollar )  { //top_type is nonterm or dollar
				if (top_type == it->token_type) {
					// Matches symbols
					t_stack.pop_back();
					//std::cout << "Popped\n";
					it++;
					// Advance
				}
				else {
					// ERROR
					std::cout << "Error: top_type = " << token_names[top_type] << ";   found: " << token_names[it->token_type] << std::endl;
					return -1;
				}

			}
			else {

				Rule cur = table.getRule( top_type - FIRST_NONLITERAL, it->token_type);
				//std::cout << "Add rule\n";
				t_stack.pop_back(); // I think every pop should add the next rule as the children 
						// of that node on the tree? We need to build the tree bottom up
				//std::cout << "Rule size: " << cur.size << std::endl;
				addRule(cur); 
			}
			for (Token i : t_stack) {
				std::cout << token_names[i.token_type] << "  ";
			}
			std::cout << "\t\t\t val: " << token_names[it->token_type] << std::endl;
			
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
		// need to handle null (pop?)
		for (int i = rule.size - 1; i >= 1; i--) {
			//std::cout << "i: " << i << std::endl;
			if (rule.data[i] == T_null) {
				//t_stack.pop_back();
				//std::cout << "null" << std::endl;
				return 2;
			}
			Token nonlit(rule.data[i], "");
			t_stack.push_back(nonlit);	
		}
		//std::cout << std::endl;
		return 0;
	}

	const std::string token_names[NUM_TOKEN_TYPES + NUM_NONTERIMNALS] = {
	"T_dot","T_semicolon","T_def","T_open_par","T_close_par","T_fed","T_comma","T_kw_int",
	"T_kw_double","T_eq","T_if","T_then","T_fi","T_while","T_do","T_od","T_print","T_return","T_else","T_plus",
	"T_minus","T_or","T_star","T_slash","T_mod","T_and","T_gt","T_lt","T_open_brac","T_close_brac","T_identifier","T_exp","T_number",
	"$","T_underscore","T_operator","T_keyword","T_not","T_int","T_double","T_temp","T_invalid","T_null",
	"PROGRAM","FDECLS","FDEC","PARAMS","PARAM_OPT","FNAME","DECLARATIONS","DECL",
	"TYPE","VARLIST","VARLIST_P","STATEMENT_SEQ","STATEMENT","STREPLC_P","EXPR","EXPR_P","TERM","TERM_P","FACTOR",
	"FUNCOPTS","EXPRSEQ","EXPRSEQ_P","COMP","COMP_P","COMP_P_P","VAR","VAR_P","ID","NUMBER","DECIMAL","EXOPT","INT"
	};

};
