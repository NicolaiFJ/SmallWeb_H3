#pragma once
#include <vector>
#include <string>

class JsonCreator
{
	std::vector<std::string> data;

	void addData(std::string container, std::string data);
	std::string getJSON();
};

