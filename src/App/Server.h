#pragma once

#include "IApplication.h"

class Server : public IApplication
{
public:
	Server() = default;
	~Server() = default;

	// Inherited via IApplication
	virtual void Run() override;
	virtual void Quit() override;
	virtual void Shutdown() override;

private:
	bool m_ShouldClose = false;
};
