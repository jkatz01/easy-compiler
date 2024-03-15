```
PROGRAM -> FDECLS DECLARATIONS STATEMENSEQ .
FDECLS -> FDEC ; FDECLS
	| -> ϵ
FDEC -> def TYPE FNAME ( PARAMS ) DECLARATIONS STATEMENSEQ fed
PARAMS -> TYPE VAR PARAM_OPT 
	| -> ϵ
PARAM_OPT -> , PARAMS
	| -> ϵ
FNAME -> ID
DECLARATIONS -> DECL ; DECLARATIONS
	| -> ϵ
DECL -> TYPE VARLIST
TYPE -> kw_int
	| -> kw_double
VARLIST -> VAR VARLISP
VARLIST_P -> , VARLIST
	| ->  ϵ
STATEMENSEQ -> STATEMENT ; STATEMENSEQ
	| -> ϵ
STATEMENT -> VAR = EXPR
	| -> if ( EXPR ) then STATEMENSEQ STREPLC_P fi
	| -> while ( EXPR ) do STATEMENSEQ od
	| -> print ( EXPR )
	| -> return ( EXPR )
	| -> ϵ
STREPLC_P -> else STATEMENSEQ
	| -> ϵ
EXPR -> TERM EXPR_P
	| -> not ( EXPR )
EXPR_P -> + TERM EXPR_P
	| -> - TERM EXPR_P
	| -> or TERM EXPR_P  
	| -> COMP TERM EXPR_P
	| ->  ϵ
TERM -> FACTOR TERM_P
TERM_P -> * FACTOR TERM_P
	| -> / FACTOR TERM_P
	| -> % FACTOR TERM_P
	| -> and FACTOR TERM_P
	| -> ϵ
FACTOR -> ID FUNCOPTS         
	| -> NUMBER
	| -> ( EXPR )
FUNCOPTS -> ( EXPRSEQ ) 
	| -> ϵ
EXPRSEQ -> EXPR EXPRSEQ_P
	| -> ϵ
EXPRSEQ_P -> , EXPRSEQ
	| -> ϵ
COMP -> > COMP_P_P
	| -> < COMP_P
	| -> = =
COMP_P -> ϵ
	| -> =
	| -> >
COMP_P_P -> ϵ
	| -> =
VAR -> ID VAR_P
VAR_P -> ϵ
	| -> [ EXPR ]
ID -> id
NUMBER -> INT DECIMAL
DECIMAL-> . INT EXOPT
	|-> ϵ
EXOPT-> exp NUMBER
	|-> ϵ
INT -> num
	| ->  - num
```

| Nonterminal   | FIRST                                                                             | FOLLOW                                                                                              |
| ------------- | --------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------- |
| PROGRAM       | ϵ    .    def    if    while    print    return    ;    kw_int    kw_double    id | $                                                                                                   |
| FDECLS        | ϵ    def                                                                          | $    kw_int    kw_double    if    while    print    return    ;    id    .                          |
| FDEC          | def                                                                               | ;                                                                                                   |
| PARAMS        | ϵ    kw_int    kw_double                                                          | )                                                                                                   |
| PARAM_OPT     | ,    ϵ                                                                            | )                                                                                                   |
| FNAME         | id                                                                                | (                                                                                                   |
| DECLARATIONS  | ϵ    kw_int    kw_double                                                          | $    if    while    print    return    ;    id    .    fed                                          |
| DECL          | kw_int    kw_double                                                               | ;                                                                                                   |
| TYPE          | kw_int    kw_double                                                               | id                                                                                                  |
| VARLIST       | id                                                                                | ;                                                                                                   |
| VARLIST_P     | ,    ϵ                                                                            | ;                                                                                                   |
| STATEMENT_SEQ | ϵ    if    while    print    return    ;    id                                    | .    fed    else    ;    fi    od                                                                   |
| STATEMENT     | if    while    print    return    ϵ    id                                         | ;                                                                                                   |
| STREPLC_P     | else    ϵ                                                                         | fi                                                                                                  |
| EXPR          | not    (    id    num    \-                                                       | ;    then    do    )    ,    ]                                                                      |
| EXPR_P        | +    \-    or    ϵ    \>    <    \=                                               | ;    then    do    )    ,    ]                                                                      |
| TERM          | (    id    num    \-                                                              | +    \-    or    ;    then    do    \>    <    \=    )    ,    ]                                    |
| TERM_P        | \*    /    %    and    ϵ                                                          | +    \-    or    ;    then    do    \>    <    \=    )    ,    ]                                    |
| FACTOR        | (    id    num    \-                                                              | \*    /    %    and    +    \-    or    ;    then    do    \>    <    \=    )    ,    ]             |
| FUNCOPTS      | (    ϵ                                                                            | \*    /    %    and    +    \-    or    ;    then    do    \>    <    \=    )    ,    ]             |
| EXPRSEQ       | not    ϵ    (    id    num    \-                                                  | )                                                                                                   |
| EXPRSEQ_P     | ,    ϵ                                                                            | )                                                                                                   |
| COMP          | \>    <    \=                                                                     | (    id    num    \-                                                                                |
| COMP_P        | ϵ    \=    \>                                                                     | (    id    num    \-                                                                                |
| COMP_P_P      | ϵ    \=                                                                           | (    id    num    \-                                                                                |
| VAR           | id                                                                                | ,    )    ;    \=                                                                                   |
| VAR_P         | ϵ    [                                                                            | ,    )    ;    \=                                                                                   |
| ID            | id                                                                                | (    \*    /    %    and    +    \-    or    ;    then    do    \>    <    \=    ,    )    [    ]   |
| NUMBER        | num    \-                                                                         | \*    /    %    and    +    \-    or    ;    then    do    \>    <    \=    )    ,    ]             |
| DECIMAL       | .    ϵ                                                                            | \*    /    %    and    +    \-    or    ;    then    do    \>    <    \=    )    ,    ]             |
| EXOPT         | exp    ϵ                                                                          | \*    /    %    and    +    \-    or    ;    then    do    \>    <    \=    )    ,    ]             |
| INT           | num    \-                                                                         | .    \*    /    %    and    +    \-    or    ;    then    do    \>    <    \=    exp    )    ,    ] |
