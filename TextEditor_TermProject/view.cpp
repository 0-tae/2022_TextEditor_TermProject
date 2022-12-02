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
		print("n:다음페이지, ");
		print("p:이전페이지, ");
		print("i:삽입, ");
		print("d:삭제, ");
		print("c:변경, ");
		print("s:찾기, ");
		print("t:저장후종료");
		printLine("");
	}
	void View::print_ErrorMessage(int givenErrorCode) {
		print_Prompt_ConsoleMessage();
		// 에러코드에 기반한 메시지 출력
	}


	void View:: print_Prompt_ConsoleMessage() {
		print("(콘솔메시지) ");
	}
	void View::print_Prompt_InputMessage() {
		print("입력: ");
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
