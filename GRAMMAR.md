		PROGRAM -> FDECLS DECLARATIONS STATEMENT_SEQ t_.
		FDECLS -> FDEC t_; FDECLS_P
				| ϵ
		  FDEC -> t_def TYPE FNAME t_( PARAMS t_) DECLARATIONS STATEMENT_SEQ t_fed
		PARAMS -> TYPE VAR PARAMS_P
				| ϵ
		 FNAME -> ID
  DECLARATIONS -> DECL t_; DECLARATIONS_P
				| ϵ
		  DECL -> TYPE VARLIST
		  TYPE -> t_kw_int
				| t_kw_double
	   VARLIST -> VAR VARLIST_P
 STATEMENT_SEQ -> STATEMENT STATEMENT_SEQ_P
	 STATEMENT -> VAR t_= EXPR
				| t_if BEXPR t_then STATEMENT_SEQ P_STREPLC t_fi
				| t_while BEXPR t_do STATEMENT_SEQ t_od
				| t_print EXPR
				| t_return EXPR
				| ϵ
	 P_STREPLC -> t_else STATEMENT_SEQ
				| ϵ
		  EXPR -> TERM P_EXPR
		P_EXPR -> t_+ TERM P_EXPR
				| t_- TERM P_EXPR
				| ϵ
		  TERM -> FACTOR P_TERM
		P_TERM -> t_* FACTOR P_TERM
				| t_/ FACTOR P_TERM
				| t_% FACTOR P_TERM
				| ϵ
		FACTOR -> VAR
				| NUMBER
				| t_( EXPR t_)
				| FNAME t_( EXPRSEQ t_)
	   EXPRSEQ -> EXPR EXPRSEQ_P
				| ϵ
		 BEXPR -> BTERM P_BEXPR
	   P_BEXPR -> t_or BTERM P_BEXPR
				| ϵ
		 BTERM -> BFACTOR P_BTERM
	   P_BTERM -> t_and BFACTOR P_BTERM
				| ϵ
	   BFACTOR -> t_( BFACTOR_P
				| t_not BFACTOR
		  COMP -> t_> COMP_P_P
				| t_< COMP_P
				| t_= t_=
		   VAR -> ID VAR_P
			ID -> t_identifier
		DOUBLE -> DECIMAL DOUBLE_P
				| NUMBER t_exp NUMBER
	   DECIMAL -> NUMBER t_. POSNUMBER
		NUMBER -> t_num
				| t_- t_num
	 POSNUMBER -> t_num
	   FDECLS_P -> ϵ
				| FDECLS
	   PARAMS_P -> ϵ
				| t_, PARAMS
 DECLARATIONS_P -> ϵ
				| DECLARATIONS
	  VARLIST_P -> t_, VARLIST
				| ϵ
STATEMENT_SEQ_P -> ϵ
				| t_; STATEMENT_SEQ
	  EXPRSEQ_P -> t_, EXPRSEQ
				| ϵ
	  BFACTOR_P -> BEXPR t_)
				| EXPR COMP EXPR t_)
		 COMP_P -> ϵ
				| t_=
				| t_>
		COMP_P_P -> ϵ
				| t_=
		  VAR_P -> ϵ
				| t_[ EXPR t_]
	   DOUBLE_P -> t_exp NUMBER
				| ϵ

| Symbol		  | Nullable | First																		 | Follow																				  |
| --------------- | -------- | ----------------------------------------------------------------------------- | -------------------------------------------------------------------------------------- |
| PROGRAM		  | FALSE	 | t_. t_; t_def t_identifier t_if t_kw_double t_kw_int t_print t_return t_while | $																					  |
| FDECLS		  | TRUE	 | t_def ϵ																		 | t_. t_; t_identifier t_if t_kw_double t_kw_int t_print t_return t_while				  |
| FDECLS_P		  | TRUE	 | t_def ϵ																		 | t_. t_; t_identifier t_if t_kw_double t_kw_int t_print t_return t_while				  |
| FDEC			  | FALSE	 | t_def																		 | t_;																					  |
| PARAMS		  | TRUE	 | t_kw_double t_kw_int ϵ														 | t_)																					  |
| PARAMS_P		  | TRUE	 | t_, ϵ																		 | t_)																					  |
| FNAME			  | FALSE	 | t_identifier																	 | t_(																					  |
| DECLARATIONS	  | TRUE	 | t_kw_double t_kw_int ϵ														 | t_. t_; t_fed t_identifier t_if t_print t_return t_while								  |
| DECLARATIONS_P  | TRUE	 | t_kw_double t_kw_int ϵ														 | t_. t_; t_fed t_identifier t_if t_print t_return t_while								  |
| DECL			  | FALSE	 | t_kw_double t_kw_int															 | t_;																					  |
| TYPE			  | FALSE	 | t_kw_double t_kw_int															 | t_identifier																			  |
| VARLIST		  | FALSE	 | t_identifier																	 | t_;																					  |
| VARLIST_P		  | TRUE	 | t_, ϵ																		 | t_;																					  |
| STATEMENT_SEQ	  | TRUE	 | t_; t_identifier t_if t_print t_return t_while ϵ								 | t_. t_else t_fed t_fi t_od															  |
| STATEMENT_SEQ_P | TRUE	 | t_; ϵ																		 | t_. t_else t_fed t_fi t_od															  |
| STATEMENT		  | TRUE	 | t_identifier t_if t_print t_return t_while ϵ									 | t_. t_; t_else t_fed t_fi t_od														  |
| P_STREPLC		  | TRUE	 | t_else ϵ																		 | t_fi																					  |
| EXPR			  | FALSE	 | t_( t_- t_identifier t_num													 | t_) t_, t_. t_; t_< t_= t_> t_] t_else t_fed t_fi t_od								  |
| P_EXPR		  | TRUE	 | t_+ t_- ϵ																	 | t_) t_, t_. t_; t_< t_= t_> t_] t_else t_fed t_fi t_od								  |
| TERM			  | FALSE	 | t_( t_- t_identifier t_num													 | t_) t_+ t_, t_- t_. t_; t_< t_= t_> t_] t_else t_fed t_fi t_od						  |
| P_TERM		  | TRUE	 | t_% t_\* t_/ ϵ																 | t_) t_+ t_, t_- t_. t_; t_< t_= t_> t_] t_else t_fed t_fi t_od						  |
| FACTOR		  | FALSE	 | t_( t_- t_identifier t_num													 | t_% t_) t_\* t_+ t_, t_- t_. t_/ t_; t_< t_= t_> t_] t_else t_fed t_fi t_od			  |
| EXPRSEQ		  | TRUE	 | t_( t_- t_identifier t_num ϵ													 | t_)																					  |
| EXPRSEQ_P		  | TRUE	 | t_, ϵ																		 | t_)																					  |
| BEXPR			  | FALSE	 | t_( t_not																	 | t_) t_do t_then																		  |
| P_BEXPR		  | TRUE	 | t_or ϵ																		 | t_) t_do t_then																		  |
| BTERM			  | FALSE	 | t_( t_not																	 | t_) t_do t_or t_then																	  |
| P_BTERM		  | TRUE	 | t_and ϵ																		 | t_) t_do t_or t_then																	  |
| BFACTOR		  | FALSE	 | t_( t_not																	 | t_) t_and t_do t_or t_then															  |
| BFACTOR_P		  | FALSE	 | t_( t_- t_identifier t_not t_num												 | t_) t_and t_do t_or t_then															  |
| COMP			  | FALSE	 | t_< t_= t_>																	 | t_( t_- t_identifier t_num															  |
| COMP_P		  | TRUE	 | t_= t_> ϵ																	 | t_( t_- t_identifier t_num															  |
| COMP_P_P		  | TRUE	 | t_= ϵ																		 | t_( t_- t_identifier t_num															  |
| VAR			  | FALSE	 | t_identifier																	 | \= t_% t_) t_\* t_+ t_, t_- t_. t_/ t_; t_< t_= t_> t_] t_else t_fed t_fi t_od		  |
| VAR_P			  | TRUE	 | t_[ ϵ																		 | \= t_% t_) t_\* t_+ t_, t_- t_. t_/ t_; t_< t_= t_> t_] t_else t_fed t_fi t_od		  |
| ID			  | FALSE	 | t_identifier																	 | \= t_% t_( t_) t_\* t_+ t_, t_- t_. t_/ t_; t_< t_= t_> t_[ t_] t_else t_fed t_fi t_od |
| DOUBLE		  | FALSE	 | t_- t_num																	 |																						  |
| DOUBLE_P		  | TRUE	 | t_exp ϵ																		 |																						  |
| DECIMAL		  | FALSE	 | t_- t_num																	 | t_exp																				  |
| NUMBER		  | FALSE	 | t_- t_num																	 | t_% t_) t_\* t_+ t_, t_- t_. t_/ t_; t_< t_= t_> t_] t_else t_exp t_fed t_fi t_od	  |
| POSNUMBER		  | FALSE	 | t_num																		 | t_exp																				  |



