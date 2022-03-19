#pragma once

class IApplication
{
public:
	virtual ~IApplication() {}
	virtual void Run() = 0;
	virtual void Quit() = 0;
	virtual void Shutdown() = 0;
};
