#include "MenuState.h"
#include "raylib.h"

#include "UI/TextButton.h"
#include "Game.h"
#include "GameState/GameState.h"
#include "Networking/NetworkManager.h"
#include "StateLibrary.h"

void MenuState::OnInit()
{
	m_PlayButton = new TextButton();
	m_PlayButton->SetText("Play");
	m_PlayButton->SetPosition({0.5f * (640 - 150), 0.5f * (800 - 40)});

	m_ExitButton = new TextButton();
	m_ExitButton->SetText("Exit");
	m_ExitButton->SetPosition({0.5f * (640 - 150), 0.5f * (800 + 60)});
}

void MenuState::OnUpdate()
{
	if(m_PlayButton->IsClicked())
	{
		TraceLog(TraceLogLevel::LOG_INFO, "Play Button Clicked");
		NetworkMessage message;
		message.messageType = (uint8_t)NetworkMessageType::CS_PLAYER_READY;
		NetworkManager::Get().Message(msgpack::pack(message));
		StateLibrary::Get().RequestStateChange(APP_STATE::WAIT);
	}

	if(m_ExitButton->IsClicked())
	{
		TraceLog(TraceLogLevel::LOG_INFO, "Exit Button Clicked");
		Game::Get().Quit();
	}
}

void MenuState::OnRender()
{
	DrawText("This is Menu State", 0, 0, 32, LIGHTGRAY);

	const char* text = "Tic Tac Toe";
	Vector2 textDim = MeasureTextEx(GetFontDefault(), text, 64, 6.4f);
	DrawText(text, 0.5f * (640 - textDim.x), 200, 64, LIGHTGRAY);

	m_PlayButton->Render();
	m_ExitButton->Render();
}

void MenuState::OnExit()
{
	delete m_PlayButton;
	delete m_ExitButton;
}
