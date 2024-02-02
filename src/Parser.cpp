#include "definitions.h"

#include <iostream>

#define NUM_NONLITERALS 4
#define NUM_LITERALS 4

class LLTable {
public:
	int rule_1[3] = { G_PROGRAM, G_FDECLS, G_DECLARATIONS };
	int* table[NUM_NONLITERALS];
};