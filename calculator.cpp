#include "calculator.h"

#include <iostream>

bool CheckIsNumber(const std::string& str) {
	bool is_number = true;
	if (str.front() != '+' && str.front() != '-' && !std::isdigit(str.front())) {
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

bool RunCalculatorCycle() {
	Number value = 0;
	if (!ReadNumber(value)) {
		return false;
	}

	std::string op;
	Number cell = 0;
	bool is_safed = false;
	bool is_exit = false;
	while (!is_exit) {
		std::cin >> op;
		if (op == "l") {
			is_exit = LoadCell(cell, is_safed, value);
		} else if (op == "s") {
			SaveCell(cell, value, is_safed);	
		} else if (op == "=") {
			std::cout << value << std::endl;	
		} else if (op == "q") {
			is_exit = true;	
		} else {
			std::cerr << "Error: Unknown token "
				  << op << std::endl;
			is_exit = true;
		}
	}

	return true;
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
