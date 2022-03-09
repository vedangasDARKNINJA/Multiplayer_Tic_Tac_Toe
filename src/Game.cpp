#include "Game.h"
#include "App/Client.h"
#include "App/Server.h"

Game::Game()
	: m_App(nullptr)
{}

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

void Game::Close()
{
	m_App->Close();
}
