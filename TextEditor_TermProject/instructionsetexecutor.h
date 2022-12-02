#pragma once
#include <ctype.h>
#include "instructionset.h"
#include "letterpointer.h"
#include "trim.h"

class InstructionExecutor {
public:
	InstructionExecutor();
	std::vector<char>& modifiedStorage();
	int resultCode();
	std::string getResultMessage();
	void process_execute();
	void intructionExecutor_initialize(InstructionSet*, const std::vector<char>&, LetterPointer*);
private:
	
	InstructionSet* _targetInstructionSet;
	std::vector<char> _modifiedStorage;
	int _resultCode;
	char _givenInstructionCode;
	int _givenErrorCode;
	std::vector<std::string> _givenParameterSet;
	LetterPointer* _givenLetterPointer;

	void selectInstruction(int);
	void decodingInstructionSet();
	bool isStringValue(std::string);

	int searchingForTargetIndex(int, int );

	void execute_instruction_i(int, int, std::string);
	void execute_instruction_d(int ,int , int );
	void execute_instruction_s(std::string);
	void execute_instruction_c(std::string, std::string);
	void execute_instruction_t();
	void execute_instruction_p();
	void execute_instruction_n();

	bool process_instruction_i();
	bool process_instruction_d();
	bool process_instruction_s();
	bool process_instruction_c();
	bool process_instruction_t();
	bool process_instruction_p();
	bool process_instruction_n();



	void setGivenLetterPointer(LetterPointer*);
	LetterPointer* givenLetterPointer();
	int givenErrorCode();
	void setGivenInstructionCode(char);
	char givenInstructionCode();

	void setGivenErrorCode(int);
	

	void setGivenParameterSet(const std::vector<std::string>&);

	std::vector<std::string>& givenParameterSet();


	void setResultCode(int);

	void setTargetInstructionSet(InstructionSet*);
	InstructionSet* targetInstructionSet();

	void setStorage(const std::vector<char>&);
};