#include "filemanager.h"

FileManager::FileManager(std::string givenFileName) {
		this->setFileStorage(new FileStorage());
		this->setFileName(givenFileName);
	}

FileManager::~FileManager() {
		this->close_File();
	}


	bool FileManager::open_FileOnlyRead() {
		
		if (!currentFile.is_open()) {
			currentFile.open(this->fileName().append(".txt"), std::ios::in);
			return true;
		}
		else
			return false;
	}
	bool FileManager::FileManager::open_FileOnlyWrite() {
		if (!currentFile.is_open()) {
			currentFile.open(this->fileName().append(".txt"), std::ios::trunc | std::ios::out); // 전부 삭제된다.
		}
		else
			return false;
	}

	void FileManager::write_All() {
		int i = 0;
		int size = fileStorage()->originalTextStorageSize();

		for (i = 0; i < size; i++) write(i);
	}

	void FileManager::write(int idx) {
		currentFile.put(fileStorage()->getCharFromStorage(idx)); // 파일 세이버에서 한 글자를 가져옴
	}

	void FileManager::save_All() { //  파일에서 한 글자를 읽어와 파일 세이버에 한 글자 저장
		char getCharFromFile;
		
		while (!currentFile.eof()) {
			currentFile.get(getCharFromFile); // 파일에서 한 글자를 읽어와 저장
			fileStorage()->sendCharToStorage(getCharFromFile); // 파일세이버에 파일의 한 글자를 전송
		}
	}

	bool FileManager::close_File() {
		if (currentFile.is_open()) {
			currentFile.close();
			return true;
		}
		else return false;

	}

	std::string FileManager::fileName() {
		return this->_currentFileName;
	}

	FileStorage* FileManager::fileStorage() {
		return _fileStorage;
	}

	void FileManager::setFileName(std::string givenFileName) {
		this->_currentFileName = givenFileName;
	}

	void FileManager::setFileStorage(FileStorage* newFileStorage) {
		this->_fileStorage = newFileStorage;
	}

	std::vector<char>& FileManager::getOriginalTextStorageFromFileStorage() {
		return this->fileStorage()->originalTextStorage();
	}
