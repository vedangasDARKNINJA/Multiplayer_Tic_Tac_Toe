#include <iostream>
#include "Game.h"
#include "CommandLineArgs.h"

int main(int argc, char** argv)
{
	CommandLineArgs arguments;
	/* Command Line Arguments
	* -c : client mode
	* -s : server mode
	* -a : Host Address
	* -t : Client Title
	* -w : Client Window Width
	* -h : Client Window Height
	*/
	for(int i = 0; i < argc; ++i)
	{
		arguments.ParseArg(argv[i]);
	}

	if (arguments.mode == ApplicationMode::CLIENT)
	{
		if (arguments.width == 0 || arguments.height == 0)
		{
			Game::Get().InitClient(640, 800, "Game");
		}
		else
		{
			Game::Get().InitClient(arguments.width, arguments.height, arguments.title);
		}
	}
	else
	{
		Game::Get().InitServer();
	}

	Game::Get().Run();
	
	Game::Get().Shutdown();
	return 0;
}
