#include "instructionset.h"

	InstructionSet:: InstructionSet() {
		this->_instructionCode = '?';
		this->_errorCode = ERROR_102;
	}
	InstructionSet:: InstructionSet(char newCode, int newError) {
		this->_instructionCode = newCode;
		this->_errorCode = newError;
		this->_parameterSet = std::vector<std::string>(0);
	}
	InstructionSet:: InstructionSet(char newCode, int newError, std::vector<std::string> newSet) {
		this->_instructionCode = newCode;
		this->_errorCode = newError;
		this->_parameterSet.swap(newSet);
	}

	char InstructionSet::instructionCode() {
		return this->_instructionCode;
	}
	int InstructionSet::errorCode() {
		return this->_errorCode;
	}
	std::vector<std::string>& InstructionSet::parameterSet() {
		return this->_parameterSet;
	}