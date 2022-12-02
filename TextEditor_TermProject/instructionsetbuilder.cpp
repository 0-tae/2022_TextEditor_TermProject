#include "instructionsetbuilder.h"
#include <regex>
#include <iostream>
#include <vector>

using namespace std;

	InstructionSetBuilder :: InstructionSetBuilder() {}
	InstructionSet* InstructionSetBuilder:: createInstructionSet(std::string givenCommand) {
		InstructionSet* givenInstructionSet = commandBuilderValidation(trim(givenCommand));
		return givenInstructionSet;
	}

	InstructionSet* InstructionSetBuilder::commandBuilderValidation(std::string givenCommand) {
		int typeOfcmd = firstPass(givenCommand[0]);
		if (typeOfcmd == TYPE_HAS_PARAMETER) { // 1. 올바른 커맨드인지 확인한다.
			if (secondPass(givenCommand)) { // 2. 정규식을 만족하는지 확인한다.
					vector<std::string> splitedCommand = split(givenCommand, R"(\(|\)|,)"); // 해당 정규식을 기준으로 인자를 문자열로 분할하여 vector에 저장한다.
					splitedCommand.erase(splitedCommand.begin()); // 분할결과, 첫 번째 요소는 인자가 아닌 명령어가(char) 들어가 있으므로 제거한다.
				if (splitedCommand.size()>0 && splitedCommand.size()<=3) { // 3. 파라미터의 인자는 3개 이하 1개 이상이다.
					return new InstructionSet(givenCommand[0], ERROR_NONE, splitedCommand); // 명령어와 코드, 분할된 명령어 vector로 구성하여 생성한다.
				}
			}
		}

		else if (typeOfcmd == TYPE_NONE_PARAMETER) {// 1. 올바른 커맨드인지 확인한다.
			if(strlen(givenCommand.c_str())==1) // 2. 파라미터가 없으므로 명령어의 길이가 1보다 클 수 없다.
				return new InstructionSet(givenCommand[0], ERROR_NONE);// 명령어와 코드로 구성하여 생성한다.
		}
		
		return new InstructionSet('?', ERROR_102);	// 위의 두 경우를 제외한 입력은 잘못된 입력으로 판단하여 오류 instructionset을 생성한다.
	}

	int InstructionSetBuilder:: firstPass(char givencmdchar) {
		switch (givencmdchar) {
		case 'i':
		case 's':
		case 'c':
		case 'd':
			return TYPE_HAS_PARAMETER;
		case 't':
		case 'n':
		case 'p':
			return TYPE_NONE_PARAMETER;
		}
		return TYPE_NOT_FOUND;
	}

	bool InstructionSetBuilder::secondPass(std::string target) {
		std::regex passElement(R"(([a-z])\(([^)]+)\))");
		return std::regex_match(target, passElement);
	}

	vector<std::string> InstructionSetBuilder:: split(std::string s, std::string pattern) {
		regex re(pattern);
		std::sregex_token_iterator iterator(s.begin(), s.end(), re, -1), end;
		return vector<std::string>(iterator, end);
	}
