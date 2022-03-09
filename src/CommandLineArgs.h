#pragma once
#include <string>

enum class ApplicationMode
{
	CLIENT,
	SERVER
};

struct CommandLineArgs
{
	ApplicationMode mode;
	unsigned int width;
	unsigned int height;
	const char* title;

	void ParseArg(char* arg);
};
