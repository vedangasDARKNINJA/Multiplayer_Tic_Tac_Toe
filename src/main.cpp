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
		std::cout << argv[i] << std::endl;
		arguments.ParseArg(argv[i]);
	}

	if (argc < 2)
	{
		Game::Get().InitClient(1280, 720, "Game");
	}
	else
	{
		Game::Get().InitClient(arguments.width, arguments.height, arguments.title);
	}

	Game::Get().Run();
	
	Game::Get().Shutdown();
	return 0;
}
