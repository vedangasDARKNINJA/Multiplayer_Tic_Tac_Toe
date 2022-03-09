#pragma once

#include "IApplication.h"

class Server : public IApplication
{
public:
	Server();
	virtual ~Server();
	virtual void Run() override;
	virtual void Close() override;
};
