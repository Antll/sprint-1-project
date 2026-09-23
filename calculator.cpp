#include "calculator.h"

#include <iostream>
#include <vector>

bool CheckIsNumber(const std::string& str) {
	bool is_number = true;
	if (str.front() != '+' && str.front() != '-' 
			       && !std::isdigit(str.front())) {
		return false;
	}

	for (size_t i = 1; i < str.size(); ++i) {
		if (!std::isdigit(str[i])) {
			is_number = false;
			break;
		}
	}

	return is_number;
}

bool ReadNumber(Number& result) {
	std::string word;
	std::cin >> word;

	Number input = 0;
	if (!(CheckIsNumber(word))) {
		std::cerr << "Error: Numeric operand expected" << std::endl;
		return false;
	}

	result = ConvertToNumber(word);
	return true;
}

bool ProcessLastOperations(std::vector<Number>& values,
		           std::vector<std::string>& operations) {
	for (size_t i = 0, j = 1; i < operations.size(); ++i) {
		if (operations[i] == "+") {
			values[j - 1] += values[j];
			values.erase(values.begin() + j);
		} else if (operations[i] == "-") {
			values[j - 1] -= values[j];	
			values.erase(values.begin() + j);
		} else if (operations[i] == "=") {
			std::cout << values.front() << std::endl;	
		}
	}
	return false;
}

bool ProcessPreLastOperations(std::vector<Number>& values,
		              std::vector<std::string>& operations,
			      Number& cell,
			      bool& is_safed) {
	bool is_fail = false;
	for (size_t i = 0, j = 1; i < operations.size() && !is_fail; ++i) {
		if (operations[i] == "l") {
			is_fail = LoadCell(cell, is_safed, values[j - 1]);
		} else if (operations[i] == "s") {
			SaveCell(cell, values[j - 1], is_safed);	
		} else if (operations[i] == "+") {
			++j; // Skip
		} else if (operations[i] == "-") {
			++j; // Skip
		} else if (operations[i] == "*") {
			values[j - 1] *= values[j];	
			values.erase(values.begin() + j);
		}
	}

	return is_fail;
}

bool ParseOperationToken(std::vector<Number>& values,
		         std::vector<std::string>& operations,
			 const std::string& op) {
	bool is_failed = false;
	Number operand = 0;
	if (op == "l") {
		operations.push_back("l");
	} else if (op == "s") {
		operations.push_back("s");
	} else if (op == "+") {
		operations.push_back("+");
		is_failed = !ReadNumber(operand);
		values.push_back(operand);
	} else if (op == "-") {
		operations.push_back("-");
		is_failed = !ReadNumber(operand);
		values.push_back(operand);
	} else if (op == "*") {
		operations.push_back("*");	
		is_failed = !ReadNumber(operand);
		values.push_back(operand);
	} else if (op == "=") {
		operations.push_back("=");
	}

	return is_failed;
}

bool ParseTokens(std::vector<Number>& values,
		 std::vector<std::string>& operations) {
	bool is_failed = false;

	std::string op;
	bool is_exit = false;
	while (!is_exit) {
		std::cin >> op;	
		if (op == "q") {
			is_exit = true;	
		} else if (ParseOperationToken(values, operations, op)) {
			std::cerr << "Error: Unknown token "
				  << op << std::endl;
			is_exit = true;
			is_failed = true;
		}
	}

	return is_failed;
}

bool RunCalculatorCycle() {
	Number value = 0;
	Number cell = 0;
	bool is_safed = false;	

	std::vector<std::string> operations;
	std::vector<Number> values = {value};

	bool is_failed = !ReadNumber(values.back())
                        ||  ParseTokens(values, operations)
	                || ProcessPreLastOperations(values,operations, 
					                  cell, is_safed)
	                || ProcessLastOperations(values, operations);

	return is_failed;
}
			
bool LoadCell(Number& cell, bool is_safed, Number& dist) {
	bool is_failed = false;
	if (is_safed) {
		dist = cell;
	} else {
		std::cerr << "Error: Memory is empty" << std::endl;
		is_failed = true;
	}

	return is_failed;
}

void SaveCell(Number& cell, Number value, bool& is_safed) {
	is_safed = true;
	cell = value;
}

