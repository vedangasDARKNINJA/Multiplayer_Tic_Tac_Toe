#include "CommandLineArgs.h"
#include <iostream>
#include <string.h>
#include <cctype>
#include <ostream>
#include <string>

void CommandLineArgs::ParseArg(char* arg)
{
	static char lastFlag = '\0';
	static bool argParsed = false;

	if(!argParsed)
	{
		if(lastFlag == 'c' || lastFlag == 's')
		{
			mode = lastFlag == 'c' ? ApplicationMode::CLIENT : ApplicationMode::SERVER;
			std::cout << "mode parsed: " << (unsigned int)mode << '\n';
			argParsed = true;
		}
		else if(lastFlag == 'w' || lastFlag == 'h')
		{
			unsigned int value = std::stoi(std::string(arg));
			if(lastFlag == 'w')
			{
				width = value;
			}
			else
			{
				height = value;
			}
			argParsed = true;
		}
		else if(lastFlag == 't')
		{
			title = arg;
			argParsed = true;
		}
	}

	if(strlen(arg) == 2 && arg[0] == '-' && isalpha(arg[1]))
	{
		lastFlag = arg[1];
		argParsed = false;
	}
}
