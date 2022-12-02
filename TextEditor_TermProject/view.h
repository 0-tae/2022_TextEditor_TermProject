#pragma once
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;
class View {
public:
	
	static void print_IndexOfLine(int);
	static void print_LineOfUnderBar();
	static void print_GuideOfCommand();
	static void print_ErrorMessage(int);
	static void print_Prompt_ConsoleMessage();
	static void print_Prompt_InputMessage();

	static void printLine(int);
	static void printLine(std::string);
	static void printLine(char);

	static void print(std::string);
	static void print(char);
	static void print(int);

	static string input_Command();
};