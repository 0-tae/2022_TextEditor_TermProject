#pragma once

#include <regex>
#include "instructionset.h"
#include "commandset.h"
#include "trim.h"

class InstructionSetBuilder {
public:
	InstructionSetBuilder();
	InstructionSet* createInstructionSet(std::string);
private:
	InstructionSet* commandBuilderValidation(std::string);

	int firstPass(char);
	bool secondPass(std::string);

	std::vector<std::string> split(std::string, std::string);
};