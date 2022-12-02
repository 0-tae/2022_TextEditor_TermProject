#pragma once
#include <string>

std::string& ltrim(std::string&, const char* t = " \t\n\r\f\v");
std::string& rtrim(std::string&, const char* t = " \t\n\r\f\v");
std::string& trim(std::string&, const char* t = " \t\n\r\f\v");