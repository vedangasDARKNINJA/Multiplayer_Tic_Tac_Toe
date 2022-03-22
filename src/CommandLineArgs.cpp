#include "CommandLineArgs.h"
#include <iostream>
#include <string.h>
#include <cctype>
#include <ostream>
#include <string>

void CommandLineArgs::ParseArg(char* arg)
{
	static char currFlag = '\0';
	static bool isFlag = false;
	static bool argParsed = false;

	if(strlen(arg) == 2 && arg[0] == '-' && isalpha(arg[1]))
	{
		currFlag = arg[1];
		argParsed = false;
		isFlag = true;
	}
	else
	{
		isFlag = false;
	}

	if(!argParsed)
	{
		if(currFlag == 'c' || currFlag == 's')
		{
			mode = currFlag == 'c' ? ApplicationMode::CLIENT : ApplicationMode::SERVER;
			argParsed = true;
		}
		else if((currFlag == 'w' || currFlag == 'h') && !isFlag)
		{
			unsigned int value = std::stoi(std::string(arg));
			if(currFlag == 'w')
			{
				width = value;
			}
			else
			{
				height = value;
			}
			argParsed = true;
		}
		else if((currFlag == 't') && !isFlag)
		{
			title = arg;
			argParsed = true;
		}
	}
}
