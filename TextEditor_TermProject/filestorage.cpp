#include <vector>
#include "filestorage.h"

FileStorage::FileStorage() {}

	void FileStorage::sendCharToStorage(char c) {
		
		originalTextStorage().push_back(c);

	}

	void FileStorage::sendCharToStorageWithIndex(int idx, char c) {
		std::vector<char>::iterator it = originalTextStorage().begin();
		originalTextStorage().insert(it + idx, c);// x번째부터 idx 떨어진 값에 c 추가
	}

	char FileStorage::getCharFromStorage(int idx) {
		if (originalTextStorageSize() > 0)
			return originalTextStorage()[idx];
		else
			return NULL;
	}


	std::vector<char>& FileStorage::originalTextStorage() {
		return this->_originalTextStorage;
	}
	

	int FileStorage::originalTextStorageSize() {
		return originalTextStorage().size();
	}

	void FileStorage::updateStorage(std::vector<char>& targetStorage) {
		originalTextStorage().swap(targetStorage);
	}