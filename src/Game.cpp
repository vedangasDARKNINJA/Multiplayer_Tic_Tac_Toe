#include "Game.h"

#include <iostream>

#include "App/Client.h"
#include "App/Server.h"
#include "Networking/NetworkManager.h"
#include "GameState/GameState.h"

Game::Game()
	: m_App(nullptr)
	, m_GameState(nullptr)
	, m_IsClient(false)
	, m_Initialized(false)
{
	m_GameState = new GameState();
}

Game::~Game()
{
	delete m_GameState; 
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
	m_IsClient = true;
}

void Game::InitServer()
{
	m_App = new Server();
}

void Game::Run()
{
	NetworkErrorCode errorCode;
	if(m_IsClient)
	{
		errorCode = NetworkManager::Get().Init(NetworkHostType::ENET_HOST_CLIENT);
	}
	else
	{
		errorCode = NetworkManager::Get().Init(NetworkHostType::ENET_HOST_SERVER);
	}

	if(errorCode != NetworkErrorCode::ENET_NO_ERROR)
	{
		std::cout << "Error initializing Network Manager. error code :"
				  << static_cast<unsigned int>(errorCode) << "\n";
		return;
	}

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

GameState* Game::GetGameState() const
{
	return m_GameState;
}
