#pragma once
#include <string>
#include <vector>
#include "errorSet.h"
class InstructionSet {
public:
	InstructionSet();
	InstructionSet(char newCode, int newError);
	InstructionSet(char newCode, int newError, std::vector<std::string> newSet);

	char instructionCode();
	int errorCode();
	std::vector<std::string>& parameterSet();
private:
	char _instructionCode;
	int _errorCode;
	std::vector<std::string> _parameterSet;
};