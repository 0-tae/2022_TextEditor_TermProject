#pragma once

#include <vector>
#include <iostream>

class FileStorage { // 원본 파일의 전체를 담고있다.

public:
	FileStorage();

	void sendCharToStorage(char);

	void sendCharToStorageWithIndex(int , char );

	char getCharFromStorage(int );

	std::vector<char>& originalTextStorage();

	int originalTextStorageSize();
	
	void updateStorage(std::vector<char>&);

private:
	std::vector<char> _originalTextStorage;
};