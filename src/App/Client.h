#pragma once

#include "IApplication.h"

class Client : public IApplication
{
public:
	Client(int width, int height, const char* title);
	virtual ~Client();
	virtual void Run() override;
	virtual void Close() override;
};
