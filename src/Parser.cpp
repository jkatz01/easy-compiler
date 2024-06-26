#include "definitions.h"
#include "LLTable.cpp"
#include "SyntaxTree.cpp"
#include <iostream>
#include <fstream>

class Parser {
public:
	std::vector<Token> const* tokens; // Tokens from tokenizer
	std::vector<Token> parse_stack; // Stack used for parsing
	SyntaxTree *program_tree; // Need to add nodes from a tree in a custom way for rules that need it
	std::vector<TreeNode*> ast_node_stack; // For returning to the node
	LLTable *table;
	int err_count = 0;


	Parser(std::vector<Token> const& token_list, SyntaxTree* tree) {
		tokens = &token_list;
		parse_stack.reserve(32);
		ast_node_stack.reserve(32);
		
		table = new LLTable(); // TODO: problem with allocating this !!
		std::cout << "constructed parser" << std::endl;
		program_tree = tree;
		
	}
	~Parser() {
		// TODO: deleting table causes heap corruption
	}

	int parse() {
		parse_stack.push_back(Token(T_dollar, ""));
		parse_stack.push_back(Token(G_PROGRAM, ""));

		std::ofstream error_file;
		error_file.open("Parsing-Errors.txt", std::ios::out | std::ios::trunc);

		int it = 0;
		while (it < tokens->size()) {
			int top_type = parse_stack.back().token_type;
			int found_type = tokens->at(it).token_type;
			//std::cout << "Parsing\n";
			
			if ( top_type < NUM_TERMINALS || top_type == T_dollar )  { //top_type is nonterm or dollar
				if (top_type == found_type) {
					// Matched symbols
					if (top_type == T_semicolon && ast_node_stack.back()->node_data->getNodeType() == AST_assignment) {
						ast_node_stack.pop_back();
					}
					parse_stack.pop_back();
					it++;
				}
				else {
					// ERROR
					std::cout << "Error: expected: " << token_names[top_type] << "\t found: " << token_names[found_type] << std::endl;
					error_file << "Error: expected: " << token_names[top_type] << "\t found: " << token_names[found_type] << std::endl;
					err_count++;
					// Handle errors by deleting
					parse_stack.pop_back(); 
					it++; 
					//return -1;
				}
			}
			else {
				
				Rule cur = table->getRule( top_type - FIRST_NONLITERAL, found_type);

				parse_stack.pop_back(); 
				addRule(cur, it);
			}
			if (PRINT_CONSOLE) {
				for (Token i : parse_stack) {
					std::cout << token_names_nice[i.token_type] << "  ";
				}
				if (it < tokens->size()) std::cout << "\t\t\t val: " << token_names_nice[found_type] << std::endl;
			}
		}
		std::cout << "Finished parsing successfully" << std::endl;
		return 0;
	}

	int addRule(Rule rule, int it) {
		// Pushes the elements of a rule on the stack
		// if rule_size is 0 do nothing
		// i stops at 1 because 0 is the first rule 0 -> 1 2 3 ...
		// push in reverse order
		if (rule.size <= 1) {
			return 1;
		}

		astAddRule(rule, it);  // build AST

		for (int i = rule.size - 1; i >= 1; i--) {
			if (rule.data[i] == T_null) {
				return 2;
			}
			Token nonlit(rule.data[i], "");
			parse_stack.push_back(nonlit);	
		}
		return 0;
	}


	void astAddRule(Rule rule, int it) {

		static VarType type_buffer = VT_int;
		static bool	   in_stmt_seq;
		static bool	   in_expr_seq;
		static bool	   in_statement;
		static bool	   in_while_statement;
		static bool	   in_if_statement;
		static bool    in_else_statement;
		static bool	   has_else;
		static bool    in_func_call;
		static int     expr_counter;
		static int	   temp_counter;
		static TreeNode* last_if;
		//OpType  op_buffer = OP_plus;

		// TODO: write an operator presadence swapper:
		// Potential way: (might work???)
		// find expr (parent) (high prec) (low prec)
		// high.second = low.first
		// parent.second = new expr (high, low.op, low.second)
		// I think this is just a left rotate??


		TreeNode* root;
		if (tokens->at(it).token_type == T_semicolon) {
			//std::cout << "counter: " << expr_counter << std::endl;
		}
		if (tokens->at(it).token_type == T_else) {
			has_else = true;
		}
		if (tokens->at(it).token_type == T_semicolon && expr_counter == 0) {
			// std::cout << "-------------------;;;;;;;;;;;;" << std::endl;
			if (ast_node_stack.back()->node_data->getNodeType() != AST_list_statements) {
				ast_node_stack.pop_back();
			}
			printAstNodeStack();
			return;
		}
		
		switch (rule.id) {
			case 1: // PROGRAM -> STATEMENT_SEQ  DECLARATIONS  FDECLS
				root = program_tree->insert(new NodeHeader(AST_program));
				ast_node_stack.push_back(root);
				astAddStandardRule(rule);
				break;
			case 3: // FDECLS -> null
				ast_node_stack.pop_back();
				break;
			case 4: //G_FDEC         T_def G_TYPE G_FNAME T_open_par G_PARAMS T_close_par G_DECLARATIONS G_STATEMENT_SEQ T_fed
			{
				TreeNode* func = program_tree->insert(new NodeFunction(AST_func_declaration, "default", VT_default), ast_node_stack.back());
				ast_node_stack.push_back(func);
				break;
			}
			case 5: //G_PARAMS      G_TYPE G_VAR G_PARAM_OPT 
			{
				TreeNode* parm = program_tree->insert(new NodeVariable(AST_parameter, "default", VT_default), ast_node_stack.back());
				ast_node_stack.push_back(parm);
				break;
			}
			case 6: //G_PARAMS      T_null
			{
				ast_node_stack.pop_back();
				break;
			}
			case 7: //G_PARAM_OPT      T_comma G_PARAMS
			{
				ast_node_stack.pop_back();
				break;
			}
			case 8: // G_PARAM_OPT      T_null
			{
				ast_node_stack.pop_back();
				break;
			}
			case 10: //DECLARATIONS -> DECL ; DECLARATIONS
			{
				if (ast_node_stack.back()->node_data->getNodeType() == AST_func_declaration) {
					TreeNode* decl_list = program_tree->insert(new NodeHeader(AST_list_declarations), ast_node_stack.back());
					ast_node_stack.push_back(decl_list);
				}
				TreeNode* decl = program_tree->insert(new NodeDeclaration(AST_declaration, VT_int), ast_node_stack.back());
				ast_node_stack.push_back(decl);
				break;
			}
			case 11: //G_DECLARATIONS      T_null
				ast_node_stack.pop_back();
				type_buffer = VT_default;
				break;
			case 12: //DECL -> TYPE VARLIST
			{
				TreeNode * varl = program_tree->insert(new NodeHeader(AST_list_variables), ast_node_stack.back());
				ast_node_stack.push_back(varl);
				break;
			}
			case 13: //G_TYPE -> T_kw_int
			{
				if (ast_node_stack.back()->node_data->getNodeType() == AST_func_declaration) {
					ast_node_stack.back()->node_data->setVarType(VT_int);
				}
				else if (ast_node_stack.back()->node_data->getNodeType() == AST_parameter) {
					ast_node_stack.back()->node_data->setVarType(VT_int);
				}
				else {
					ast_node_stack.at(ast_node_stack.size() - 2)->node_data->setVarType(VT_int);
					type_buffer = VT_int;
				}
				break;
			}
			case 14: //G_TYPE -> T_kw_double
			{
				if (ast_node_stack.back()->node_data->getNodeType() == AST_func_declaration) {
					ast_node_stack.back()->node_data->setVarType(VT_double);
				}
				else if (ast_node_stack.back()->node_data->getNodeType() == AST_parameter) {
					ast_node_stack.back()->node_data->setVarType(VT_double);
				}
				else {
					ast_node_stack.at(ast_node_stack.size() - 2)->node_data->setVarType(VT_double);
					type_buffer = VT_double;
				}
				break;
			}
			case 17: //G_VARLIST_P -> T_null
				break;
			case 18: //G_STATEMENT_SEQ      G_STATEMENT T_semicolon G_STATEMENT_SEQ
			{
				if (in_stmt_seq == false && ast_node_stack.back()->node_data->getNodeType() == AST_func_declaration) {
					TreeNode* seq = program_tree->insert(new NodeHeader(AST_list_statements), ast_node_stack.back());
					ast_node_stack.push_back(seq);
					in_stmt_seq = true;
				}
				if (/*in_stmt_seq == false && */ast_node_stack.back()->node_data->getNodeType() == AST_while) {
					TreeNode* seq = program_tree->insert(new NodeHeader(AST_list_statements), ast_node_stack.back());
					ast_node_stack.push_back(seq);
					in_stmt_seq = true;
				}
				if (/*in_stmt_seq == false && */ast_node_stack.back()->node_data->getNodeType() == AST_if) {
					TreeNode* seq = program_tree->insert(new NodeHeader(AST_list_statements), ast_node_stack.back());
					ast_node_stack.push_back(seq);
					in_stmt_seq = true;
				}
				if (/*in_stmt_seq == false && */ast_node_stack.back()->node_data->getNodeType() == AST_else) {
					TreeNode* seq = program_tree->insert(new NodeHeader(AST_list_statements), ast_node_stack.back());
					ast_node_stack.push_back(seq);
					in_stmt_seq = true;
				}
				break;
			}
			case 19: //G_STATEMENT_SEQ      T_null
				if (ast_node_stack.back()->node_data->getNodeType() == AST_list_statements) {
					ast_node_stack.pop_back();
					ast_node_stack.pop_back();
					in_stmt_seq = false;
				}
				else if (ast_node_stack.back()->node_data->getNodeType() == AST_while) {
					ast_node_stack.pop_back();
					in_stmt_seq = false;
				}
				else if (ast_node_stack.back()->node_data->getNodeType() == AST_if) {
					ast_node_stack.pop_back();
					in_stmt_seq = false;
				}
				else if (ast_node_stack.back()->node_data->getNodeType() == AST_else) {
					ast_node_stack.pop_back();
					in_stmt_seq = false;
				}
				break;
			case 20: //G_STATEMENT      G_VAR T_eq G_EXPR
			{
				TreeNode * asgn = program_tree->insert(new NodeHeader(AST_assignment), ast_node_stack.back());
				ast_node_stack.push_back(asgn);
				break;
			}
			case 21: //G_STATEMENT      T_if T_open_par G_EXPR T_close_par T_then G_STATEMENT_SEQ G_STREPLC_P T_fi
			{
				in_if_statement = true;
				TreeNode* asgn = program_tree->insert(new NodeHeader(AST_if), ast_node_stack.back());
				ast_node_stack.push_back(asgn);
				last_if = asgn;
				break;
			}
			case 22: //G_STATEMENT      T_while T_open_par G_EXPR T_close_par T_do G_STATEMENT_SEQ T_od
			{
				in_while_statement = true;
				TreeNode* asgn = program_tree->insert(new NodeHeader(AST_while), ast_node_stack.back());
				ast_node_stack.push_back(asgn);
				break;
			}
			case 23: //G_STATEMENT      T_print T_open_par G_EXPR T_close_par
			{
				in_statement = true;
				TreeNode* asgn = program_tree->insert(new NodeHeader(AST_print), ast_node_stack.back());
				ast_node_stack.push_back(asgn);
				break;
			}
			case 24: //G_STATEMENT      T_return T_open_par G_EXPR T_close_par 
			{
				in_statement = true;
				TreeNode* asgn = program_tree->insert(new NodeHeader(AST_return), ast_node_stack.back());
				ast_node_stack.push_back(asgn);
				break;
			}
			case 26: //G_STREPLC_P      T_else G_STATEMENT_SEQ
			{
				in_else_statement = true;
				TreeNode* els = program_tree->insert(new NodeHeader(AST_else), ast_node_stack.back());
				ast_node_stack.push_back(els);
				last_if->node_data->setNodeType(AST_if_with_else);
				break;
			}
			case 27: //G_STREPLC_P      T_null
			{
				break;
			}
			case 28: //G_EXPR         G_TERM G_EXPR_P
			{
				expr_counter = 0;
				TreeNode* asgn = program_tree->insert(new NodeExpression(AST_expression), ast_node_stack.back());
				ast_node_stack.push_back(asgn);
				break;
			}
			case 29: //G_EXPR_P	      T_not G_TERM G_EXPR_P
			{
				std::cout << "got to case 29" << std::endl;
				ast_node_stack.back()->node_data->setOpType(OP_not);
				TreeNode* expr = program_tree->insert(new NodeExpression(AST_expression), ast_node_stack.back());
				ast_node_stack.push_back(expr);
				expr_counter++;
				break;
			}
			case 30: //G_EXPR_P      T_plus G_TERM G_EXPR_P
			{
				ast_node_stack.back()->node_data->setOpType(OP_plus);
				TreeNode* expr = program_tree->insert(new NodeExpression(AST_expression), ast_node_stack.back());
				ast_node_stack.push_back(expr);
				expr_counter++;
				break;
			}
			case 31: //G_EXPR_P      T_minus G_TERM G_EXPR_P
			{
				ast_node_stack.back()->node_data->setOpType(OP_minus);
				TreeNode* expr = program_tree->insert(new NodeExpression(AST_expression), ast_node_stack.back());
				ast_node_stack.push_back(expr);
				expr_counter++;
				break;
			}
			case 32: //G_EXPR_P      T_or G_TERM G_EXPR_P
			{
				ast_node_stack.back()->node_data->setOpType(OP_or);
				TreeNode* expr = program_tree->insert(new NodeExpression(AST_expression), ast_node_stack.back());
				ast_node_stack.push_back(expr);
				expr_counter++;
				break;
			}
			case 33: //G_EXPR_P      G_COMP G_TERM G_EXPR_P
			{
				ast_node_stack.back()->node_data->setOpType(OP_default);
				TreeNode* expr = program_tree->insert(new NodeExpression(AST_expression), ast_node_stack.back());
				ast_node_stack.push_back(expr);
				expr_counter++;
				break;
			}
			case 34: //G_EXPR_P      T_null
				std::cout << "---------------------> EXPRESSION COUNTER  ==== " << expr_counter << std::endl;
				std::cout << "reached case 34" << std::endl;
				while (expr_counter > 0) {
					std::cout << "---------------------> EXPRESSION COUNTER " << expr_counter << std::endl;
					ast_node_stack.pop_back();
					expr_counter--;
				}
				if (tokens->at(it).token_type == T_semicolon) {
					ast_node_stack.pop_back();
				}
				if (in_while_statement) {
					in_while_statement = false;
					ast_node_stack.pop_back();
				}
				if (in_if_statement) {
					in_if_statement = false;
					ast_node_stack.pop_back();
				}
				if (in_else_statement) {
					//in_else_statement = false;
					//ast_node_stack.pop_back();
				}
				else if (in_statement) {
					in_statement = false;
					ast_node_stack.pop_back();
					ast_node_stack.pop_back();
				}
				if (in_expr_seq) {
					ast_node_stack.pop_back();
				}
				// Pop back for every expression encountered
				break;
			case 36: //G_TERM_P      T_star G_FACTOR G_TERM_P
			{
				ast_node_stack.back()->node_data->setOpType(OP_times);
				TreeNode* expr = program_tree->insert(new NodeExpression(AST_expression), ast_node_stack.back());
				ast_node_stack.push_back(expr);
				expr_counter++;
				break;
			}
			case 37: //G_TERM_P      T_slash G_FACTOR G_TERM_P
			{
				ast_node_stack.back()->node_data->setOpType(OP_divide);
				TreeNode* expr = program_tree->insert(new NodeExpression(AST_expression), ast_node_stack.back());
				ast_node_stack.push_back(expr);
				expr_counter++;
				break;
			}
			case 38: //G_TERM_P      T_mod G_FACTOR G_TERM_P
			{
				ast_node_stack.back()->node_data->setOpType(OP_mod);
				TreeNode* expr = program_tree->insert(new NodeExpression(AST_expression), ast_node_stack.back());
				ast_node_stack.push_back(expr);
				expr_counter++;
				break;
			}
			case 39: //G_TERM_P      T_and G_FACTOR G_TERM_P
			{
				ast_node_stack.back()->node_data->setOpType(OP_and);
				TreeNode* expr = program_tree->insert(new NodeExpression(AST_expression), ast_node_stack.back());
				ast_node_stack.push_back(expr);
				expr_counter++;
				break;
			}
			case 40: //G_TERM_P      T_null
			{
				break;
			}
			case 41: //G_FACTOR      G_ID G_FUNCOPTS
			{
				TreeNode* facvar = program_tree->insert(new NodeHeader(AST_factor_var), ast_node_stack.back());
				ast_node_stack.push_back(facvar);
				break;
			}
			case 42: //G_FACTOR      G_NUMBER    we can start the number builder
			{
				TreeNode* fac = program_tree->insert(new NodeConstFactor(AST_factor_const), ast_node_stack.back());
				ast_node_stack.push_back(fac);
				break;
			}
			case 44: //G_FUNCOPTS      T_open_par G_EXPRSEQ T_close_par 
			{
				std::string name = ast_node_stack.back()->children.at(0)->node_data->getNodeStrVal();
				ast_node_stack.back()->children.erase(ast_node_stack.back()->children.begin());
				
				NodeExpression* new_expr_data = new NodeExpression(AST_expression);
				delete ast_node_stack.back()->node_data;
				ast_node_stack.back()->node_data = new_expr_data;
				ast_node_stack.back()->node_data->setOpType(OP_single_factor); // TEMPORARY, need to get actual op
				
				TreeNode* fun_call = program_tree->insert(new NodeHeader(AST_func_call), ast_node_stack.back());
				ast_node_stack.push_back(fun_call);
				// Instead, replace the node with a nodeExpression
				ast_node_stack.back()->node_data->setStrVal(name);
				ast_node_stack.back()->node_data->setNodeType(AST_func_call);
				in_func_call = true;
				break;
			}
			case 45: //G_FUNCOPTS      T_null
				break;
			case 46: //G_EXPRSEQ      G_EXPR G_EXPRSEQ_P
			{
				// Save counter
				if (!in_expr_seq) {
					temp_counter = expr_counter;
					std::cout << "Saved counter: " << expr_counter << std::endl;
				}
				in_expr_seq = true;
				
				break;
			}
			case 47: //G_EXPRSEQ      T_null 
			{
				ast_node_stack.pop_back();	
				
				in_expr_seq = false;
				break;
			}
			case 48: //G_EXPRSEQ_P      T_comma G_EXPRSEQ
			{
				break;
			}
			case 49: //G_EXPRSEQ_P      T_null
				// retrieve counter
				expr_counter = temp_counter;
				std::cout << "Retrieved counter: " << expr_counter << std::endl;
				if (in_expr_seq) {
					std::cout << "in expr seq" << std::endl;
					if (in_func_call) {
						in_func_call = false;
					}
					else {
						ast_node_stack.pop_back();
					}
				}
				in_expr_seq = false;
				ast_node_stack.pop_back();

				break;
			case 50: //G_COMP         T_gt G_COMP_P_P
			{
				ast_node_stack.at(ast_node_stack.size() - 2)->node_data->setOpType(OP_greater);
				break;
			}
			case 51: //G_COMP         T_lt G_COMP_P
			{
				ast_node_stack.at(ast_node_stack.size() - 2)->node_data->setOpType(OP_lesser);
				break;
			}
			case 52: //G_COMP         T_eq T_eq
			{
				ast_node_stack.at(ast_node_stack.size() - 2)->node_data->setOpType(OP_equals);
				break;
			}
			case 54: //G_COMP_P      T_eq
			{
				ast_node_stack.at(ast_node_stack.size() - 2)->node_data->setOpType(OP_lesser_eq);
				break;
			}
			case 55: //G_COMP_P      T_gt
			{
				ast_node_stack.at(ast_node_stack.size() - 2)->node_data->setOpType(OP_unequals);
				break;
			}
			case 57: // G_COMP_P_P      T_eq
			{
				ast_node_stack.at(ast_node_stack.size() - 2)->node_data->setOpType(OP_greater_eq);
				break;
			}
			case 58: //G_VAR         G_ID G_VAR_P
				break;
			case 59: //G_VAR_P         T_null
				break;
			case 61: //G_ID -> T_identifier
			{
				// Insert variable identifier into some buffer so the node can get it?
				NodeType cur_type = ast_node_stack.back()->node_data->getNodeType();
				if (cur_type == AST_list_variables || cur_type == AST_assignment) { //AST_list_variables might have to be changed to AST_declaration
					program_tree->insert(new NodeVariable(AST_variable, tokens->at(it).token_value, type_buffer), ast_node_stack.back());
				}
				else if (cur_type == AST_factor_var) {
					ast_node_stack.back()->node_data->setStrVal(tokens->at(it).token_value);
					ast_node_stack.pop_back();
				}
				else if (cur_type == AST_func_declaration) {
					ast_node_stack.back()->node_data->setStrVal(tokens->at(it).token_value);
				}
				else if (cur_type == AST_parameter) {
					ast_node_stack.back()->node_data->setStrVal(tokens->at(it).token_value);
				}
				break;
			}
			case 62: //G_NUMBER      G_INT G_DECIMAL
				break;
			case 63: //G_DECIMAL      T_dot G_INT G_EXOPT
				ast_node_stack.back()->node_data->appendNumString(tokens->at(it).token_value);
				ast_node_stack.back()->node_data->setVarType(VT_double);
				break;
			case 64: //G_DECIMAL      T_null
				//  we can finish the number builder at this point
				ast_node_stack.pop_back(); // ???
				break;
			case 65: //G_EXOPT         T_exp G_NUMBER
				ast_node_stack.back()->node_data->appendNumString(tokens->at(it).token_value);
				ast_node_stack.back()->node_data->setVarType(VT_double);
				break;
			case 67: //G_INT         T_number
				ast_node_stack.back()->node_data->appendNumString(tokens->at(it).token_value);
				break;
			case 68: // G_INT         T_minus T_number
				ast_node_stack.back()->node_data->appendNumString(tokens->at(it).token_value);
				ast_node_stack.back()->node_data->appendNumString(tokens->at(it + 1).token_value);
				break;
		}
		printAstNodeStack();
	}

	void astAddStandardRule(Rule rule) {
		// Add only the non terminals of a rule that does not need special conditions
		std::vector<TreeNode*> temp_nodes;
		temp_nodes.reserve(16);

		for (int i = 1; i < rule.size; i++) {
			if (rule.data[i] >= G_PROGRAM) {
				NodeType cur_type = nonterminalToNodetype(rule.data[i]);
				// Switch cur_type to different node header types 
				TreeNode *child = program_tree->insert(new NodeHeader(cur_type), ast_node_stack.back());
				temp_nodes.push_back(child);
			}
		}
		// Push to active node stack in reverse order
		for (int j = int(temp_nodes.size()) - 1; j >= 0; j--) {
			// go through temp_nodes backwards to add to node stack
			ast_node_stack.push_back(temp_nodes.at(j));
		}
		//printAstNodeStack();
	}

	NodeType nonterminalToNodetype(int value) {
		switch (value) {
			case G_PROGRAM:
				return AST_program;
			case G_FDECLS:
				return AST_list_func_declarations;
			case G_DECLARATIONS:
				return AST_list_declarations;
			case G_STATEMENT_SEQ:
				return AST_list_statements;
			case G_DECL:
				return AST_declaration;
			case G_TYPE:
				return AST_type;
			case G_VARLIST:
				return AST_list_variables;
			default:
				return AST_head;
		}
	}

	void printAstNodeStack() {
		std::cout << "AST Node Stack: ";
		for (TreeNode* n : ast_node_stack) {
			n->node_data->print();
			std::cout << "   ";
		}
		std::cout << std::endl;
	}
};
