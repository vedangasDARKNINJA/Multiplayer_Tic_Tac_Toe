#pragma once

#include "IApplication.h"

class Client : public IApplication
{
public:
	Client(int width, int height, const char* title);
	virtual ~Client();
	virtual void Run() override;
	virtual void Quit() override;
	virtual void Shutdown() override;

private:
	int m_Width;
	int m_Height;
	const char* m_Title;

	bool m_ShouldQuit = false;
};
