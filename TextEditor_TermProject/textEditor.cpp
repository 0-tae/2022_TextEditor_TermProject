
#include <iostream>
#include "textEditor.h"

#define MAX_LINE 20
#define MAX_LENGTH_FOR_ONE_LINE 75


	void TextEditor::run() {
		std::string inputCommand;
		textEditor_initialize(); // �ʱ�ȭ
		do {
			settingMainPage(); // ��� ȭ�� ����
			inputCommand = View::input_Command(); // �Է¹ޱ�
			View::print_LineOfUnderBar(); // - ���� ���
			InstructionSet* instruction = parseLine(inputCommand.c_str()); // �Է°� �м�
			instructionExecute(instruction); // �Է°� ����
			if (quit()) { // ��ɾ� 't'�ϰ�� ���� �� ����
				fileManager()->close_File(); // file�� �ݴ´�.
				fileManager()->open_FileOnlyWrite(); // ���� �������� ����.
				fileManager()->write_All(); // ���� ���丮���� ��� ���� ���Ͽ� �ۼ��Ѵ�.
				break; // �ݺ��� ����
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
		//View::print("�Է��� ������ �����մϴ�.");
		std::string inputFileName = "test";//View::input_Command();
		setFileManager(new FileManager(inputFileName));
		setLetterPointer(new LetterPointer());
		setInstructionExecutor(new InstructionExecutor());

		if (!load_File(inputFileName)) { // ������ �о�´�. fileManager()->save_All()�� ���� ���� ������ ���Ͻ��丮���� �����Ѵ�.
			exit(0); // �����Ѵٸ� ���α׷��� �����Ѵ�.
		}

		letterPointer()->setLetterMaxPointer(fileManager()->fileStorage()->originalTextStorageSize()); // ���Ͻ��丮���� size�� maxPointer�̴�.
	}

	InstructionSet* TextEditor::parseLine(std::string givenCmd) {
		InstructionSetBuilder* instructionSetBuilder = new InstructionSetBuilder();
		return instructionSetBuilder->createInstructionSet(givenCmd);
	}

	void TextEditor::instructionExecute(InstructionSet* givenInstruction) {
		instructionExecutor()->intructionExecutor_initialize(givenInstruction,fileManager()->getOriginalTextStorageFromFileStorage(),letterPointer());
		//executor�� �ʱ�ȭ�ϰ�, instructionset��, ��� ������ ���� ���� ���丮���� vector�� letterPointer�� ���ڷ� �Ѱ��ش�.
		instructionExecutor()->process_execute(); // ��ɾ �����Ѵ�.
		if (instructionExecutor()->resultCode() == ERROR_NONE) { // ��ɾ� ������ resultCode�� ERROR_NONE�� ��쿡�� vector�� ������Ʈ�Ѵ�.
			fileManager()->fileStorage()->updateStorage(instructionExecutor()->modifiedStorage()); // executor���� ������ �纻 vector�� ���丮�� vector�� �����Ѵ�.
			letterPointer()->setLetterMaxPointer(fileManager()->fileStorage()->originalTextStorageSize()); // vector�� size�� �����Ǿ��� ���ɼ��� �����Ƿ�, maxPonter�� �����Ѵ�.
		}
	}

	bool TextEditor::load_File(std::string givenFileName) {
		if (fileManager()->open_FileOnlyRead()) {
			fileManager()->save_All(); // ���� �����ٸ� filesaver�� ���� ����
			return true;
		}
		else {
			return false;
		}
	}

	void TextEditor::printPage(){
		FileStorage* fileStorage = fileManager()->fileStorage(); //���Ͻ��丮�� �ҷ�����
		bool hasNoLetter = false; // 
		
		if (!isMaxPointer()) {
			int count = letterPointer()->currentStartLocation(); // ���� �������� ���� �����Ϳ��� �����Ѵ�.
			
			for (int line = 1; line < MAX_LINE + 1 && !hasNoLetter; line++) { // line�� 1~20���� �����Ѵ�.
				View::printLine(""); 
				View::print_IndexOfLine(line); // �� ������ �ε����� ���
				for (int letter = 0; letter < MAX_LENGTH_FOR_ONE_LINE; letter++) { // Letter�� 0~74���� �����Ѵ�
					if (count < fileStorage->originalTextStorageSize()) { // ���Ͻ��丮���� �� ���̺��� ũ�ٸ� �����Ѵ�.
						char givenLetter = fileStorage->getCharFromStorage(count++); // ���� ���丮���� count��° index���� �� ���ڸ� �����´�.
						View::print(givenLetter); // �ش� ���ڸ� ����Ѵ�
						if (givenLetter == '\n') break; // ���� ���ڸ� �޾ƿԴٸ� ���� ������ ��� ��ħ
					}
					else { 
						hasNoLetter = true; // ���� ���丮������ count�� �� ũ�ٸ� �� �̻� ����� ���ڰ� ����.
						break;
					}
				}
			}
			letterPointer()->setLetterEndPointer(count - 1); // ���� �������� �� �����ʹ� count-1�̴�. ����� ������ �����Ѵ�.
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
		printPage(); // ���ϳ��� ���
		View::printLine(""); // ���๮�� ���
		View::print_LineOfUnderBar(); // - ���� ���
		View::print_GuideOfCommand(); // �Է� ���̵� ���
		View::print_LineOfUnderBar();// - ���� ���
		View::print_Prompt_ConsoleMessage(); // "(�ָܼ޽���)" ���
		if (instructionExecutor()->resultCode() != ERROR_NONE) // executor�� resultCode�� ERROR_NONE�� �ƴҶ� �ش��ϴ� �޽��� ���
			View::print(instructionExecutor()->getResultMessage());
		View::printLine(""); // ���๮�� ���
		View::print_LineOfUnderBar();// - ���� ���
		View::print_Prompt_InputMessage(); // "�Է� : " ���
		return;
	}
