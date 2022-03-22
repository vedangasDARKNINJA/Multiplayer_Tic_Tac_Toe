#pragma once
#include <string>

enum class ApplicationMode
{
	CLIENT,
	SERVER
};

struct CommandLineArgs
{
	ApplicationMode mode = ApplicationMode::CLIENT;
	unsigned int width = 0;
	unsigned int height = 0;
	const char* title = "Game";

	void ParseArg(char* arg);
};
