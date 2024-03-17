#include "definitions.h"
#include "LLTable.cpp"
#include <iostream>
#include <string>
#include <fstream>

class NodeData {
public:
	virtual void print() = 0;
};

class NodeHeader : public NodeData {
public:
	NodeType node_type;
	NodeHeader(NodeType type) : node_type(type) {}
	void print() override {
		std::cout << ast_type_names[node_type];
	}
};

struct TreeNode {
	NodeData* node_data;
	std::vector<TreeNode*> children;
	TreeNode(NodeData *nd) : node_data(nd) {}
};

class SyntaxTree {
private:
	TreeNode* root;

	void destroy(TreeNode* node) {
		if (node == nullptr) {
			return;
		}
		for (TreeNode* child : node->children) {
			destroy(child);
		}
		delete node;
	}
public:
	SyntaxTree() : root(nullptr) {}

	~SyntaxTree() {
		destroy(root);
	}

	TreeNode* insert(NodeData* value, TreeNode* parent = nullptr) {
		TreeNode *new_node = new TreeNode(value);
		if (parent == nullptr) {
			if (root == nullptr) {
				root = new_node;
			}
			else {
				std::cerr << "Cannot set root again!" << std::endl;
			}
		}
		else {
			parent->children.push_back(new_node);
		}
		return new_node;
	}

	void print(TreeNode* node, int depth = 0) {
		if (node == nullptr) {
			return;
		}
		for (int i = 0; i < depth; i++) {
			std::cout << "        ";
		}

		node->node_data->print();
		std::cout << std::endl;

		for (TreeNode* child : node->children) {
			print(child, depth + 1);
		}
	}

	void print() {
		print(root);
	}
};

class Parser {
public:
	std::vector<Token> const* tokens; // Tokens from tokenizer
	std::vector<Token> parse_stack; // Stack used for parsing
	SyntaxTree program_tree; // Need to add nodes from a tree in a custom way for rules that need it
	// std::vector<Token> tokens_for_node; // Temporary stack for nodes that need to read values from the token list
	std::vector<TreeNode*> ast_node_stack; // For returning to the node
	LLTable table;

	// Buffers for putting values into nodes
	VarType type_buffer = VT_int;
	OpType  op_buffer = OP_plus;
	std::string num_buffer = "";

	Parser(std::vector<Token> const& token_list) {
		tokens = &token_list;
		parse_stack.reserve(32);
		ast_node_stack.reserve(32);
	}

	int parse() {
		parse_stack.push_back(Token(T_dollar, ""));
		parse_stack.push_back(Token(G_PROGRAM, ""));

		std::ofstream error_file;
		error_file.open("Parsing-Errors.txt", std::ios::out | std::ios::trunc);

		// While we still have tokens left...
		// if current token matches top of stack -> pop 
		// else get the rule  from table[stack.top()][current_literal]
		// then pop the top non literal and replace it with the rule
		
		int it = 0;
		while (it < tokens->size()) {
			int top_type = parse_stack.back().token_type;
			int found_type = tokens->at(it).token_type;
			//std::cout << "Parsing\n";
			
			if ( top_type < NUM_TERMINALS || top_type == T_dollar )  { //top_type is nonterm or dollar
				if (top_type == found_type) {
					// Matched symbols
					parse_stack.pop_back();
					it++;
				}
				else {
					// ERROR
					std::cout << "Error: expected: " << token_names[top_type] << "\t found: " << token_names[found_type] << std::endl;
					error_file << "Error: expected: " << token_names[top_type] << "\t found: " << token_names[found_type] << std::endl;
					// Handle errors by deleting
					parse_stack.pop_back(); // ????
					it++; 
					//return -1;
				}
			}
			else {

				Rule cur = table.getRule( top_type - FIRST_NONLITERAL, found_type);
				parse_stack.pop_back(); // I think every pop makes a node, with the rule that replaced it as the children
				addRule(cur, found_type);
			}
			for (Token i : parse_stack) {
				std::cout << token_names_nice[i.token_type] << "  ";
			}
			if (it < tokens->size()) std::cout << "\t\t\t val: " << token_names_nice[found_type] << std::endl;
			
		}
		std::cout << "Finished parsing successfully" << std::endl;
		std::cout << "\n\n\nAbstract Syntax Tree:" << std::endl;
		
		program_tree.print();

		return 0;
	}

	int addRule(Rule rule, int found_type) {
		// Pushes the elements of a rule on the stack
		// if rule_size is 0 do nothing
		// i stops at 1 because 0 is the first rule 0 -> 1 2 3 ...
		// push in reverse order
		if (rule.size <= 1) {
			return 1;
		}

		astAddRule(rule, found_type);  // build AST

		for (int i = rule.size - 1; i >= 1; i--) {
			//std::cout << "i: " << i << std::endl;
			if (rule.data[i] == T_null) {
				//parse_stack.pop_back(); unnecessary 
				//std::cout << "null" << std::endl;
				return 2;
			}
			Token nonlit(rule.data[i], "");
			parse_stack.push_back(nonlit);	
		}
		//std::cout << std::endl;
		return 0;
	}


	void astAddRule(Rule rule, int found_type) {
		TreeNode* root;
		if (found_type == T_semicolon) {
			ast_node_stack.pop_back();
		}
		switch (rule.id) {
			case 1: // PROGRAM -> STATEMENT_SEQ  DECLARATIONS  FDECLS
				root = program_tree.insert(new NodeHeader(AST_program));
				ast_node_stack.push_back(root);
				astAddStandardRule(rule);
				break;
			case 3: // FDECLS -> null
				ast_node_stack.pop_back();
				//std::cout << "FDECLS -> NULL" << std::endl;
				break;
			case 10: //DECLARATIONS -> DECL ; DECLARATIONS
				{
				TreeNode* decl = program_tree.insert(new NodeHeader(AST_declaration), ast_node_stack.back());
				ast_node_stack.push_back(decl);
				break;
				}
			case 11: //G_DECLARATIONS      T_null
				ast_node_stack.pop_back();
				break;
			case 12: //DECL -> TYPE VARLIST
				astAddStandardRule(rule);
				break;
			case 13: //G_TYPE -> T_kw_int
				// TODO: add type to some buffer maybe?
				ast_node_stack.pop_back();
				break;
			case 14: //G_TYPE -> T_kw_double
				// TODO: add type
				ast_node_stack.pop_back();
				break;
			case 17: //G_VARLIST_P -> T_null
				break;
			case 20: //G_STATEMENT      G_VAR T_eq G_EXPR
				{
				TreeNode * asgn = program_tree.insert(new NodeHeader(AST_assignment), ast_node_stack.back());
				ast_node_stack.push_back(asgn);
				break;
				}
			case 28: //G_EXPR         G_TERM G_EXPR_P
				{
				TreeNode* asgn = program_tree.insert(new NodeHeader(AST_expression), ast_node_stack.back());
				ast_node_stack.push_back(asgn);
				break;
				}
			case 31: //G_EXPR_P      T_minus G_TERM G_EXPR_P
				{
				program_tree.insert(new NodeHeader(AST_operator), ast_node_stack.back());
				TreeNode* expr = program_tree.insert(new NodeHeader(AST_expression), ast_node_stack.back());
				ast_node_stack.push_back(expr);
				break;
				}
			case 34: //G_EXPR_P      T_null
				
				break;
			case 42: //G_FACTOR      G_NUMBER
			{
				TreeNode* asgn = program_tree.insert(new NodeHeader(AST_factor_const), ast_node_stack.back());
				ast_node_stack.push_back(asgn);
				break;
			}
			case 59: //G_VAR_P         T_null
				break;
			case 58: //G_VAR         G_ID G_VAR_P
				program_tree.insert(new NodeHeader(AST_variable), ast_node_stack.back());
				break;
			case 61: //G_ID -> T_identifier
				// Insert variable identifier into some buffer so the node can get it?
				break;
			case 62: //G_NUMBER      G_INT G_DECIMAL
				ast_node_stack.pop_back();
				break;
		}
		//printAstNodeStack();
	}

	void astAddStandardRule(Rule rule) {
		// Add only the non terminals of a rule that does not need special conditions
		std::vector<TreeNode*> temp_nodes;
		temp_nodes.reserve(16);

		for (int i = 1; i < rule.size; i++) {
			if (rule.data[i] >= G_PROGRAM) {
				NodeType cur_type = nonterminalToNodetype(rule.data[i]);
				TreeNode *child = program_tree.insert(new NodeHeader(cur_type), ast_node_stack.back());
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
	//G_PROGRAM = NUM_TOKEN_TYPES, // Start at the end of TokenType so we can use both together
	//G_FDECLS,
	//G_FDEC,			// Function declaration // def int func(int x, double y) body fed
	//G_PARAMS,		// Paramters of function // (int x, double y) 
	//G_PARAM_OPT,
	//G_FNAME,		// Defined name // x 
	//G_DECLARATIONS,
	//G_DECL,			// Variable declaration // int x, y;
	//G_TYPE,			// int // double
	//G_VARLIST,
	//G_VARLIST_P,
	//G_STATEMENT_SEQ,
	//G_STATEMENT,		// x = y // if .. // while ... // print // return // null
	//G_STREPLC_P,
	//G_EXPR,			// binary operations // a + b // a - b
	//G_EXPR_P,
	//G_TERM,			// binary operations // a * b // a / b // a % b
	//G_TERM_P,
	//G_FACTOR,		// thing in operation 
	//G_FUNCOPTS,
	//G_EXPRSEQ,
	//G_EXPRSEQ_P,
	//G_COMP,			// Comparison // x 
	//G_COMP_P,
	//G_COMP_P_P,
	//G_VAR,			// Variable  // x
	//G_VAR_P,		// Array     // ..[expr]
	//G_ID,			// Identifier
	//G_NUMBER,
	//G_DECIMAL,		// if this exists a number is type double
	//G_EXOPT,		// exponential in double
	//G_INT
	
};
