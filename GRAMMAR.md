```
		PROGRAM -> FDECLS DECLARATIONS STATEMENSEQ .
		FDECLS -> FDEC ; FDECLS_P
				| ϵ
		  FDEC -> def TYPE FNAME ( PARAMS ) DECLARATIONS STATEMENSEQ fed
		PARAMS -> TYPE VAR PARAMS_P
				| ϵ
		 FNAME -> ID
  DECLARATIONS -> DECL ; DECLARATIONS_P
				| ϵ
		  DECL -> TYPE VARLIST
		  TYPE -> kw_int
				| kw_double
	   VARLIST -> VAR VARLISP
 STATEMENSEQ -> STATEMENT STATEMENSEQ_P
	 STATEMENT -> VAR = EXPR
				| if BEXPR then STATEMENSEQ P_STREPLC fi
				| while BEXPR do STATEMENSEQ od
				| print EXPR
				| return EXPR
				| ϵ
	 P_STREPLC -> else STATEMENSEQ
				| ϵ
		  EXPR -> TERM P_EXPR
		P_EXPR -> + TERM P_EXPR
				| - TERM P_EXPR
				| ϵ
		  TERM -> FACTOR P_TERM
		P_TERM -> * FACTOR P_TERM
				| / FACTOR P_TERM
				| % FACTOR P_TERM
				| ϵ
		FACTOR -> VAR
				| NUMBER
				| ( EXPR )
				| FNAME ( EXPRSEQ )
	   EXPRSEQ -> EXPR EXPRSEQ_P
				| ϵ
		 BEXPR -> BTERM P_BEXPR
	   P_BEXPR -> or BTERM P_BEXPR
				| ϵ
		 BTERM -> BFACTOR P_BTERM
	   P_BTERM -> and BFACTOR P_BTERM
				| ϵ
	   BFACTOR -> ( BFACTOR_P
				| not BFACTOR
		  COMP -> > COMP_P_P
				| < COMP_P
				| = =
		   VAR -> ID VAR_P
			ID -> identifier
		DOUBLE -> DECIMAL DOUBLE_P
				| NUMBER exp NUMBER
	   DECIMAL -> NUMBER . POSNUMBER
		NUMBER -> num
				| - num
	 POSNUMBER -> num
	   FDECLS_P -> ϵ
				| FDECLS
	   PARAMS_P -> ϵ
				| , PARAMS
 DECLARATIONS_P -> ϵ
				| DECLARATIONS
	  VARLISP -> , VARLIST
				| ϵ
STATEMENSEQ_P -> ϵ
				| ; STATEMENSEQ
	  EXPRSEQ_P -> , EXPRSEQ
				| ϵ
	  BFACTOR_P -> BEXPR )
				| EXPR COMP EXPR )
		 COMP_P -> ϵ
				| =
				| >
		COMP_P_P -> ϵ
				| =
		  VAR_P -> ϵ
				| [ EXPR ]
	   DOUBLE_P -> exp NUMBER
				| ϵ
```

| Symbol		 | Nullable | First														| Follow												|
| -------------- | -------- | --------------------------------------------------------- | ----------------------------------------------------- |
| PROGRAM		 | FALSE	| . ; def identifier if kw_double kw_int print return while | $														|
| FDECLS		 | TRUE		| def ϵ														| . ; identifier if kw_double kw_int print return while |
| FDECLS_P		 | TRUE		| def ϵ														| . ; identifier if kw_double kw_int print return while |
| FDEC			 | FALSE	| def														| ;														|
| PARAMS		 | TRUE		| kw_double kw_int ϵ										| )														|
| PARAMS_P		 | TRUE		| , ϵ														| )														|
| FNAME			 | FALSE	| identifier												| (														|
| DECLARATIONS	 | TRUE		| kw_double kw_int ϵ										| . ; fed identifier if print return while				|
| DECLARATIONS_P | TRUE		| kw_double kw_int ϵ										| . ; fed identifier if print return while				|
| DECL			 | FALSE	| kw_double kw_int											| ;														|
| TYPE			 | FALSE	| kw_double kw_int											| identifier											|
| VARLIST		 | FALSE	| identifier												| ;														|
| VARLISP		 | TRUE		| , ϵ														| ;														|
| STATEMENSEQ	 | TRUE		| ; identifier if print return while ϵ						| . else fed fi od										|
| STATEMENSEQ_P	 | TRUE		| ; ϵ														| . else fed fi od										|
| STATEMENT		 | TRUE		| identifier if print return while ϵ						| . ; else fed fi od									|
| P_STREPLC		 | TRUE		| else ϵ													| fi													|
| EXPR			 | FALSE	| ( - identifier num										| ) , . ; < = > ] else fed fi od						|
| P_EXPR		 | TRUE		| + - ϵ														| ) , . ; < = > ] else fed fi od						|
| TERM			 | FALSE	| ( - identifier num										| ) + , - . ; < = > ] else fed fi od					|
| P_TERM		 | TRUE		| % \* / ϵ													| ) + , - . ; < = > ] else fed fi od					|
| FACTOR		 | FALSE	| ( - identifier num										| % ) \* + , - . / ; < = > ] else fed fi od				|
| EXPRSEQ		 | TRUE		| ( - identifier num ϵ										| )														|
| EXPRSEQ_P		 | TRUE		| , ϵ														| )														|
| BEXPR			 | FALSE	| ( not														| ) do then												|
| P_BEXPR		 | TRUE		| or ϵ														| ) do then												|
| BTERM			 | FALSE	| ( not														| ) do or then											|
| P_BTERM		 | TRUE		| and ϵ														| ) do or then											|
| BFACTOR		 | FALSE	| ( not														| ) and do or then										|
| BFACTOR_P		 | FALSE	| ( - identifier not num									| ) and do or then										|
| COMP			 | FALSE	| < = >														| ( - identifier num									|
| COMP_P		 | TRUE		| = > ϵ														| ( - identifier num									|
| COMP_P_P		 | TRUE		| = ϵ														| ( - identifier num									|
| VAR			 | FALSE	| identifier												| \= % ) \* + , - . / ; < = > ] else fed fi od			|
| VAR_P			 | TRUE		| [ ϵ														| \= % ) \* + , - . / ; < = > ] else fed fi od			|
| ID			 | FALSE	| identifier												| \= % ( ) \* + , - . / ; < = > [ ] else fed fi od		|
| DOUBLE		 | FALSE	| - num														|														|
| DOUBLE_P		 | TRUE		| exp ϵ														|														|
| DECIMAL		 | FALSE	| - num														| exp													|
| NUMBER		 | FALSE	| - num														| % ) \* + , - . / ; < = > ] else exp fed fi od			|
| POSNUMBER		 | FALSE	| num														| exp													|