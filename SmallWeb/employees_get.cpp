#include <string>


static std::string Users_get()
{
	std::string ret = 
		"{\"id\":" + std::to_string(rand() % 156) + 
		",\n\"name\":" + "\"Mar\"" + 
		",\n\"email\":" + "\"mail@mail.mail\"" + "}";
	return ret;
}