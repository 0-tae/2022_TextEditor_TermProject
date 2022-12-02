#pragma once

#include <vector>
#include <iostream>

class FileStorage { // ���� ������ ��ü�� ����ִ�.

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