#include "definitions.h"
#include "LLTable.cpp"
#include <iostream>
#include <string>
#include <fstream>


class Parser {
public:
	std::vector<Token> const* tokens;
	std::vector<Token> t_stack;
	
	LLTable table;
	Parser(std::vector<Token> const& token_list) {
		tokens = &token_list;
	}
	// TODO: fix grammar to include not
	int parse() {
		t_stack.push_back(Token(T_dollar, ""));
		t_stack.push_back(Token(G_PROGRAM, ""));

		std::ofstream error_file;
		error_file.open("Parsing-Errors.txt", std::ios::out | std::ios::trunc);

		// While we still have tokens left...
		// if current token matches top of stack -> pop 
		// else get the rule  from table[stack.top()][current_literal]
		// then pop the top non literal and replace it with the rule
		
		int it = 0;
		while (it < tokens->size()) {
			int top_type = t_stack.back().token_type;
			//std::cout << "Parsing\n";
			
			if ( top_type < NUM_TERMINALS || top_type == T_dollar )  { //top_type is nonterm or dollar
				if (top_type == tokens->at(it).token_type) {
					// Matched symbols
					t_stack.pop_back();
					it++;
				}
				else {
					// ERROR
					std::cout << "Error: expected: " << token_names[top_type] << "\t found: " << token_names[tokens->at(it).token_type] << std::endl;
					error_file << "Error: expected: " << token_names[top_type] << "\t found: " << token_names[tokens->at(it).token_type] << std::endl;
					// Handle errors by deleting
					t_stack.pop_back(); // ????
					it++; 
					//return -1;
				}

			}
			else {

				Rule cur = table.getRule( top_type - FIRST_NONLITERAL, tokens->at(it).token_type);
				t_stack.pop_back(); // I think every pop makes a node, with the rule that replaced it as the children
				addRule(cur); 
			}
			for (Token i : t_stack) {
				std::cout << token_names[i.token_type] << "  ";
			}
			if (it < tokens->size()) std::cout << "\t\t\t val: " << token_names[tokens->at(it).token_type] << std::endl;
			
		}
		std::cout << "Finished parsing successfully" << std::endl;
		return 0;
	}

	int addRule(Rule rule) {
		// Pushes the elements of a rule on the stack
		// if rule_size is 0 do nothing
		// i stops at 1 because 0 is the first rule 0 -> 1 2 3 ...
		// push in reverse order
		if (rule.size <= 1) {
			return 1;
		}
		for (int i = rule.size - 1; i >= 1; i--) {
			//std::cout << "i: " << i << std::endl;
			if (rule.data[i] == T_null) {
				//t_stack.pop_back(); unnecessary 
				//std::cout << "null" << std::endl;
				return 2;
			}
			Token nonlit(rule.data[i], "");
			t_stack.push_back(nonlit);	
		}
		//std::cout << std::endl;
		return 0;
	}
};
