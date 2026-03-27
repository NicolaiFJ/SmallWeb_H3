#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getSubUrl.h"
#pragma once;

char* getSubUrl(char* buf, int numBytes)//The caller has ownership of the return value
{
	int start = 0;
	int end = 0;

	for (int i = 0; i < numBytes; i++)
	{
		if (buf[i] == '\0')
		{
			break;
		}

		if (start == 0)
		{
			if (buf[i] == ' ')
			{
				start = i;
			}
		}
		else
		{
			if (buf[i] == ' ')
			{
				end = i;
				break;
			}
		}
	}

	if (end == 0)
	{
		return NULL;
	}
	if (end >= numBytes)
	{
		return NULL;
	}
	char* ret = (char*)malloc(end - start + 1);

	if (ret == NULL)
	{
		return NULL;
	}
	


	memcpy(ret, buf + start +1, end - start - 1);
	ret[end - start - 1] = '\0';

	return ret;
}