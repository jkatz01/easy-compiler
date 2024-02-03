#include "definitions.h"

#include <iostream>

#define NUM_NONTERIMNALS 4
#define NUM_TERMINALS 4

class LLTable {
public:
	// First int in rule is the left hand side
	int rule_1[5] = { G_PROGRAM, G_FDECLS, G_DECLARATIONS, G_STATEMENT_SEQ, T_dot };

	int rule_2[3] = { G_FDECLS, G_FDEC, T_semicolon };
	int rule_3[4] = { G_FDECLS, G_FDEC, T_semicolon, G_FDECLS };

	int rule_4[10] = { G_FDEC, T_def, G_TYPE, G_FNAME, T_open_par, G_PARAMS, T_close_par, G_DECLARATIONS, G_STATEMENT_SEQ, T_fed };

	int rule_5[3] = { G_PARAMS, G_TYPE, G_VAR };
	int rule_6[5] = { G_PARAMS, G_TYPE, G_VAR, T_comma, G_PARAMS };




	int* table[NUM_NONTERIMNALS][NUM_TERMINALS];

	void addTableRules () {
		;
	}
};