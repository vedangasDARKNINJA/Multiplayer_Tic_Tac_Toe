#pragma once

class IApplication;
class GameState;

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

	GameState* GetGameState() const;
	
	inline bool IsClient() const
	{
		return m_IsClient;
	}

private:
	Game();
	~Game();

private:
	bool m_IsClient;
	IApplication* m_App;
	GameState* m_GameState;
	bool m_Initialized;
};
