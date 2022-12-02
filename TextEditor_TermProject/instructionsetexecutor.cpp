#include "instructionsetexecutor.h"
#include <iostream>

#pragma once
InstructionExecutor::InstructionExecutor() { this->setResultCode(ERROR_NONE); }


void InstructionExecutor::process_execute() {
	decodingInstructionSet(); // ���ڷ� ���� instructionSet�� �����Ͽ� �� ���� �����Ѵ�.

	if (givenErrorCode() != ERROR_NONE) { // error_none�� �ƴ϶��, �ùٸ��� ���� ��ɾ�� �����ϰ� �����Ѵ�.
		this->setResultCode(ERROR_102);
		return;
	}

	selectInstruction(givenInstructionCode()); // �ùٸ� ��ɾ ������ �ִٸ� instruction�� �����Ѵ�.
}

	void InstructionExecutor::selectInstruction(int code) {
		switch (code) {
		case 'i':
			process_instruction_i();
			break;
		case 's':
			process_instruction_s();
			break;
		case 'c':
			process_instruction_c();
			break;
		case 'd':
			process_instruction_d();
			break;
		case 't':
			process_instruction_t();
			break;
		case 'n':
			process_instruction_n();
			break;
		case 'p':
			process_instruction_p();
			break;
		default:
			this->setResultCode(ERROR_102);
		}
	}



	void InstructionExecutor::intructionExecutor_initialize(InstructionSet* givenInstructionSet, const std::vector<char>& givenStorage,LetterPointer* givenLetterPointer) {
		setTargetInstructionSet(givenInstructionSet);
		setStorage(givenStorage);
		setGivenLetterPointer(givenLetterPointer);
		setResultCode(ERROR_NONE);
		decodingInstructionSet();
	}

	void InstructionExecutor::decodingInstructionSet() {
		setGivenInstructionCode(targetInstructionSet()->instructionCode());
		setGivenErrorCode(targetInstructionSet()->errorCode());
		setGivenParameterSet(targetInstructionSet()->parameterSet());
	}



	int InstructionExecutor::searchingForTargetIndex(int line, int index) {
		int start = givenLetterPointer()->currentStartLocation(); 
		int end = givenLetterPointer()->currentEndLocation();
		int lineSize = ((end - start) / MAX_LENGTH_FOR_ONE_LINE) + 1;

		for (int currentLine = 1; currentLine < lineSize + 1; currentLine++) {
			int startOfLetterLocation = start;
			for (int currentLetter = startOfLetterLocation; currentLetter < startOfLetterLocation + MAX_LENGTH_FOR_ONE_LINE; currentLetter = ++start) {
				// startOfLetterLocation�� �� ���ھ� ������ ������ �����Ѵ�.
				if (modifiedStorage().at(currentLetter) == '\n') break; // ���๮�ڸ� �����ٸ� break
				if (currentLine == line && startOfLetterLocation + index == currentLetter) {
					// ���� ���ΰ� �Է°� ����, ���� ���ڿ� Ž�� ���������� �Է°� ��ŭ ������ ���� ��ġ�Ѵٸ� �ش� ��ġ�� ����ڰ� �Է��� ��ġ�̴�.
					return currentLetter;
				}
			}
		}

		return ERROR_UNDEFINED; // ��ȿ�� �˻�� ���� ã�� �� ���� ���� ������, ���� �����ϰ� �ȴٸ� ����� ������ �����Ѵ�.
	}

	bool InstructionExecutor::isStringValue(std::string givenString) {
		return (givenString.size() > 1 || givenString.at(0) != '0') && atoi(givenString.c_str()) == 0;
		// ������ ���̰� 1���� ũ��, atoi���� 0�̰� ���ڿ��� ù ��° ���ڰ� ���ڰ� �ƴѰ��
	}


	bool InstructionExecutor::process_instruction_i() {
		if (givenParameterSet().size() == 3) { // i ��ɾ��� ���ڴ� 3������ �Ѵ�.
			std::string firstElement = trim(givenParameterSet().at(0));
			std::string secondElement = trim(givenParameterSet().at(1));
			std::string thirdElement = trim(givenParameterSet().at(2));
			
			
			if (isStringValue(firstElement)) {
				setResultCode(ERROR_103); // �߸��� ���� �Է�
				return false;
			}
			else if (isStringValue(secondElement)) {
				setResultCode(ERROR_103); // �߸��� ���� �Է�
				return false;
			}
			else if (thirdElement.size() > 100) {
				setResultCode(ERROR_101); // ���ڿ��� ���̰� �ʹ� Ŭ ���
				return false;
			}

			int start = givenLetterPointer()->currentStartLocation(); // ���� �������� ������
			int end = givenLetterPointer()->currentEndLocation(); // ���� �������� ������ ��
			int lineSize = ((start - end) / MAX_LENGTH_FOR_ONE_LINE) + 1; // ���� line�� ũ��� �� ������ ������ 75�� ���� ��+1�� ����.

			int lineForinput = atoi(firstElement.c_str()); // ������ �ε����� ���� ���̴�.
			int indexForinput = atoi(secondElement.c_str()); // ������ �ε����� ���� ���̴�.
			std::string stringForinput = thirdElement.c_str(); // ������ ���ڷ� ���� ���̴�.

			if (lineSize < lineForinput && lineSize == 0) { // ���� ���κ��� �Է��� ������ �� ũ�ų� 0�ΰ��
				setResultCode(ERROR_201); // �߸��� �ε��� ����
				return false;
			}
			else if (indexForinput > MAX_LENGTH_FOR_ONE_LINE) { // �� ���� �ִ� ���̺��� �� ū ���� �Էµ� ���
				setResultCode(ERROR_201); // �߸��� �ε��� ����
				return false;
			}
			execute_instruction_i(lineForinput, indexForinput, stringForinput);
		}
		else {
			setResultCode(ERROR_103);
			return false;
		}


		return true;
	}


	void InstructionExecutor::execute_instruction_i(int line, int index, std::string str) {
		int startPoint = searchingForTargetIndex(line, index);
		
		if (startPoint == ERROR_UNDEFINED) return;
		
		
		for (int i = 0; i < str.size(); i++)
			modifiedStorage().insert(modifiedStorage().begin() + startPoint + i, str.at(i));
	}


	bool InstructionExecutor::process_instruction_d() {
		if (givenParameterSet().size() == 3) { // ���ڴ� 3������ �Ѵ�.
			std::string firstElement = trim(givenParameterSet().at(0));
			std::string secondElement = trim(givenParameterSet().at(1));
			std::string thirdElement = trim(givenParameterSet().at(2));

			if (isStringValue(firstElement)) {
				setResultCode(ERROR_103); // �߸��� ���� �Է�
				return false;
			}
			else if (isStringValue(secondElement)) {
				setResultCode(ERROR_103); // �߸��� ���� �Է�
				return false;
			}
			else if (isStringValue(thirdElement)){
				setResultCode(ERROR_103); // �߸��� ���� �Է�
				return false;
			}

			int start = givenLetterPointer()->currentStartLocation();
			int end = givenLetterPointer()->currentEndLocation();
			int lineSize = ((start - end) / MAX_LENGTH_FOR_ONE_LINE) + 1;

			int lineForinput = atoi(firstElement.c_str());
			int indexForinput = atoi(secondElement.c_str());
			int goalIndexForinput = atoi(thirdElement.c_str());

			if (lineSize < lineForinput && lineSize == 0) { // ���� ���κ��� �Է��� ������ �� ũ�ų� 0�ΰ��
				setResultCode(ERROR_201); // �߸��� �ε��� ����
				return false;
			}
			else if (indexForinput > MAX_LENGTH_FOR_ONE_LINE) { // �� ���� �ִ� ���̺��� �� ū ���� �Էµ� ���
				setResultCode(ERROR_201); // �߸��� �ε��� ����
				return false;
			}

			execute_instruction_d(lineForinput, indexForinput, goalIndexForinput);
		}
		else {
			setResultCode(ERROR_103);
			return false;
		}


		return true;
	}
	void InstructionExecutor::execute_instruction_d(int line, int index, int goalIndex) {
		int startPoint = searchingForTargetIndex(line, index);

		if (startPoint == ERROR_UNDEFINED) {
			setResultCode(ERROR_UNDEFINED);
			return;
		}else if (goalIndex > givenLetterPointer()->currentEndLocation() - startPoint) {
			setResultCode(ERROR_201); // �߸��� �ε��� ����
			return;
		}


		for (int i = 0; i < goalIndex; i++)
			modifiedStorage().erase(modifiedStorage().begin() + startPoint);
		
	}

	bool InstructionExecutor::process_instruction_s() {
		if (givenParameterSet().size() == 1) {
			std::string givenString = trim(givenParameterSet().at(0));
			execute_instruction_s(givenString);
		}
		else {
			setResultCode(ERROR_103);
			return false;
		}

		return true;
	}
	void InstructionExecutor::execute_instruction_s(std::string targetString) {
		std::string savedEntireString(modifiedStorage().begin(), modifiedStorage().end());
		int pausePoint = -1; // �������� �Ǵ�
		
		if (savedEntireString.find(targetString) != std::string::npos) { // �κ� ���ڿ��� ã�Ҵٸ�
			pausePoint = savedEntireString.find(targetString); // �κй��ڿ��� ���� ���� �ε����� �����´�
			
			while (!givenLetterPointer()->returnStackisEmpty()) givenLetterPointer()->popPrevLocationFromReturnStack(); // ���� ������ ����.

			int count = pausePoint-1; // ���� ��ġ�� -1�κ��� �ּ� pointer�� 0���� Ž���� �����Ѵ�.
			if(count==0) givenLetterPointer()->pushPrevLocationToReturnStack(count); // 0�� ��츦 ���� ó���Ѵ�.
			else {
				while (count > 0) {
					for (int line = MAX_LINE; line > 0 && count > 0; line--) { // �� �ε������� ������ �����Ѵ�.
						for (int letter = MAX_LENGTH_FOR_ONE_LINE - 1; letter > -1 && count > 0; letter--) {
							if (modifiedStorage().at(count--) == '\n') break; // ���๮�ڸ� �����ٸ� break
						}
					}
					givenLetterPointer()->pushPrevLocationToReturnStack(count); // 20������ �Ž��� �ö� ��� 1���� 0��° �ε��� count�� return stack�� ���Եȴ�.
				}
			}
			

			givenLetterPointer()->setLetterStartPointer(pausePoint); // ����� ���������� ���ڿ��� ���� ��ġ�� pausePoint�� ����
		}
		else {
			setResultCode(ERROR_303);
			return;
		}
	}



	bool InstructionExecutor::process_instruction_c() {
		if (givenParameterSet().size() == 2) {
			std::string targetForinput = trim(givenParameterSet().at(0));
			std::string swapForinput = trim(givenParameterSet().at(1));
			execute_instruction_c(targetForinput, swapForinput);
		}
		else {
			setResultCode(ERROR_103);
			return false;
		}
		return true;
	}
	void InstructionExecutor::execute_instruction_c(std::string targetString, std::string stringForSwap) {
		std::string savedEntireString(modifiedStorage().begin(), modifiedStorage().end()); // �纻 vector�� ���� ���ڿ��� ��� ����
		int pausePoint = -1; // �������� �Ǵ�
		int currentPoint = 0;
		
		while (savedEntireString.find(targetString,currentPoint) != std::string::npos) {
			pausePoint = savedEntireString.find(targetString, currentPoint); // ã�� ���ڿ��� ���� ����
			for (int i = 0; i < targetString.size(); i++) {
				modifiedStorage().erase(modifiedStorage().begin()+pausePoint); // ������������ ã�� ���ڿ��� ���̸�ŭ ����
			}
			for (int i = 0; i < stringForSwap.size(); i++) {
				modifiedStorage().insert(modifiedStorage().begin() + pausePoint + i, stringForSwap.at(i)); // ��ü�� ���ڿ��� ����
			}

			std::string modifiedString(modifiedStorage().begin(), modifiedStorage().end()); // ���� �� ����� ���ڿ��� �ٽ� ����
			savedEntireString = modifiedString; // ���� ���ڸ� ������ ���ڷ� ����
			currentPoint = pausePoint+1; // ���� �ε������� Ž��
		}

		if(pausePoint==-1) {
			setResultCode(ERROR_303); // �ش��ϴ� ���ڰ� �� ���� �����ٸ� no search ����
			return;
		}
	}


	bool InstructionExecutor::process_instruction_t() {
		execute_instruction_t();
		return true;
	}
	void InstructionExecutor::execute_instruction_t() {
		setResultCode(ERROR_QUIT);
	}

	bool InstructionExecutor::process_instruction_n() {
		if (givenParameterSet().size() == 0) {
			if ((givenLetterPointer()->currentEndLocation() + 1) < modifiedStorage().size()) { // ���� ���� ����Ű�� ���� ������ ������ �� �۴ٸ�
				execute_instruction_n();
			} else {
				setResultCode(ERROR_302);
				return false;
			}
		}
		else {
			setResultCode(ERROR_UNDEFINED);
			return false;
		}
		return true;
	}
	void InstructionExecutor::execute_instruction_n() {
		givenLetterPointer()->pushPrevLocationToReturnStack(givenLetterPointer()->currentStartLocation()); // ���� 1���� 0��° �� ���� ���ÿ� �����Ѵ�
		givenLetterPointer()->setLetterStartPointer(givenLetterPointer()->currentEndLocation() + 1); // ������ ���� ������ �� ����+1�� ��ü�Ѵ�.
		int prevLetters = givenLetterPointer()->maxLocation() - givenLetterPointer()->currentStartLocation(); // ���������� �� ������ ���̸� ����Ѵ�.

		if (prevLetters / (MAX_LINE + 1) <MAX_LINE) { // �ؽ�Ʈ �����ʹ� �׻� 20������ ����ؾ� �ϹǷ�, ������ ��¶����� 20���κ��� �۴ٸ�
			givenLetterPointer()->setLetterStartPointer(givenLetterPointer()->peekPrevStartLocation()+prevLetters);
			// ������ ���� ���������� �����ּҿ��� ���̸�ŭ ������ ��ġ�� ������ �����ϵ��� �Ѵ�.
		}
			
	}

	bool InstructionExecutor::process_instruction_p() {
		if (givenParameterSet().size() == 0) {

			if (!givenLetterPointer()->returnStackisEmpty()) { // ������ ����ִٸ� ���� �������� ���ٴ� �ǹ��̴�.
				execute_instruction_p();
			}

			else {
				setResultCode(ERROR_301);
				return false;
			}
		}
		else {
			setResultCode(ERROR_UNDEFINED);
			return false;
		}
		return true;
	}
	void InstructionExecutor::execute_instruction_p() {
		givenLetterPointer()->setLetterStartPointer(givenLetterPointer()->popPrevLocationFromReturnStack()); // ���� ���ÿ��� pop�� �ּҰ� ���� �������̴�.
	}

	std::string InstructionExecutor::getResultMessage() {
		switch (this->resultCode()) {
			case ERROR_101:
				return "Parameter String is TOO LONG.";
			case ERROR_102:
				return "Your input is invalid instruction or Your input is WRONG.";
			case ERROR_103:
				return "Your input is valid instruction. but, parameter is incorrect.";
			case ERROR_201:
				return "Your instruction parameter representing index is Out-Of-Range.";
			case ERROR_301:
				return "This is the first page.";
			case ERROR_302:
				return "This is the last page.";
			case ERROR_303:
				return "NOT found 404..";
			case ERROR_UNDEFINED:
				return "Undefined Error";
			case ERROR_QUIT:
			case ERROR_NONE:
				return "";
		}
	}




	void InstructionExecutor::setGivenLetterPointer(LetterPointer* newPointer) {
		this->_givenLetterPointer = newPointer;
	}
	LetterPointer* InstructionExecutor::givenLetterPointer() {
		return this->_givenLetterPointer;
	}

	void InstructionExecutor::setGivenInstructionCode(char newCode) {
		this->_givenInstructionCode = newCode;
	}
	char InstructionExecutor::givenInstructionCode() {
		return this->_givenInstructionCode;
	}

	void InstructionExecutor::setGivenErrorCode(int newErrorCode) {
		this->_givenErrorCode = newErrorCode;
	}
	int InstructionExecutor::givenErrorCode() {
		return this->_givenErrorCode;
	}

	void InstructionExecutor::setGivenParameterSet(const std::vector<std::string>& newParameterSet) {
		this->_givenParameterSet = newParameterSet;
	}

	std::vector<std::string>& InstructionExecutor::givenParameterSet() {
		return this->_givenParameterSet;
	}


	void InstructionExecutor::setResultCode(int newCode) {
		this->_resultCode = newCode;
	}
	int InstructionExecutor::resultCode() {
		return this->_resultCode;
	}

	void InstructionExecutor::setTargetInstructionSet(InstructionSet* newInstructionSet) {
		this->_targetInstructionSet = newInstructionSet;
	}
	InstructionSet* InstructionExecutor::targetInstructionSet() {
		return this->_targetInstructionSet;
	}

	void InstructionExecutor::setStorage(const std::vector<char>& newStorage) {
		this->_modifiedStorage = newStorage;
	}

	std::vector<char>& InstructionExecutor::modifiedStorage() {
		return this->_modifiedStorage;
	}