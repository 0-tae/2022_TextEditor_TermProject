#include "trim.h"


 std::string& ltrim(std::string& s, const char* t)
{
	s.erase(0, s.find_first_not_of(t));
	return s;
}

 std::string& rtrim(std::string& s, const char* t)
{
	s.erase(s.find_last_not_of(t) + 1);
	return s;
}

 std::string& trim(std::string& s, const char* t)
{
	return ltrim(rtrim(s, t), t);
}