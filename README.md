﻿# Compiler and stuff

Documentation can be found in:
`DOCUMENTATION/html/index.html`

## Quick Start
This project uses `flat assembler 1.73.32` for assembly/intermediate code. You can get it here: https://flatassembler.net/
The only major deviation from the original grammar is parsing binary expressions 
and comparisons as normal expressions like addition and subtraction 

Project structure:
------------

    ├── README.md           <- The readme
    ├── tests               <- various tests to run
    │
    ├── src                 <- Source code.
        ├── main.cpp        <- The main program to run the entire compiler
        ├── definitions.h   <- Structs, enums, macros, includes
        ├── Lexer.cpp       <- Lexical analysis class, stores tokens
        ├── Parser.cpp      <- Parsing class, generates syntax tree
        ├── LLTable.cpp     <- Helper class that stores grammar rules and LL1 table
        └── SyntaxTree.cpp  <- Abstract Syntax Tree class to use for compiling
------------

Grammar:
```
PROGRAM ->          FDECLS DECLARATIONS STATEMENT_SEQ.
FDECLS ->           FDEC; | FDECLS FDEC; | ϵ
FDEC ->             def TYPE FNAME ( PARAMS ) DECLARATIONS STATEMENT_SEQ fed
PARAMS ->           TYPE VAR | TYPE VAR , PARAMS | ϵ
FNAME ->            ID
DECLARATIONS ->     DECL; | DECLARATIONS DECL; | ϵ
DECL ->             TYPE VARLIST
TYPE ->             int | double
VARLIST ->          VAR, VARLIST | VAR
STATEMENT_SEQ ->    STATEMENT | STATEMENT; STATEMENT_SEQ
STATEMENT ->        VAR = EXPR |
                        if BEXPR then STATEMENT_SEQ fi |
                        if BEXPR then STATEMENT_SEQ else STATEMENT_SEQ fi |
                        while BEXPR do STATEMENT_SEQ od |
                        print EXPR |
                        return EXPR | ϵ

EXPR ->				EXPR + TERM | EXPR - TERM | TERM
TERM ->     		TERM * FACTOR | TERM / FACTOR | TERM % FACTOR | FACTOR
FACTOR ->     		VAR | NUMBER | (EXPR) | FNAME(EXPRSEQ)
EXPRSEQ -> 	  		EXPR, EXPRSEQ | EXPR | ϵ
BEXPR ->    		BEXPR or BTERM | BTERM
BTERM ->   		 	BTERM and BFACTOR | BFACTOR
BFACTOR ->  	    (BEXPR) | not BFACTOR | (EXPR COMP EXPR)
COMP ->     		< | > | == | <= | >= | <>
VAR ->        	 	ID | ID[EXPR]
LETTER ->     		a | b | c | ... | Z
DIGIT ->     		1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0
ID ->         		<LETTER> | <ID><LETTER> | <ID><DIGIT>
NUMBER ->     		INTEGER | DOUBLE```
