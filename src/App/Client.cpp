#include "Client.h"
#include "StateLibrary/StateLibrary.h"

#include "StateLibrary/MenuState.h"
#include "StateLibrary/WaitState.h"
#include "StateLibrary/PlayState.h"
#include "StateLibrary/PostGameState.h"

#include "raylib.h"

#include "Networking/NetworkManager.h"


Client::Client(int width, int height, const char* title)
	: m_Width(width)
	, m_Height(height)
	, m_Title(title)
{

	StateLibrary::Get().RegisterState(APP_STATE::MENU, std::make_unique<MenuState>());
	StateLibrary::Get().RegisterState(APP_STATE::WAIT, std::make_unique<WaitState>());
	StateLibrary::Get().RegisterState(APP_STATE::PLAY, std::make_unique<PlayState>());
	StateLibrary::Get().RegisterState(APP_STATE::POSTGAME, std::make_unique<PostGameState>());

	InitWindow(width, height, title);
	SetTargetFPS(60);
}

Client::~Client()
{	
}

void Client::Run()
{
	StateLibrary::Get().Init();
	while(!WindowShouldClose() && !m_ShouldQuit)
	{
		StateLibrary::Get().ProcessStateChanges();
		NetworkManager::Get().PollEvents();

#ifdef DEBUG
		StateLibrary::Get().ProcessEvents();
#endif // DEBUG

		StateLibrary::Get().Update();

		BeginDrawing();
		ClearBackground(RAYWHITE);

		StateLibrary::Get().Render();

		EndDrawing();
	}
}

void Client::Quit() 
{
	m_ShouldQuit = true;
}

void Client::Shutdown() 
{
	CloseWindow();
	NetworkManager::Get().Shutdown();
}
