#include "definitions.h"
#include <iostream>
#include <fstream>
#include "CodeGenerator.cpp"

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
	virtual void		setOpType(OpType t) {std::cout << "set op type called in wrong class" << std::endl;}
	virtual OpType		getOpType() { return OP_default; }
	virtual void		appendNumString(std::string s) {};
	
	virtual std::string	getNodeStrVal() {return "";};
	virtual VarType		getNodeVarType() {return VT_default;};
	void				setNodeType(NodeType n) { node_type = n; }
	NodeType			getNodeType() { return node_type; }
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
	VarType getNodeVarType() override { return function_type; }
};

class NodeExpression : public NodeData {
public:
	std::string str_val = "";
	OpType op_type = OP_single_factor;
	bool is_funcall = false; // If true, ignore operator
	NodeExpression(NodeType type) : NodeData(type) {}
	void print() override {
		if (!is_funcall) std::cout << ast_type_names[node_type] << "    op: " << operator_names[op_type];
		else if (is_funcall)  std::cout << ast_type_names[node_type] << "    name: " << str_val;
	}
	void setOpType(OpType t) override { op_type = t; }
	OpType getOpType() override { return op_type; }
	void setStrVal(std::string s) override { 
		str_val = s; 
		is_funcall = true;
	}
	std::string getNodeStrVal() override { return str_val;}

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
	VarType getNodeVarType() override { return var_type; }
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
	std::string	 getNodeStrVal() override { return num_str; }
	VarType getNodeVarType() override { return var_type; }
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
	VarType getNodeVarType() override {return var.type;}
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
	std::vector<Variable> functions_table; // Just use the Variable struct, all we need is name and type.
											// Implementation of function is just in assembly not here
	std::ofstream error_file;
	CodeGenerator* assembler;

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
	SyntaxTree(CodeGenerator* generator) : root(nullptr) {
		error_file.open("Semantic-Errors.txt", std::ios::out | std::ios::trunc);
		std::vector<Variable> first_table;
		var_table.push_back(first_table);
		assembler = generator;
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
	Variable variableLookup(std::string var_name) {
		for (auto& tb : var_table) {
			for (Variable v : tb) {
				if (v.name == var_name) { return v; }
			}
			// Couldn't find in scope
		}
		// Add error message here instead
		std::cout << "ERROR: Could not find variable " << var_name << std::endl;
		return Variable("", VT_invalid);
	}
	void addSingleDeclaration(TreeNode* node) {
		VarType my_vartype = node->node_data->getNodeVarType();
		int my_offset = (int)((var_table.back().size() + 1) * QWORD_SIZE);
		var_table.back().push_back(Variable(node->node_data->getNodeStrVal(), my_vartype, my_offset));

		assembler->makeDeclaration(my_offset);
	}
	void addDeclaration(TreeNode* node) {
		
		VarType decl_type = node->node_data->getNodeVarType();
		for (TreeNode* child : node->children[0]->children) { //decl -> list_vars -> ...
			if (child->node_data->getNodeType() != AST_variable) { // This should only be full of AST_variable
				std::cout << "ERROR: trying to add variable but found node of type " << child->node_data->getNodeType() << std::endl;
			}
			std::cout << "Added " << child->node_data->getNodeStrVal() << "  " << type_names[decl_type] << std::endl;
			int my_offset = (int)((var_table.back().size() + 1) * QWORD_SIZE);
			var_table.back().push_back(Variable(child->node_data->getNodeStrVal(), decl_type, my_offset));
			
			assembler->makeDeclaration(my_offset);
		}
	}
	void addFunctionToTable(TreeNode* node, int scope) {
		std::string f_name = node->node_data->getNodeStrVal();
		VarType     f_type = node->node_data->getNodeVarType();
		functions_table.push_back(Variable(f_name, f_type));
		std::cout << "Added function: " << type_names[f_type] << "    " << f_name << std::endl; 
	}
	
	int variableOffsetFromNode(TreeNode* node) {
		// TODO: add fail state
		Variable my_var = variableLookup(node->node_data->getNodeStrVal());
		if (my_var.type == VT_invalid) {
			std::cout << "ERROR: could not find variable " << node->node_data->getNodeStrVal() << std::endl;
		}
		return my_var.offset;
	}

	int constIntValueFromNode(TreeNode* node) {
		return std::stoi(node->node_data->getNodeStrVal());
	}

	void compileFactorToRegister(TreeNode* node, std::string reg) {
		if (node->node_data->getNodeType() == AST_factor_var) {
			int my_offset = variableOffsetFromNode(node);
			assembler->makeMoveVariableToReg(my_offset, reg);
		}
		else if (node->node_data->getNodeType() == AST_factor_const) {
			int my_value = constIntValueFromNode(node);
			assembler->makeMoveConstIntToReg(my_value, reg);
		}
		else if (node->node_data->getNodeType() == AST_factor_call) {
			std::cout << "Function calls not implemented yet" << std::endl;
		}
	}
	// TODO: make this smaller 
	void compileOperationOnRegisters(std::string reg_1, std::string reg_2, OpType operation) {
		if (operation == OP_not) {
			assembler->notRegister(reg_1);
		}
		if (operation == OP_or) {
			assembler->orRegisters(reg_1, reg_2);
		}
		if (operation == OP_and) {
			assembler->andRegisters(reg_1, reg_2);
		}
		else if (operation == OP_equals) {
			assembler->equalsRegisters(reg_1, reg_2);
		}
		else if (operation == OP_unequals) {
			assembler->unequalsRegisters(reg_1, reg_2);
		}
		else if (operation == OP_greater_eq) {
			assembler->greaterEqualsRegisters(reg_1, reg_2);
		}
		else if (operation == OP_lesser_eq) {
			assembler->lesserEqualsRegisters(reg_1, reg_2);
		}
		else if (operation == OP_greater) {
			assembler->greaterRegisters(reg_1, reg_2);
		}
		else if (operation == OP_lesser) {
			assembler->lesserRegisters(reg_1, reg_2);
		}
		else if (operation == OP_plus) {
			assembler->addRegisters(reg_1, reg_2);
		}
		else if (operation == OP_minus) {
			assembler->subRegisters(reg_1, reg_2);
		}
		else if (operation == OP_times) {
			assembler->imulRegisters(reg_1, reg_2);
		}
		else if (operation == OP_divide) {
			assembler->idivRegisters(reg_1, reg_2);
		}
	}

	int operatorPriority(OpType operation) {
		if (operation == OP_single_factor) {
			return 1;
		}
		else if (operation == OP_equals) {
			return 50;
		}
		else if (operation == OP_unequals) {
			return 50;
		}
		else if (operation == OP_greater_eq) {
			return 50;
		}
		else if (operation == OP_lesser_eq) {
			return 50;
		}
		else if (operation == OP_greater) {
			return 50;
		}
		else if (operation == OP_lesser) {
			return 50;
		}
		else if (operation == OP_not) {
			return 50; // TODO: not should have the lowest priority possible?
		}
		else if (operation == OP_or) {
			return 50;
		}
		else if (operation == OP_and) {
			return 75;
		}
		else if (operation == OP_plus) {
			return 50;
		}
		else if (operation == OP_minus) {
			return 50;
		}
		else if (operation == OP_times) {
			return 75;
		}
		else if (operation == OP_divide) {
			return 75;
		}
		return -999;
	}

	TreeNode* compileExpression(TreeNode* node, bool is_subexpr) {
		OpType my_optype = node->node_data->getOpType();
		int my_priority = operatorPriority(my_optype);
		if (my_optype == OP_default) {
			std::cout << "ERROR: did not expect to get OP_default from node" << std::endl;
		}
		else if (my_optype == OP_single_factor) {
			if (!is_subexpr) compileFactorToRegister(node->children[0], "rax");
		}
		else if (my_optype == OP_not) {
			compileFactorToRegister(node->children[0]->children[0], "rax");
			compileOperationOnRegisters("rax", "rbx", my_optype);
			if (node->children[0]->node_data->getOpType() != OP_single_factor) {
				compileExpression(node->children[0], true);
			}
			else {
				return nullptr;
			}
		}
		else { 

			if (node->children.size() < 2) {
				std::cout << "ERROR: expression should have two child nodes" << std::endl;
				return nullptr;
			}
			// TODO: add support for expressions in left side
			if (!is_subexpr) {
				compileFactorToRegister(node->children[0], "rax"); // TODO: compile expression on left side of tree
			}

			// Check priority of right child
			int right_child_priority = operatorPriority(node->children[1]->node_data->getOpType());
			std::cout << "Priority: " << my_priority << "    Right child:" << right_child_priority << std::endl;
			if (right_child_priority > my_priority) { 
				// if next node has higher priority, call expr() recursively then [add first, second]
				//////assembler->moveRegisters("r14", "rax");
				assembler->pushRegister("rax");
				// TODO: need to move temporaries to stack ------------------------------------
				TreeNode* continue_node = compileExpression(node->children[1], false);
				assembler->popToRegister("r14");
				compileOperationOnRegisters("r14", "rax", my_optype);
				assembler->moveRegisters("rax", "r14"); 
				
				if (continue_node != nullptr) {
					std::cout << "continue " << std::endl;
					if (continue_node->node_data->getOpType() != OP_single_factor) compileExpression(continue_node, true);
				}
				return nullptr;
			}
			else if (right_child_priority == my_priority) {
				// first do [add rax, first_of_child], then call expr()
				compileFactorToRegister(node->children[1]->children[0], "rbx"); // Move first of (right) child to rbx 
				compileOperationOnRegisters("rax", "rbx", my_optype);
				if(node->children[1]->node_data->getNodeType() != OP_single_factor) {
					TreeNode* continue_node = compileExpression(node->children[1], true);
					return continue_node;
				}
				else {
					return nullptr;
				}
			}
			else if (right_child_priority < my_priority) {
				// return right child as node to continue
				compileFactorToRegister(node->children[1]->children[0], "rbx"); // Move first of (right) child to rbx 
				compileOperationOnRegisters("rax", "rbx", my_optype);
				if (is_subexpr) {
					return node->children[1];
				}
				else {
					TreeNode* continue_node = compileExpression(node->children[1], true);
					return continue_node;
				}
				// STILL need to use second value not first
			}
		}
		// The idea: if the subexpression op_type has a higher priority, call expr() recursively first then [add first, second]
		//                  if the next one is the same priority, continue as normal
		//                  if the next one is of LOWER priority, return that node to continue from
		//                                (then use whats in rax already, not the left child)
		//                  otherwise, we do [add first, second] first then call expr() recursively
		//
		//                  it needs to return a node that we will continue from...
		return nullptr; // Temporary?

	}
	void compileTreeMaster() {
		assembler->initAssembly();
		//assembler->testIntPrint();
		std::vector<Variable> first_table;
		var_table.push_back(first_table);
		compileTree(root);
		assembler->finalizeAssembly();
	}


	// Returning from this function finishes compilation of a node and its children
	void compileTree(TreeNode* node) {
		if (node == nullptr) {
			return;
		}

		NodeType my_type = node->node_data->getNodeType();
		if (my_type == AST_list_func_declarations) {
			// Compile all functions
			for (TreeNode* function : node->children) {
				// note: need to keep rax in some temporary place
				addFunctionToTable(node, 0);
				assembler->functionStart(function->node_data->getNodeStrVal());

				std::vector<Variable> second_table;
				var_table.push_back(second_table);

				int end_of_parameters = (int)function->children.size();

				for (int i = (int)function->children.size() - 1; i >= 0; i--) {
					if (function->children[i]->node_data->getNodeType() == AST_parameter) {
						std::cout << "Found parameter " << function->children[i]->node_data->getNodeStrVal() << std::endl;
						addSingleDeclaration(function->children[i]);
					}
					else {
						end_of_parameters--;
					}
				}

				// Handle list declarations
				std::cout << "Thing after last parameter: " << ast_type_names[function->children[end_of_parameters]->node_data->getNodeType()] << std::endl;
				if (end_of_parameters >= function->children.size()) {
					std::cout << "ERROR: function is missing declaration sequence or statement sequence" << std::endl;
					return;
				}
				compileTree(function->children[end_of_parameters]);
				compileTree(function->children[end_of_parameters + 1]);
				// Hande list statements
				assembler->functionEnd();
				var_table.pop_back();
			}
			assembler->startMainAssembly();
			return; 
		}
		else if (my_type == AST_declaration) {
			addDeclaration(node);
			return;
		}
		else if (my_type == AST_assignment) {
			std::cout << "-------- TYPE CHECK: --------" << std::endl;
			typeCheckNode(node);
			std::cout << "-------- ended check --------" << std::endl;


			std::string my_var_name = node->children[0]->node_data->getNodeStrVal();
			Variable my_var = variableLookup(my_var_name);
			int my_offset = my_var.offset; 

			if(node->children.size() > 1)  compileExpression(node->children[1], false);

			assembler->makeAssignment(my_offset); // right now nothing is pushed to stack so cant print
			return;
		}
		else if (my_type == AST_while) {
			assembler->makeWhileStart();
			compileExpression(node->children[0], false);
			assembler->makeWhileMiddle("rax");
			if (node->children.size() > 1) compileTree(node->children[1]);
			assembler->makeWhileEnd();
			return;
		}
		else if (my_type == AST_print) {
			if (node->children.size() >= 1) {
				compileExpression(node->children[0], false);
				assembler->makePrintInt();
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
			VarType var_type = node->node_data->getNodeVarType();
			std::cout << "Found factor const type: " << type_names[var_type] << std::endl;
			return var_type;
		}
		else if (my_type == AST_factor_var) {
			std::string node_var_name = node->node_data->getNodeStrVal();
			// Find symbol in symbol table
			Variable looked_up = variableLookup(node_var_name);
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

			lhs = variableLookup(tempVar->var.name).type;
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
				std::cout << v.name << "    " << type_names[v.type] << v.offset << std::endl;
			}
			// Couldn't find in scope
		}
		std::cout << std::endl;
	}
	void printFunctionTable() {
		for (Variable f : functions_table) {
			std::cout << f.name << "    " << type_names[f.type] << std::endl;
		}
		std::cout << std::endl;
	}
};
