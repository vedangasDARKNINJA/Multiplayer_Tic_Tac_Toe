#pragma once

#include "IApplication.h"

class Server : public IApplication
{
public:
	Server();
	virtual ~Server();

	// Inherited via IApplication
	virtual void Run() override;
	virtual void Quit() override;
	virtual void Shutdown() override;
};
