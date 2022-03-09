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

	Game game;
	game.InitClient(arguments.width, arguments.height, arguments.title);
	game.Run();
	game.Close();

	return 0;
}
