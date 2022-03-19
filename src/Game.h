#pragma once

class IApplication;

class Game
{
public:
	static Game& Get();
	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator =(const Game&) = delete;
	Game& operator=(Game&&) = delete;

	void InitClient(int width, int height, const char* title);
	void InitServer();
	void Run();
	void Quit();
	void Shutdown();

private:
	Game();
	~Game();

private:
	IApplication* m_App = nullptr;
	bool m_Initialized = false;
};
