#pragma once
#include <string>
class WebManager
{
public:
	bool isMatch(std::string inp, std::string comparer);
	std::string getWebHeadders(int mainFileSize);
};

