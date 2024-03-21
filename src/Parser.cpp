#include "definitions.h"
#include "LLTable.cpp"
#include <iostream>
#include <string>
#include <fstream>

class NodeData {
public:
	virtual void print() = 0;
	virtual void setVarType(VarType t) = 0;
	virtual void setStrVal(std::string s) = 0;
	virtual void appendNumString(std::string s) = 0;
	virtual NodeType getNodeType() = 0; // TODO: only have this function once instead of defined in every base class
	virtual void	 setNodeType(NodeType n) = 0;
	virtual ~NodeData() {}
};

class NodeHeader : public NodeData {
public:
	NodeType node_type;
	std::string str_value = "";
	NodeHeader(NodeType type) : node_type(type) {}
	NodeHeader(NodeType type, std::string s) : node_type(type), str_value(s) {}
	void print() override {
		std::cout << ast_type_names[node_type];
		if (node_type == AST_factor_var) {
			std::cout << "    " << str_value;
		}
	}
	void setVarType(VarType t) override {
		;
	}
	void setStrVal(std::string s) override {
		str_value = s;
	}
	void appendNumString(std::string s) {
		;
	}
	NodeType getNodeType() {
		return node_type;
	}
	void setNodeType(NodeType n) {
		node_type = n;
	}
};

class NodeDeclaration : public NodeData {
public:
	NodeType node_type;
	VarType var_type;
	NodeDeclaration(NodeType type, VarType v) : node_type(type), var_type(v) {}
	void print() override {
		std::cout << ast_type_names[node_type] << "    type: " << type_names[var_type];
	}
	void setVarType(VarType t) override {
		var_type = t;
	}
	void setStrVal(std::string s) override {
		;
	}
	void appendNumString(std::string s) {
		std::cout << "Function Should not be called" << std::endl;
	}
	NodeType getNodeType() {
		return node_type;
	}
	void setNodeType(NodeType n) {
		node_type = n;
	}
};

class NodeConstFactor : public NodeData {
public:
	NodeType node_type;
	VarType var_type = VT_int; //int by default
	std::string num_str = "";
	NodeConstFactor(NodeType type) : node_type(type) {}
	void print() override {
		std::cout << ast_type_names[node_type] << "    type: " << type_names[var_type] << "    val: " << num_str;
	}
	void setVarType(VarType t) override {
		var_type = t;
	}
	void setStrVal(std::string s) override {
		;
	}
	void appendNumString(std::string s) override {
		num_str.append(s);
	}
	NodeType getNodeType() {
		return node_type;
	}
	void setNodeType(NodeType n) {
		node_type = n;
	}
};

class NodeVariable : public NodeData {
public:
	NodeType node_type;
	VarType var_type = VT_int; //int by default
	std::string var_name = "";
	NodeVariable(NodeType t, std::string n, VarType vt) : node_type(t), var_name(n), var_type(vt)  {}
	void print() override {
		std::cout << ast_type_names[node_type] << "    type: " << type_names[var_type] << "    name: " << var_name;
	}
	void setVarType(VarType t) override {
		var_type = t;
	}
	void setStrVal(std::string s) override {
		;
	}
	void appendNumString(std::string s) override {
		;
	}
	NodeType getNodeType() {
		return node_type;
	}
	void setNodeType(NodeType n) {
		node_type = n;
	}
};

struct TreeNode {
	NodeData* node_data;
	std::vector<TreeNode*> children;
	TreeNode(NodeData *nd) : node_data(nd) {}
};

struct Variable {
	std::string name;
	VarType		type;
	Variable(std::string n, VarType t) : name(n), type(t) {}
};

class SyntaxTree {
private:
	TreeNode* root;
	std::vector<Variable> var_table;

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
		for (int i = 0; i < depth - 1; i++) {
			std::cout << "    ";
		}
		if (depth > 0) std::cout << "|___";
		else std::cout << "    ";

		node->node_data->print();
		std::cout << std::endl;

		for (TreeNode* child : node->children) {
			print(child, depth + 1);
		}
	}

	void print() {
		print(root);
	}

	TreeNode* getRoot() {
		return root;
	}

	void buildSymbolTable(TreeNode* node, bool in_decl) {
		//std::cout << ast_type_names[node->node_data->getNodeType()];
		//std::cout << std::endl;
		if (node == nullptr) {
			return;
		}
		if (in_decl && node->node_data->getNodeType() == AST_variable) {
			NodeVariable* tempVar = dynamic_cast<NodeVariable*>(node->node_data);
			for (Variable v : var_table) {
				if (tempVar->var_name == v.name) {
					std::cout << "Variable " << tempVar->var_name << " already in symbol table!" << std::endl;
				}
			}
			var_table.push_back(Variable(tempVar->var_name, tempVar->var_type));
		}
		for (TreeNode* child : node->children) {
			if (node->node_data->getNodeType() == AST_declaration || in_decl == true) {
				buildSymbolTable(child, true);
			}
			else {
				buildSymbolTable(child, false);
			}
		}
	}

	void printSymbolTable() {
		for (Variable i : var_table) {
			std::cout << i.name << "    " << type_names[i.type] << std::endl;
		}
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
				addRule(cur, it);
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


	void astAddRule(Rule rule, int it) {

		static VarType type_buffer = VT_int;
		//OpType  op_buffer = OP_plus;

		// MAJOR TODO:::: write an operator presadence swapper:
		// Potential way: (might work???)
		// find expr (parent) (high prec) (low prec)
		// high.second = low.first
		// parent.second = new expr (high, low.op, low.second)
		// I think this is just a left rotate??

		// Can also start working on the symbol table


		TreeNode* root;
		if (tokens->at(it).token_type == T_semicolon) {
			ast_node_stack.pop_back();
			//std::cout << "semicolon pop" << std::endl;
			//printAstNodeStack();
			return;
			
		}
		switch (rule.id) {
			case 1: // PROGRAM -> STATEMENT_SEQ  DECLARATIONS  FDECLS
				root = program_tree.insert(new NodeHeader(AST_program));
				ast_node_stack.push_back(root);
				astAddStandardRule(rule);
				break;
			case 3: // FDECLS -> null
				ast_node_stack.pop_back();
				break;
			case 10: //DECLARATIONS -> DECL ; DECLARATIONS
			{
				TreeNode* decl = program_tree.insert(new NodeDeclaration(AST_declaration, VT_int), ast_node_stack.back());
				ast_node_stack.push_back(decl);
				break;
			}
			case 11: //G_DECLARATIONS      T_null
				ast_node_stack.pop_back();
				type_buffer = VT_default;
				break;
			case 12: //DECL -> TYPE VARLIST
			{
				TreeNode * varl = program_tree.insert(new NodeHeader(AST_list_variables), ast_node_stack.back());
				ast_node_stack.push_back(varl);
				break;
			}
			case 13: //G_TYPE -> T_kw_int
				ast_node_stack.at(ast_node_stack.size() - 2)->node_data->setVarType(VT_int);
				type_buffer = VT_int;
				break;
			case 14: //G_TYPE -> T_kw_double
				ast_node_stack.at(ast_node_stack.size() - 2)->node_data->setVarType(VT_double);
				type_buffer = VT_double;
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
			case 36: //G_TERM_P      T_star G_FACTOR G_TERM_P
			{
				program_tree.insert(new NodeHeader(AST_operator), ast_node_stack.back());
				TreeNode* expr = program_tree.insert(new NodeHeader(AST_expression), ast_node_stack.back());
				ast_node_stack.push_back(expr);
				break;
			}
			case 41: //G_FACTOR      G_ID G_FUNCOPTS
			{
				// Need to figure out if funcopts was called or not
				// Maybe start as a NodeName(AST_factor_var) in here, and if funcopts was used
				// Then change its type to AST_fun_call
				TreeNode* facvar = program_tree.insert(new NodeHeader(AST_factor_var), ast_node_stack.back());
				ast_node_stack.push_back(facvar);
				break;
			}
			case 42: //G_FACTOR      G_NUMBER    we can start the number builder
			{
				TreeNode* fac = program_tree.insert(new NodeConstFactor(AST_factor_const), ast_node_stack.back());
				ast_node_stack.push_back(fac);
				break;
			}
			case 44: //G_FUNCOPTS      T_open_par G_EXPRSEQ T_close_par 
			{
				ast_node_stack.back()->node_data->setNodeType(AST_func_call);
				break;
			}
			case 48: //G_EXPRSEQ_P      T_comma G_EXPRSEQ
			{
				ast_node_stack.pop_back();
				break;
			}
			case 49: //G_EXPRSEQ_P      T_null
				ast_node_stack.pop_back();
				break;

			case 59: //G_VAR_P         T_null
				break;
			case 58: //G_VAR         G_ID G_VAR_P
				break;
			case 61: //G_ID -> T_identifier
				// Insert variable identifier into some buffer so the node can get it?
				if (ast_node_stack.back()->node_data->getNodeType() == AST_list_variables) { //AST_list_variables might have to be changed to AST_declaration
					program_tree.insert(new NodeVariable(AST_variable, tokens->at(it).token_value, type_buffer), ast_node_stack.back());
				}
				else if (ast_node_stack.back()->node_data->getNodeType() == AST_factor_var) {
					ast_node_stack.back()->node_data->setStrVal(tokens->at(it).token_value);
					ast_node_stack.pop_back();
				}
				break;
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
			// CASE 42: FACTOR  -> NUMBER we can start the number builder
			// CASE 64: DECIMAL -> null we can finish the number builder at this point
			
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
				// Switch cur_type to different node header types 
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
};
