#include "calculator.h"

#include <iostream>
#include <vector>
#include <cmath>

bool CheckIsNumber(const std::string& str) {
	bool is_number = true;
	if (str.front() != '+' && str.front() != '-' 
			       && !std::isdigit(str.front())) {
		return false;
	}

	if ((str.front() == '+' || str.front() == '-') && str.size() < 2) {
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

// True if op1 >= op2
bool NotLowerPriority(const std::string& op1,
		      const std::string& op2) {
	bool is_op1_ge = false; // greate or equal
	if (op1 == "**") {
		is_op1_ge = true;	
	} else if (op1 == "*" || op1 == "/") {
		if (op2 == "+" || op2 == "-" || op2 == "*" || op2 == "/"
		   || op2 == "l" || op2 == "s" || op2 == "=") {
			is_op1_ge = true;	
		} 
	} else if (op1 == "+" || op1 == "-") {
		if (op2 == "+" || op2 == "-" || op2 == "=" || op2 == ":"
		    || op2 == "s" || op2 == "l") {
			is_op1_ge = true;	
		}	
	} else if (op1 == "=" || op1 == ":" || op1 == "s" || op1 == "l") {
		is_op1_ge = true;	
	}

	return is_op1_ge;
}

bool CheckIfAdditiveOperation(const std::string& op) {
	return ((op == "+") || (op == "-")) ? true : false;
}

bool CheckIfCummulativeOperation(const std::string& op) {
	return ((op == "*") || (op == "/") || (op == "**")) ? true : false;
}

bool CheckIfAccumulatorOperation(const std::string& op) {
	return ((op == "=") || (op == ":")) ? true : false;
}

bool CheckIfCellOperatoin(const std::string& op) {
	return ((op == "s") || (op == "l")) ? true : false;
}

bool EvaluateAdditiveOperation(const std::string& op, 
		               Number& left, Number& right) {
	bool is_fail = false;
	if (op == "+") {
		left += right;	
	} else if (op == "-") {
		left -= right;	
	} else {
		is_fail = false;
	}

	return is_fail;
}

bool EvaluateCummulativeOperation(const std::string& op,
		                  Number& left, Number& right) {
	bool is_fail = false;
	if (op == "*") {
		left *= right;	
	} else if (op == "/") {
		left /= right;	
	} else if (op == "**") {
		left = std::pow(left, right);	
	} else {
		is_fail = true;
	}

	return is_fail;
}

bool EvaluateAccumulatorOperation(const std::string& op,
	  	                  Number left) {
	bool is_fail = false;
	if (op == "=") {
		std::cout << left << std::endl;	
	} else {
		is_fail = true;	
	}

	return is_fail;
}

bool EvaluateAccumulatorOperation(const std::string& op,
	  	                  Number& left, Number right) {
	bool is_fail = false;
	if (op == ":") {
		left = right;	
	} else {
		is_fail = true;
	}

	return is_fail;
}

bool EvaluateCellOperatoin(const std::string& op, 
		           Number& cell, Number& value, 
			   Number& cell_dist, bool& is_safed) {
	bool is_fail = false;
	if (op == "s") {
		SaveCell(cell, value, is_safed);	
	} else if (op == "l") {
		LoadCell(cell, is_safed, cell_dist);	
	} else {
		is_fail = true;
	}

	return is_fail;
}

bool EvaluateOperation(const std::string& op, Number& left, Number& right,
		       Number& cell, Number& cell_dist, bool& is_safed) {
	bool is_fail = false;
	if ((op == "+") || (op == "-")) {
		is_fail = EvaluateAdditiveOperation(op, left, right);	
	} else if ((op == "*") || (op == "/") || (op == "**")) {
		is_fail = EvaluateCummulativeOperation(op, left, right);	
	} else if (op == ":") {
		is_fail = EvaluateAccumulatorOperation(op, left, right);	
	} else if (op == "=") {
		is_fail = EvaluateAccumulatorOperation(op, left);	
	} else if (op == "s" || op == "l") {
		is_fail = EvaluateCellOperatoin(op, cell, left, 
				                cell_dist, is_safed);	
	} else {
		is_fail = true;
	}

	return is_fail;
}

bool EraseUsedOperand(std::vector<Number>& values,
		      const std::string& op, size_t pos) {
	bool is_fail = false;
	if (values.empty() || pos > values.size() - 1) {
		return true;	
	}

	if (CheckIfAdditiveOperation(op) || CheckIfCummulativeOperation(op)
	    || op == ":") {
		values.erase(values.begin() + pos);	
	}

	return is_fail;
}

bool EraseEvaluatedOperation(std::vector<std::string>& operations, 
		             size_t pos) {
	bool is_fail = false;
	if (operations.empty() || pos > operations.size() - 1) {
		return true;	
	}

	operations.erase(operations.begin() + pos);

	return is_fail;
}

bool ProcessOperations(std::vector<Number>& values,
		       std::vector<std::string>& operations,
		       Number& cell,
		       bool& is_safed) {
	bool is_failed = false;
	int i = 0; // operations
	int j = (values.size() > 1) ? 1 : 0; // values
	while (!operations.empty() && !is_failed) {
		if (operations.size() == 1 
		    || NotLowerPriority(operations[i], operations[i + 1])) {
			Number& left = values.size() > 1 ? values[j - 1]
				                         : values[j];
			is_failed = EvaluateOperation(operations[i], 
			         	              left, 
					              values[j], cell, 
						      left, 
						      is_safed)	
			           || EraseUsedOperand(values, 
				   	               operations[i], j)
			           || EraseEvaluatedOperation(operations, i);
			i = 0;
			j = (values.size() > 1) ? 1 : 0;
		} else {
			++i;
			++j;
		}
	}

	return is_failed;
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
	} else if (op == "/") {
		operations.push_back("/");	
		is_failed = !ReadNumber(operand);
		values.push_back(operand);
	} else if (op == "**") {
		operations.push_back("**");	
		is_failed = !ReadNumber(operand);
		values.push_back(operand);
	} else if (op == "=") {
		operations.push_back("=");
	} else {
		std::cerr << "Error: Unknown token "
		          << op << std::endl;
		is_failed = true;
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
                        || ParseTokens(values, operations)
			|| ProcessOperations(values, operations,
					     cell, is_safed);

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

