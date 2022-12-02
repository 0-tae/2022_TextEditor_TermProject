
#include <iostream>
#include "textEditor.h"

#define MAX_LINE 20
#define MAX_LENGTH_FOR_ONE_LINE 75


	void TextEditor::run() {
		std::string inputCommand;
		textEditor_initialize(); // 초기화
		do {
			settingMainPage(); // 출력 화면 구성
			inputCommand = View::input_Command(); // 입력받기
			View::print_LineOfUnderBar(); // - 라인 출력
			InstructionSet* instruction = parseLine(inputCommand.c_str()); // 입력값 분석
			instructionExecute(instruction); // 입력값 실행
			if (quit()) { // 명령어 't'일경우 저장 후 종료
				fileManager()->close_File(); // file을 닫는다.
				fileManager()->open_FileOnlyWrite(); // 쓰기 전용으로 연다.
				fileManager()->write_All(); // 파일 스토리지의 모든 값을 파일에 작성한다.
				break; // 반복문 종료
			}
		} while (1);
	}

	FileManager* TextEditor::fileManager() {
		return this->_fileManager;
	}

	InstructionExecutor* TextEditor::instructionExecutor() {
		return this->_instrcutionExecutor;
	}

	void TextEditor::setFileManager(FileManager* newFileManager) {
		this->_fileManager = newFileManager;
	}
	void TextEditor::setLetterPointer(LetterPointer* newLetterPointer) {
		this->_letterPointer = newLetterPointer;
	}
	void TextEditor::setInstructionExecutor(InstructionExecutor* newInstructionExecutor) {
		this->_instrcutionExecutor = newInstructionExecutor;
	}
	

	void TextEditor::textEditor_initialize() {
		//View::print("입력한 파일을 실행합니다.");
		std::string inputFileName = "test";//View::input_Command();
		setFileManager(new FileManager(inputFileName));
		setLetterPointer(new LetterPointer());
		setInstructionExecutor(new InstructionExecutor());

		if (!load_File(inputFileName)) { // 파일을 읽어온다. fileManager()->save_All()을 통해 파일 내용을 파일스토리지로 복사한다.
			exit(0); // 실패한다면 프로그램을 종료한다.
		}

		letterPointer()->setLetterMaxPointer(fileManager()->fileStorage()->originalTextStorageSize()); // 파일스토리지의 size가 maxPointer이다.
	}

	InstructionSet* TextEditor::parseLine(std::string givenCmd) {
		InstructionSetBuilder* instructionSetBuilder = new InstructionSetBuilder();
		return instructionSetBuilder->createInstructionSet(givenCmd);
	}

	void TextEditor::instructionExecute(InstructionSet* givenInstruction) {
		instructionExecutor()->intructionExecutor_initialize(givenInstruction,fileManager()->getOriginalTextStorageFromFileStorage(),letterPointer());
		//executor를 초기화하고, instructionset과, 명령 수행을 위한 파일 스토리지의 vector와 letterPointer를 인자로 넘겨준다.
		instructionExecutor()->process_execute(); // 명령어를 수행한다.
		if (instructionExecutor()->resultCode() == ERROR_NONE) { // 명령어 수행결과 resultCode가 ERROR_NONE일 경우에만 vector를 업데이트한다.
			fileManager()->fileStorage()->updateStorage(instructionExecutor()->modifiedStorage()); // executor에서 수정된 사본 vector를 스토리지 vector에 적용한다.
			letterPointer()->setLetterMaxPointer(fileManager()->fileStorage()->originalTextStorageSize()); // vector의 size가 수정되었을 가능성이 있으므로, maxPonter를 조정한다.
		}
	}

	bool TextEditor::load_File(std::string givenFileName) {
		if (fileManager()->open_FileOnlyRead()) {
			fileManager()->save_All(); // 파일 열었다면 filesaver에 전부 저장
			return true;
		}
		else {
			return false;
		}
	}

	void TextEditor::printPage(){
		FileStorage* fileStorage = fileManager()->fileStorage(); //파일스토리지 불러오기
		bool hasNoLetter = false; // 
		
		if (!isMaxPointer()) {
			int count = letterPointer()->currentStartLocation(); // 현재 페이지의 시작 포인터에서 시작한다.
			
			for (int line = 1; line < MAX_LINE + 1 && !hasNoLetter; line++) { // line은 1~20까지 존재한다.
				View::printLine(""); 
				View::print_IndexOfLine(line); // 한 라인의 인덱스를 출력
				for (int letter = 0; letter < MAX_LENGTH_FOR_ONE_LINE; letter++) { // Letter은 0~74까지 존재한다
					if (count < fileStorage->originalTextStorageSize()) { // 파일스토리지의 총 길이보다 크다면 종료한다.
						char givenLetter = fileStorage->getCharFromStorage(count++); // 파일 스토리지의 count번째 index에서 한 글자를 가져온다.
						View::print(givenLetter); // 해당 글자를 출력한다
						if (givenLetter == '\n') break; // 개행 문자를 받아왔다면 현재 라인의 출력 마침
					}
					else { 
						hasNoLetter = true; // 파일 스토리지보다 count가 더 크다면 더 이상 출력할 문자가 없다.
						break;
					}
				}
			}
			letterPointer()->setLetterEndPointer(count - 1); // 현재 페이지의 끝 포인터는 count-1이다. 출력할 때마다 갱신한다.
		}
	}

	LetterPointer* TextEditor::letterPointer() {
		return this->_letterPointer;
	}

	bool TextEditor::quit() {
		return instructionExecutor()->resultCode() == ERROR_QUIT;
	}

	bool TextEditor::isMaxPointer() {
		return this->letterPointer()->currentStartLocation() >= maxTextStorageSize();
	}

	int TextEditor::maxTextStorageSize() {
		return this->fileManager()->fileStorage()->originalTextStorageSize();
	}

	void TextEditor::settingMainPage() {
		printPage(); // 파일내용 출력
		View::printLine(""); // 개행문자 출력
		View::print_LineOfUnderBar(); // - 라인 출력
		View::print_GuideOfCommand(); // 입력 가이드 출력
		View::print_LineOfUnderBar();// - 라인 출력
		View::print_Prompt_ConsoleMessage(); // "(콘솔메시지)" 출력
		if (instructionExecutor()->resultCode() != ERROR_NONE) // executor의 resultCode가 ERROR_NONE이 아닐때 해당하는 메시지 출력
			View::print(instructionExecutor()->getResultMessage());
		View::printLine(""); // 개행문자 출력
		View::print_LineOfUnderBar();// - 라인 출력
		View::print_Prompt_InputMessage(); // "입력 : " 출력
		return;
	}
