#include "letterpointer.h"


	LetterPointer::LetterPointer() {
		resetLetterPointer();
	}

	void LetterPointer::resetLetterPointer() {
		setLetterStartPointer(0);
		setLetterEndPointer(-1);
	}

	void LetterPointer::setLetterStartPointer(int newStart) {
		this->_startOflocation = newStart;
	}
	void LetterPointer::setLetterEndPointer(int newEnd) {
		this->_endOflocation = newEnd;
	}
	void LetterPointer::setLetterMaxPointer(int newMax) {
		this->_maxOflocation = newMax;
	}
	void LetterPointer::pushPrevLocationToReturnStack(int newStart) {
		this->returnStackForPrevLocation().push(newStart);
	}

	int LetterPointer::popPrevLocationFromReturnStack() {
		int popped = this->returnStackForPrevLocation().top();
		this->returnStackForPrevLocation().pop();
		return popped;
	}

	int LetterPointer::peekPrevStartLocation() {
		return this->returnStackForPrevLocation().top();
	}

	int LetterPointer::currentStartLocation() {
		return this->_startOflocation;
	}
	int LetterPointer::currentEndLocation() {
		return this->_endOflocation;
	}

	std::stack<int>& LetterPointer::returnStackForPrevLocation() {
		return this->_returnStackForPrevLocation;
	}

	int LetterPointer::maxLocation() {
		return this->_maxOflocation;
	}

	bool LetterPointer::returnStackisEmpty() {
		return this->returnStackForPrevLocation().empty();
	}