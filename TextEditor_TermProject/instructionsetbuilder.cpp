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
		if (typeOfcmd == TYPE_HAS_PARAMETER) { // 1. �ùٸ� Ŀ�ǵ����� Ȯ���Ѵ�.
			if (secondPass(givenCommand)) { // 2. ���Խ��� �����ϴ��� Ȯ���Ѵ�.
					vector<std::string> splitedCommand = split(givenCommand, R"(\(|\)|,)"); // �ش� ���Խ��� �������� ���ڸ� ���ڿ��� �����Ͽ� vector�� �����Ѵ�.
					splitedCommand.erase(splitedCommand.begin()); // ���Ұ��, ù ��° ��Ҵ� ���ڰ� �ƴ� ��ɾ(char) �� �����Ƿ� �����Ѵ�.
				if (splitedCommand.size()>0 && splitedCommand.size()<=3) { // 3. �Ķ������ ���ڴ� 3�� ���� 1�� �̻��̴�.
					return new InstructionSet(givenCommand[0], ERROR_NONE, splitedCommand); // ��ɾ�� �ڵ�, ���ҵ� ��ɾ� vector�� �����Ͽ� �����Ѵ�.
				}
			}
		}

		else if (typeOfcmd == TYPE_NONE_PARAMETER) {// 1. �ùٸ� Ŀ�ǵ����� Ȯ���Ѵ�.
			if(strlen(givenCommand.c_str())==1) // 2. �Ķ���Ͱ� �����Ƿ� ��ɾ��� ���̰� 1���� Ŭ �� ����.
				return new InstructionSet(givenCommand[0], ERROR_NONE);// ��ɾ�� �ڵ�� �����Ͽ� �����Ѵ�.
		}
		
		return new InstructionSet('?', ERROR_102);	// ���� �� ��츦 ������ �Է��� �߸��� �Է����� �Ǵ��Ͽ� ���� instructionset�� �����Ѵ�.
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
