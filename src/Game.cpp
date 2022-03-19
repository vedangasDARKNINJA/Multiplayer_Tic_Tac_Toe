#include "Game.h"
#include "App/Client.h"
#include "App/Server.h"

Game::Game()
	: m_App(nullptr)
{}

Game::~Game()
{
	delete m_App;
}

Game& Game::Get()
{
	static Game instance;
	return instance;
}

void Game::InitClient(int width, int height, const char* title)
{
	m_App = new Client(width, height, title);
}

void Game::InitServer()
{
	m_App = new Server();
}

void Game::Run()
{
	m_App->Run();
}

void Game::Quit()
{
	m_App->Quit();
}

void Game::Shutdown()
{
	m_App->Shutdown();
}
