#pragma once

class IApplication;

class Game
{
public:
	Game();
	void InitClient(int width, int height, const char* title);
	void InitServer();
	void Run();
	void Close();

private:
	IApplication* m_App = nullptr;
	bool m_Initialized = false;
};
