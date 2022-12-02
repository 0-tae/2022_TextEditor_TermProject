#include "instructionsetexecutor.h"
#include <iostream>

#pragma once
InstructionExecutor::InstructionExecutor() { this->setResultCode(ERROR_NONE); }


void InstructionExecutor::process_execute() {
	decodingInstructionSet(); // 인자로 받은 instructionSet을 분해하여 각 값을 저장한다.

	if (givenErrorCode() != ERROR_NONE) { // error_none이 아니라면, 올바르지 않은 명령어로 간주하고 종료한다.
		this->setResultCode(ERROR_102);
		return;
	}

	selectInstruction(givenInstructionCode()); // 올바른 명령어를 가지고 있다면 instruction을 수행한다.
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
				// startOfLetterLocation은 한 글자씩 진행할 때마다 증가한다.
				if (modifiedStorage().at(currentLetter) == '\n') break; // 개행문자를 만났다면 break
				if (currentLine == line && startOfLetterLocation + index == currentLetter) {
					// 현재 라인과 입력값 라인, 현재 글자와 탐색 시작점에서 입력값 만큼 떨어진 값과 일치한다면 해당 위치가 사용자가 입력한 위치이다.
					return currentLetter;
				}
			}
		}

		return ERROR_UNDEFINED; // 유효성 검사로 인해 찾을 수 없는 경우는 없으나, 만약 도달하게 된다면 설계상 오류로 간주한다.
	}

	bool InstructionExecutor::isStringValue(std::string givenString) {
		return (givenString.size() > 1 || givenString.at(0) != '0') && atoi(givenString.c_str()) == 0;
		// 문자의 길이가 1보다 크며, atoi값이 0이고 문자열의 첫 번째 글자가 숫자가 아닌경우
	}


	bool InstructionExecutor::process_instruction_i() {
		if (givenParameterSet().size() == 3) { // i 명령어의 인자는 3개여야 한다.
			std::string firstElement = trim(givenParameterSet().at(0));
			std::string secondElement = trim(givenParameterSet().at(1));
			std::string thirdElement = trim(givenParameterSet().at(2));
			
			
			if (isStringValue(firstElement)) {
				setResultCode(ERROR_103); // 잘못된 인자 입력
				return false;
			}
			else if (isStringValue(secondElement)) {
				setResultCode(ERROR_103); // 잘못된 인자 입력
				return false;
			}
			else if (thirdElement.size() > 100) {
				setResultCode(ERROR_101); // 문자열의 길이가 너무 클 경우
				return false;
			}

			int start = givenLetterPointer()->currentStartLocation(); // 현재 페이지의 시작점
			int end = givenLetterPointer()->currentEndLocation(); // 현재 페이지의 마지막 점
			int lineSize = ((start - end) / MAX_LENGTH_FOR_ONE_LINE) + 1; // 현재 line의 크기는 그 사이의 값에서 75를 나눈 값+1과 같다.

			int lineForinput = atoi(firstElement.c_str()); // 라인의 인덱스로 쓰일 값이다.
			int indexForinput = atoi(secondElement.c_str()); // 글자의 인덱스로 쓰일 값이다.
			std::string stringForinput = thirdElement.c_str(); // 삽입할 문자로 쓰일 값이다.

			if (lineSize < lineForinput && lineSize == 0) { // 가진 라인보다 입력한 라인이 더 크거나 0인경우
				setResultCode(ERROR_201); // 잘못된 인덱스 참조
				return false;
			}
			else if (indexForinput > MAX_LENGTH_FOR_ONE_LINE) { // 한 줄의 최대 길이보다 더 큰 값이 입력된 경우
				setResultCode(ERROR_201); // 잘못된 인덱스 참조
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
		if (givenParameterSet().size() == 3) { // 인자는 3개여야 한다.
			std::string firstElement = trim(givenParameterSet().at(0));
			std::string secondElement = trim(givenParameterSet().at(1));
			std::string thirdElement = trim(givenParameterSet().at(2));

			if (isStringValue(firstElement)) {
				setResultCode(ERROR_103); // 잘못된 인자 입력
				return false;
			}
			else if (isStringValue(secondElement)) {
				setResultCode(ERROR_103); // 잘못된 인자 입력
				return false;
			}
			else if (isStringValue(thirdElement)){
				setResultCode(ERROR_103); // 잘못된 인자 입력
				return false;
			}

			int start = givenLetterPointer()->currentStartLocation();
			int end = givenLetterPointer()->currentEndLocation();
			int lineSize = ((start - end) / MAX_LENGTH_FOR_ONE_LINE) + 1;

			int lineForinput = atoi(firstElement.c_str());
			int indexForinput = atoi(secondElement.c_str());
			int goalIndexForinput = atoi(thirdElement.c_str());

			if (lineSize < lineForinput && lineSize == 0) { // 가진 라인보다 입력한 라인이 더 크거나 0인경우
				setResultCode(ERROR_201); // 잘못된 인덱스 참조
				return false;
			}
			else if (indexForinput > MAX_LENGTH_FOR_ONE_LINE) { // 한 줄의 최대 길이보다 더 큰 값이 입력된 경우
				setResultCode(ERROR_201); // 잘못된 인덱스 참조
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
			setResultCode(ERROR_201); // 잘못된 인덱스 참조
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
		int pausePoint = -1; // 시작지점 판단
		
		if (savedEntireString.find(targetString) != std::string::npos) { // 부분 문자열을 찾았다면
			pausePoint = savedEntireString.find(targetString); // 부분문자열의 시작 지점 인덱스를 가져온다
			
			while (!givenLetterPointer()->returnStackisEmpty()) givenLetterPointer()->popPrevLocationFromReturnStack(); // 복귀 스택을 비운다.

			int count = pausePoint-1; // 현재 위치의 -1로부터 최소 pointer인 0까지 탐색을 진행한다.
			if(count==0) givenLetterPointer()->pushPrevLocationToReturnStack(count); // 0인 경우를 따로 처리한다.
			else {
				while (count > 0) {
					for (int line = MAX_LINE; line > 0 && count > 0; line--) { // 끝 인덱스에서 역으로 조사한다.
						for (int letter = MAX_LENGTH_FOR_ONE_LINE - 1; letter > -1 && count > 0; letter--) {
							if (modifiedStorage().at(count--) == '\n') break; // 개행문자를 만났다면 break
						}
					}
					givenLetterPointer()->pushPrevLocationToReturnStack(count); // 20라인을 거슬러 올라간 결과 1라인 0번째 인덱스 count가 return stack에 삽입된다.
				}
			}
			

			givenLetterPointer()->setLetterStartPointer(pausePoint); // 출력의 시작지점을 문자열의 시작 위치인 pausePoint로 설정
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
		std::string savedEntireString(modifiedStorage().begin(), modifiedStorage().end()); // 사본 vector의 값을 문자열로 모두 복사
		int pausePoint = -1; // 시작지점 판단
		int currentPoint = 0;
		
		while (savedEntireString.find(targetString,currentPoint) != std::string::npos) {
			pausePoint = savedEntireString.find(targetString, currentPoint); // 찾은 문자열의 시작 지점
			for (int i = 0; i < targetString.size(); i++) {
				modifiedStorage().erase(modifiedStorage().begin()+pausePoint); // 시작지점에서 찾은 문자열의 길이만큼 삭제
			}
			for (int i = 0; i < stringForSwap.size(); i++) {
				modifiedStorage().insert(modifiedStorage().begin() + pausePoint + i, stringForSwap.at(i)); // 대체할 문자열을 삽입
			}

			std::string modifiedString(modifiedStorage().begin(), modifiedStorage().end()); // 삭제 후 변경된 문자열을 다시 받음
			savedEntireString = modifiedString; // 현재 문자를 수정된 문자로 변경
			currentPoint = pausePoint+1; // 다음 인덱스부터 탐색
		}

		if(pausePoint==-1) {
			setResultCode(ERROR_303); // 해당하는 문자가 한 번도 없었다면 no search 에러
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
			if ((givenLetterPointer()->currentEndLocation() + 1) < modifiedStorage().size()) { // 현재 끝이 가리키는 곳이 파일의 끝보다 더 작다면
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
		givenLetterPointer()->pushPrevLocationToReturnStack(givenLetterPointer()->currentStartLocation()); // 현재 1라인 0번째 를 복귀 스택에 저장한다
		givenLetterPointer()->setLetterStartPointer(givenLetterPointer()->currentEndLocation() + 1); // 다음의 시작 지점을 끝 지점+1로 교체한다.
		int prevLetters = givenLetterPointer()->maxLocation() - givenLetterPointer()->currentStartLocation(); // 시작지점과 끝 지점의 차이를 계산한다.

		if (prevLetters / (MAX_LINE + 1) <MAX_LINE) { // 텍스트 에디터는 항상 20라인을 출력해야 하므로, 다음의 출력라인이 20라인보다 작다면
			givenLetterPointer()->setLetterStartPointer(givenLetterPointer()->peekPrevStartLocation()+prevLetters);
			// 다음의 시작 지점을현재 복귀주소에서 차이만큼 증가한 위치한 곳에서 시작하도록 한다.
		}
			
	}

	bool InstructionExecutor::process_instruction_p() {
		if (givenParameterSet().size() == 0) {

			if (!givenLetterPointer()->returnStackisEmpty()) { // 스택이 비어있다면 이전 페이지가 없다는 의미이다.
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
		givenLetterPointer()->setLetterStartPointer(givenLetterPointer()->popPrevLocationFromReturnStack()); // 리턴 스택에서 pop한 주소가 이전 페이지이다.
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