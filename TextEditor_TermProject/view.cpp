#include "view.h"


using namespace std;
    void View:: print_IndexOfLine(int idx) {
		printf("%2d",idx);
		print("| ");
	}
	void View::print_LineOfUnderBar() {
		printLine("-------------------------------------------------------------------------------");
	}
	void View:: print_GuideOfCommand() {
		print("n:����������, ");
		print("p:����������, ");
		print("i:����, ");
		print("d:����, ");
		print("c:����, ");
		print("s:ã��, ");
		print("t:����������");
		printLine("");
	}
	void View::print_ErrorMessage(int givenErrorCode) {
		print_Prompt_ConsoleMessage();
		// �����ڵ忡 ����� �޽��� ���
	}


	void View:: print_Prompt_ConsoleMessage() {
		print("(�ָܼ޽���) ");
	}
	void View::print_Prompt_InputMessage() {
		print("�Է�: ");
	}

	
	void View::printLine(int str) {
		cout << str << endl;
	}
	void View::printLine(std::string str) {
		cout << str << endl;
	}
	void View::printLine(char str) {
		cout << str << endl;
	}

	void View::print(int str) {
		cout << str;
	}

	void View::print(char str) {
		cout << str;
	}
	void View::print(std::string str) {
		cout << str;
	}

	string View::input_Command() {
		std::string buffer = "";
		buffer.reserve(1500);
		getline(cin, buffer);
		return buffer;
	}
