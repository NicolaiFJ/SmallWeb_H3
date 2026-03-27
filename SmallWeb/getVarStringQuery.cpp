#include <string>
#include "getVarStringQuery.h"

std::string getVarStringQuery(char* buf, int buffSize, std::string get)
{
	int startName = 0;
	int endName = 0;

	bool foundMatch = false;

	std::string copy(buf, buffSize);

	for (int i = 0; i < buffSize; i++)
	{
		if (foundMatch)
		{
			if (buf[i] == '&')
				return copy.substr(startName, i - startName);
		}

		if (buf[i] == '?' || buf[i] == '&')
		{
			startName = i + 1;
		}
		else if (buf[i] == '=')
		{
			endName = i;

			if (copy.substr(startName, endName - startName) == get)
			{
				foundMatch = true;
				startName = i + 1;
			}
		}
	}

	
	if (foundMatch)
		return copy.substr(startName, buffSize - startName);

	return "";
}
