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
	std::cout << value << std::endl;

	return true;
}
