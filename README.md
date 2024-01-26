# Compiler and stuff

Documentation can be found in:
`DOCUMENTATION/html/index.html`

### Files
- main.cpp
- definitions.h
- Lexer.cpp

Project structure:
------------

    ├── README.md           <- The readme
    ├── old                 <- old files that aren't included in the build
    ├── tests               <- various tests to run
    │
    ├── src                <- Source code.
        ├── main.cpp        <- The main program to run the entire compiler
        ├── definitions.h   <- Struct, enum, define, include declarations 
        ├── Lexer.cpp       <- Lexical analysis class, stores tokens
        │
        └── 
------------

Grammar:
```
PROGRAM ->          FDECLS DECLARATIONS STATEMENT_SEQ.
FDECLS ->           FDEC; | FDECLS FDEC; |
FDEC ->             def TYPE FNAME ( PARAMS ) DECLARATIONS STATEMENT_SEQ fed
PARAMS ->           TYPE VAR | TYPE VAR , PARAMS |
FNAME ->            ID
DECLARATIONS ->     DECL; | DECLARATIONS DECL; |
DECL ->             TYPE VARLIST
TYPE ->             int | double
VARLIST ->          VAR, VARLIST | VAR
STATEMENT_SEQ ->    STATEMENT | STATEMENT; STATEMENT_SEQ
STATEMENT ->        VAR = EXPR |
                        if BEXPR then STATEMENT_SEQ fi |
                        if BEXPR then STATEMENT_SEQ else STATEMENT_SEQ fi |
                        while BEXPR do STATEMENT_SEQ od |
                        print EXPR |
                        return EXPR |
EXPR ->				EXPR + TERM | EXPR - TERM | TERM
TERM ->     		TERM * FACTOR | TERM / FACTOR | TERM % FACTOR | FACTOR
FACTOR ->     		VAR | NUMBER | (EXPR) | FNAME(EXPRSEQ)
EXPRSEQ -> 	  		EXPR, EXPRSEQ | EXPR |
BEXPR ->    		BEXPR or BTERM | BTERM
BTERM ->   		 	BTERM and BFACTOR | BFACTOR
BFACTOR ->  	    (BEXPR) | not BFACTOR | (EXPR COMP EXPR)
COMP ->     		< | > | == | <= | >= | <>
VAR ->        	 	ID | ID[EXPR]
LETTER ->     		a | b | c | ... | Z
DIGIT ->     		1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0
ID ->         		<LETTER> | <ID><LETTER> | <ID><DIGIT>
NUMBER ->     		INTEGER | DOUBLE```