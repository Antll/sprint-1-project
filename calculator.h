#pragma once

#include <string>

using Number = double;

inline double ConvertToNumber(const std::string& line) {
	return std::stod(line);
}

bool ReadNumber(Number& result);

bool RunCalculatorCycle();
