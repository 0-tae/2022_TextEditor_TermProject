#pragma once
#include <stack>
#define MAX_LINE 20
#define MAX_LENGTH_FOR_ONE_LINE 75
class LetterPointer {
public:
	LetterPointer();

	void resetLetterPointer();
	void setLetterStartPointer(int );
	void setLetterEndPointer(int);
	void setLetterMaxPointer(int);

	int peekPrevStartLocation();
	int currentStartLocation();
	int currentEndLocation();
	int maxLocation();

	void pushPrevLocationToReturnStack(int newStart);
	int popPrevLocationFromReturnStack();

	bool returnStackisEmpty();
private:
	std::stack<int> _returnStackForPrevLocation;
	int _startOflocation;
	int _endOflocation;
	int _maxOflocation;

	std::stack<int>& returnStackForPrevLocation();

};
