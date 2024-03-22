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
	virtual std::string	 getNodeStrVal() = 0;
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
	void setVarType(VarType t) override {}

	void setStrVal(std::string s) override {
		str_value = s;
	}
	std::string	 getNodeStrVal() {
		return str_value;
	}
	void appendNumString(std::string s) {}

	NodeType getNodeType() {
		return node_type;
	}
	void setNodeType(NodeType n) {
		node_type = n;
	}
};

class NodeFunction : public NodeData {
public:
	NodeType node_type;
	std::string function_name;
	VarType function_type; // return type
	NodeFunction(NodeType type, std::string s, VarType vt) : node_type(type), function_name(s), function_type(vt) {}
	void print() override {
		std::cout << ast_type_names[node_type] << "    name: " << function_name << "    return type: " << type_names[function_type];
	}
	void setVarType(VarType t) override {
		function_type = t;
	}
	void setStrVal(std::string s) override {
		function_name = s;
	}
	std::string	 getNodeStrVal() {
		return function_name;
	}
	void appendNumString(std::string s) {}

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

	void setStrVal(std::string s)  {}
	std::string	 getNodeStrVal() { return ""; }

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
	void setStrVal(std::string s) override {}
	std::string	 getNodeStrVal() { return ""; }

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

struct Variable {
	std::string name;
	VarType		type;
	Variable() : name("def"), type(VT_default) {}
	Variable(std::string n, VarType t) : name(n), type(t) {}
};

class NodeVariable : public NodeData {
public:
	NodeType node_type;
	Variable var;
	NodeVariable(NodeType t, std::string n, VarType vt) {
		node_type = t;
		var.name = n;
		var.type = vt;
	}
	void print() override {
		std::cout << ast_type_names[node_type] << "    type: " << type_names[var.type] << "    name: " << var.name;
	}
	void setVarType(VarType t) override {
		var.type = t;
	}
	void setStrVal(std::string s) override {
		var.name = s;
	}
	void appendNumString(std::string s) override {}
	std::string	 getNodeStrVal() {
		return var.name;
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
	~TreeNode() {
		delete node_data;
	}
};



class SyntaxTree {
private:
	TreeNode* root;
	std::vector<Variable> var_table;

	std::ofstream error_file;
	

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
	SyntaxTree() : root(nullptr) {
		error_file.open("Semantic-Errors.txt", std::ios::out | std::ios::trunc);
	}

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
		if (depth > 0) {
			std::cout << "|___";
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

	TreeNode* getRoot() {
		return root;
	}

	// Looks up variables by name in a table
	Variable variableLookup(Variable var) {
		for (Variable v : var_table) {
			if (v.name == var.name) {
				return v;
			}
		}
		return Variable("", VT_invalid);
	}

	VarType typeCheckExpression(TreeNode* node) {
		if (node == nullptr) {
			return VT_default;
		}
		NodeType my_type = node->node_data->getNodeType();
		if (my_type == AST_expression) {
			if (node->children.size() == 1) {
				return typeCheckExpression(node->children.at(0));
			}
			else if (node->children.size() == 3) { //TODO: needs to be changed to 2 if we remove AST_operator
				VarType lhs = typeCheckExpression(node->children.at(0));
				VarType rhs = typeCheckExpression(node->children.at(2));
				if (lhs == rhs) {
					std::cout << "Expression Types Matched" << std::endl;
				}
				else {
					std::cout << "EXPRESSION TYPE MISMATCH!!" << std::endl;
					error_file << "EXPRESSION TYPE MISMATCH!!" << std::endl;
					return VT_invalid;
				}
				return lhs;
			}
		}
		else if (my_type == AST_factor_const) {
			NodeConstFactor* tempConst = dynamic_cast<NodeConstFactor*>(node->node_data);
			std::cout << "Found factor const type: " << type_names[tempConst->var_type] << std::endl;
			return tempConst->var_type;
		}
		else if (my_type == AST_factor_var) {
			std::string node_var_name = node->node_data->getNodeStrVal();
			// Find symbol in symbol table
			Variable looked_up = variableLookup(Variable(node_var_name, VT_default));
			std::cout << "Found factor var type: " << type_names[looked_up.type] << std::endl;
			return looked_up.type;
		}
		else if (my_type == AST_func_call) {
			// ignore for now, should return the (return type) of the func
			return VT_invalid;
		}
		else {
			return VT_invalid;
		}
		return VT_invalid;
	}

	VarType typeCheckTree(TreeNode* node) {
		if (node == nullptr) {
			return VT_default;
		}
		NodeType cur_type = node->node_data->getNodeType();
		VarType lhs = VT_default;
		VarType rhs = VT_default;
		if (cur_type == AST_assignment) {
			if (node->children.at(0)->node_data->getNodeType() != AST_variable) return VT_invalid;
			NodeVariable* tempVar = dynamic_cast<NodeVariable*>(node->children.at(0)->node_data);

			lhs = variableLookup(tempVar->var).type;
			std::cout << "Found assignment variable: " << type_names[lhs] << std::endl;
			rhs = typeCheckExpression(node->children.at(1));
			if (lhs == rhs) {
				std::cout << "Assignment Types Matched" << std::endl;
			}
			else {
				std::cout << "ASSIGNMENT TYPE MISMATCH!!" << std::endl;
				error_file << "ASSIGNMENT TYPE MISMATCH!!" << std::endl;
				return VT_invalid;
			}
		}

		for (TreeNode* child : node->children) {
			typeCheckTree(child);
		}
		return lhs;
	}

	void buildSymbolTable(TreeNode* node, bool in_decl) {
		if (node == nullptr) {
			return;
		}
		if (in_decl && node->node_data->getNodeType() == AST_variable) {
			NodeVariable* tempVar = dynamic_cast<NodeVariable*>(node->node_data);
			for (Variable v : var_table) {
				if (tempVar->var.name == v.name) {
					std::cout << "Variable " << tempVar->var.name << " already in symbol table!" << std::endl;
				}
			}
			var_table.push_back(Variable(tempVar->var.name, tempVar->var.type));
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

	// Function to make sure all symbols can be found in the symbol table
	void checkSymbolReferences(TreeNode* node, bool in_stmt) {
		if (node == nullptr) {
			return;
		}
		NodeType cur_type = node->node_data->getNodeType();
		if (in_stmt && (cur_type == AST_factor_var || cur_type == AST_variable)) {
			bool found = false;
			for (Variable v : var_table) {
				if (v.name == node->node_data->getNodeStrVal()) {
					std::cout << "Found variable " << v.name << "    type:" << type_names[v.type] << std::endl;
					found = true;
				}
			}
			if (!found) {
				std::cout << "COULD NOT FIND VARIABLE " << node->node_data->getNodeStrVal() << std::endl;
				error_file << "COULD NOT FIND VARIABLE " << node->node_data->getNodeStrVal() << std::endl;
			}
		}
		for (TreeNode* child : node->children) {
			if (cur_type == AST_assignment || in_stmt == true) {
				checkSymbolReferences(child, true);
			}
			else {
				checkSymbolReferences(child, false);
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
	SyntaxTree *program_tree; // Need to add nodes from a tree in a custom way for rules that need it
	std::vector<TreeNode*> ast_node_stack; // For returning to the node
	LLTable *table;


	Parser(std::vector<Token> const& token_list, SyntaxTree* tree) {
		tokens = &token_list;
		parse_stack.reserve(32);
		ast_node_stack.reserve(32);
		table = new LLTable();
		program_tree = tree;

	}
	~Parser() {
		// TODO: deleting table causes heap corruption
		;
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
					parse_stack.pop_back();
					it++;
				}
				else {
					// ERROR
					std::cout << "Error: expected: " << token_names[top_type] << "\t found: " << token_names[found_type] << std::endl;
					error_file << "Error: expected: " << token_names[top_type] << "\t found: " << token_names[found_type] << std::endl;
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
			for (Token i : parse_stack) {
				std::cout << token_names_nice[i.token_type] << "  ";
			}
			if (it < tokens->size()) std::cout << "\t\t\t val: " << token_names_nice[found_type] << std::endl;
			
		}
		std::cout << "Finished parsing successfully" << std::endl;
		std::cout << "\n\n\nAbstract Syntax Tree:" << std::endl;
		
		program_tree->print();

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
			case 10: //DECLARATIONS -> DECL ; DECLARATIONS
			{
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
				break;
			}
			case 19: //G_STATEMENT_SEQ      T_null
				if (ast_node_stack.back()->node_data->getNodeType() == AST_list_statements) {
					ast_node_stack.pop_back();
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
			case 28: //G_EXPR         G_TERM G_EXPR_P
			{
				TreeNode* asgn = program_tree->insert(new NodeHeader(AST_expression), ast_node_stack.back());
				ast_node_stack.push_back(asgn);
				break;
			}
			case 31: //G_EXPR_P      T_minus G_TERM G_EXPR_P
			{
				program_tree->insert(new NodeHeader(AST_operator), ast_node_stack.back());
				TreeNode* expr = program_tree->insert(new NodeHeader(AST_expression), ast_node_stack.back());
				ast_node_stack.push_back(expr);
				break;
			}
			case 34: //G_EXPR_P      T_null
				break;
			case 36: //G_TERM_P      T_star G_FACTOR G_TERM_P
			{
				program_tree->insert(new NodeHeader(AST_operator), ast_node_stack.back());
				TreeNode* expr = program_tree->insert(new NodeHeader(AST_expression), ast_node_stack.back());
				ast_node_stack.push_back(expr);
				break;
			}
			case 41: //G_FACTOR      G_ID G_FUNCOPTS
			{
				// Need to figure out if funcopts was called or not
				// Maybe start as a NodeName(AST_factor_var) in here, and if funcopts was used
				// Then change its type to AST_fun_call
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
				ast_node_stack.back()->node_data->setNodeType(AST_func_call);
				break;
			}
			case 45: //G_FUNCOPTS      T_null
				//ast_node_stack.pop_back();
				break;
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
					std::cout << "got here ------------------------ " << tokens->at(it).token_value << std::endl;
					ast_node_stack.back()->node_data->print();
					std::cout << std::endl;
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
