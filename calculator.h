#pragma once

#include <string>

using Number = double;

inline double ConvertToNumber(const std::string& line) {
	return std::stod(line);
}

bool ReadNumber(Number& result);

bool RunCalculatorCycle();
			
bool LoadCell(Number& cell, bool is_safed, Number& dist);
			
void SaveCell(Number& cell, Number value, bool& is_safed);
			
bool Sum(Number& value);
