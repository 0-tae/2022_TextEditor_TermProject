#pragma once

#include "filemanager.h"
#include "Instructionsetbuilder.h"
#include "instructionsetexecutor.h"
#include "view.h"




class TextEditor {
public:
	void run();

private:
	FileManager* _fileManager; // ���� ������
	InstructionExecutor* _instrcutionExecutor; // ��� ������
	LetterPointer* _letterPointer; // letter
\

	void setFileManager(FileManager* );
	void setLetterPointer(LetterPointer*);
	void setInstructionExecutor(InstructionExecutor*);

	void textEditor_initialize();
	FileManager* fileManager();
	InstructionExecutor* instructionExecutor();
	LetterPointer* letterPointer();
	InstructionSet* parseLine(std::string);

	void instructionExecute(InstructionSet*);
	bool load_File(std::string);
	void printPage();
	bool quit();
	bool isMaxPointer();
	int maxTextStorageSize();
	void settingMainPage();
};