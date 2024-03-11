#include "definitions.h"
#include <fstream>
#include <iostream>
#include <sstream>


class LLTable {
public:
	// TODO: make file reader that takes all this info from a file
	LLTable() {
		read_rules("src/grammar.txt");
		read_table("src/table.txt");
	}
	// First int in rule is the left hand side
	Rule r_blank[1] = { 0 };

	Rule rules[NUM_RULES];
	Rule *table[NUM_NONTERIMNALS][34];

	void read_rules(std::string in_file_name) {
		std::ifstream in_file(in_file_name);
		std::string line;
		int rule_count = 0;
		if (in_file.is_open()) {
			while (std::getline(in_file, line)) {
				// Get a rule from row
				int sym_count = 0;
				Rule rule{};
				std::istringstream line_stream(line);
				auto token = std::string{};
				std::cout << rule_count + 1 << " ";
				while (line_stream >> token) {
					// Find enum for rule
					std::cout << token << " ";
					for (int i = 0; i < ARR_SIZE(token_names); i++) {
						if (token_names[i] == token) {
							rule.data[sym_count] = i;
						}
					}
					sym_count++;
				}
				std::cout << std::endl;
				rule.size = sym_count;
				
				rules[rule_count] = rule;
				rule_count++;
			}
			in_file.close();	
		}
		else {
			std::cout << "failed to open file\n";
		}
		
		/*for (Rule x : rules) {
			std::cout << x.size << " ";
		}
		std::cout << std::endl;*/
	}
	void read_table(std::string in_file_name) {
		std::ifstream in_file(in_file_name);
		std::string line;
		int row_count = 0;
		if (in_file.is_open()) {
			while (std::getline(in_file, line)) {
				// Get a rule from row
				std::istringstream line_stream(line);
				auto token = std::string{};
				//std::cout << line << "\n";
				int col_count = 0;
				while (line_stream >> token) {
					// Token
					int value = std::stoi(token);
					if (value == 0) {
						table[row_count][col_count] = r_blank;
					}
					else {
						table[row_count][col_count] = &rules[value - 1];
					}
					std::cout << value << " ";
					col_count++;
				}
				row_count++;
				std::cout << std::endl;
			}
			in_file.close();
		}
		else {
			std::cout << "failed to open file\n";
		}
	}
	Rule getRule(int i, int j) {
		Rule rule = *table[i][j];
		return rule;
	}
};
