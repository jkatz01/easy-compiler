#include "definitions.h"
#include <iostream>
#include <fstream>

class NodeData {
protected:
	NodeType node_type;
public:
	
	NodeData() {node_type = AST_head;}
	NodeData(NodeType type) {
		node_type = type;
	}

	virtual void		print() {};
	virtual void		setVarType(VarType t) {};
	virtual void		setStrVal(std::string s) {};
	virtual void		setOpType(OpType t) {std::cout << "set op type called" << std::endl;};
	virtual void		appendNumString(std::string s) {};
	
	virtual std::string	getNodeStrVal() {return "";};
	void				setNodeType(NodeType n) { node_type = n; }
	NodeType			getNodeType() { return node_type; };
};

class NodeHeader : public NodeData {
public:
	std::string str_value = "";
	NodeHeader(NodeType type) : NodeData(type) {}
	NodeHeader(NodeType type, std::string s) : NodeData(type) {
		str_value = s;
	}
	void print() override {
		std::cout << ast_type_names[node_type];
		if (node_type == AST_factor_var) { std::cout << "    name: " << str_value; }
	}

	void		setStrVal(std::string s) override { str_value = s; }
	std::string getNodeStrVal() override { return str_value; }
};

class NodeFunction : public NodeData {
public:
	std::string function_name;
	VarType function_type; // return type
	NodeFunction(NodeType type, std::string s, VarType vt) : NodeData(type){
		function_name = s;
		function_type = vt;
	}
	void print() override {
		std::cout << ast_type_names[node_type] << "    name: " << function_name << "    return type: " << type_names[function_type];
	}
	void setVarType(VarType t) override { function_type = t; }
	void setStrVal(std::string s) override { function_name = s; }
	std::string	 getNodeStrVal() override { return function_name; }
};

class NodeExpression : public NodeData {
public:
	OpType op_type = OP_single_factor;
	NodeExpression(NodeType type) : NodeData(type) {}
	void print() override {
		std::cout << ast_type_names[node_type] << "    op: " << operator_names[op_type];
	}
	void setOpType(OpType t) override { op_type = t; }
};

class NodeDeclaration : public NodeData {
public:
	VarType var_type;
	NodeDeclaration(NodeType type, VarType v) : NodeData(type) {
		var_type = v;
	}
	void print() override {
		std::cout << ast_type_names[node_type] << "    type: " << type_names[var_type];
	}
	void setVarType(VarType t) override { var_type = t; }
	std::string	 getNodeStrVal() override { return ""; }
	void appendNumString(std::string s) override { std::cout << "Function Should not be called" << std::endl; }
};

class NodeConstFactor : public NodeData {
public:
	VarType var_type = VT_int; //int by default
	std::string num_str = "";
	NodeConstFactor(NodeType type) : NodeData(type) {}
	void print() override {
		std::cout << ast_type_names[node_type] << "    type: " << type_names[var_type] << "    val: " << num_str;
	}
	void setVarType(VarType t) override { var_type = t; }
	std::string	 getNodeStrVal() override { return ""; }
	void appendNumString(std::string s) override { num_str.append(s); }
};

class NodeVariable : public NodeData {
public:
	Variable var;
	NodeVariable(NodeType t, std::string n, VarType vt) : NodeData(t) {
		var.name = n;
		var.type = vt;
	}
	void print() override {
		std::cout << ast_type_names[node_type] << "    type: " << type_names[var.type] << "    name: " << var.name;
	}
	void setVarType(VarType t) override { var.type = t; }
	void setStrVal(std::string s) override { var.name = s; }
	std::string	 getNodeStrVal() override { return var.name; }
};

struct TreeNode {
	NodeData* node_data;
	std::vector<TreeNode*> children;
	TreeNode(NodeData* nd) : node_data(nd) {}
	~TreeNode() {
		delete node_data;
	}
};

class SyntaxTree {
private:
	TreeNode* root;
	std::vector<std::vector<Variable>> var_table;

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
		std::vector<Variable> first_table;
		var_table.push_back(first_table);
	}

	~SyntaxTree() {
		destroy(root);
	}

	TreeNode* insert(NodeData* value, TreeNode* parent = nullptr) {
		TreeNode* new_node = new TreeNode(value);
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

		for (int i = 0; i < depth - 1; i++) { std::cout << "    "; }
		if (depth > 0) { std::cout << "|___"; }

		node->node_data->print();
		std::cout << std::endl;

		for (TreeNode* child : node->children) { print(child, depth + 1); }
	}

	void print() { print(root); }

	TreeNode* getRoot() {
		return root;
	}

	// Looks up variables by name in a table
	Variable variableLookup(Variable var) {
		for (auto& tb : var_table) {
			for (Variable v : tb) {
				if (v.name == var.name) { return v; }
			}
			// Couldn't find in scope
		}
		// Add error message here instead
		return Variable("", VT_invalid);
	}

	void addDeclaration(TreeNode* node) {
		// TODO: add variable offset in stack
		NodeDeclaration* decl = dynamic_cast<NodeDeclaration*>(node->node_data);
		VarType decl_type = decl->var_type;
		for (TreeNode* child : node->children.at(0)->children) { //decl -> list_vars -> ...
			if (child->node_data->getNodeType() != AST_variable) { // This should only be full of AST_variable
				std::cout << "ERROR: trying to add variable but found node of type " << child->node_data->getNodeType() << std::endl;
			}
			std::cout << "Added " << child->node_data->getNodeStrVal() << "  " << type_names[decl_type] << std::endl;
			var_table.back().push_back(Variable(child->node_data->getNodeStrVal(), decl_type));
		}
	}
	void compileTreeMaster() {
		compileTree(root);
	}
	/*
	compiletree()
		if decl -> add to symbol table
		if stmt -> type check
		if func_decl -> add to symbol table (when to pop?)
		think about returning after doing an operation for some type of node
	*/
	// Returning from this function finishes compilation of a node and its children
	void compileTree(TreeNode* node) {
		if (node == nullptr) {
			return;
		}

		NodeType my_type = node->node_data->getNodeType();
		if (my_type == AST_func_declaration) {
			std::cout << "Ignoring function: " << node->node_data->getNodeStrVal() << std::endl;
			return; // skip functions for now
		}
		else if (my_type == AST_declaration) {
			// Add declaration variables to symbol table
			addDeclaration(node);
			return; // ?????
		}
		else if (my_type == AST_assignment) {
			std::cout << "-------- TYPE CHECK: --------" << std::endl;
			typeCheckNode(node);
			std::cout << "-------- ended check --------" << std::endl;
		}
		else if (my_type == AST_factor_var || my_type == AST_variable) {
			if (variableLookup(Variable(node->node_data->getNodeStrVal(), VT_default)).type == VT_invalid) {
				// BAD!!!!
				std::cout << "ERROR: Failed to find variable " << node->node_data->getNodeStrVal() << std::endl;
			}
			else {
				// good
				std::cout << "Good variable :)    " << node->node_data->getNodeStrVal() << std::endl;
			}
		}

		for (TreeNode* child : node->children) {
			compileTree(child);
		}
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
			else if (node->children.size() == 2) {
				VarType lhs = typeCheckExpression(node->children.at(0));
				VarType rhs = typeCheckExpression(node->children.at(1));
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

	VarType typeCheckNode(TreeNode* node) {
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
			typeCheckNode(child);
		}
		return lhs;
	}

	void printSymbolTable() {
		for (auto& tb : var_table) {
			for (Variable v : tb) {
				std::cout << v.name << "    " << type_names[v.type] << std::endl;
			}
			// Couldn't find in scope
		}
	}
};
