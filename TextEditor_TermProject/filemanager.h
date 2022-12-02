#pragma once

#include <fstream>
#include "filestorage.h"

class FileManager { // 파일을 생성 및 관리, 저장은 saver에서
public:
	FileManager(std::string givenFileName);

	~FileManager();

	bool open_FileOnlyRead();
	bool open_FileOnlyWrite();
	void write_All();
	void write(int );
	void save_All();
	bool close_File();
	std::string fileName();
	FileStorage* fileStorage();
	std::vector<char>& getOriginalTextStorageFromFileStorage();
private:
	std::fstream currentFile;
	std::string _currentFileName;
	FileStorage* _fileStorage;

	void setFileName(std::string);
	void setFileStorage(FileStorage*);
	
};