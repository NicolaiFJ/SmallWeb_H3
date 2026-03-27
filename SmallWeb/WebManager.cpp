#include "WebManager.h"

bool WebManager::isMatch(std::string inp, std::string comparer)
{
    if (comparer.size() <= 0)
    {
        return false;
    }

    if(inp >= comparer)
    { 
        for (int i = 0; i < inp.length(); i++)
        {
            if (inp[i] == '?')
            {
                if (inp.substr(0, i ) == comparer)
                {
                    return true;
                }
            }
        }

        if (inp.size() == comparer.size())
        {
            if (inp == comparer)
            {
                return true;
            }
        }

    }
    return false;
}

std::string WebManager::getWebHeadders(int mainFileSize)
{
    return "HTTP/1.1 200 OK\r\nAccess-Control-Allow-Origin: *\r\nAccess-Control-Allow-Headers: *\r\nContent-Type: application/json\r\nContent-Length: " + std::to_string(mainFileSize) + "\r\n" + "Connection: close\r\n\r\n";
}
