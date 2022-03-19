#include "MenuState.h"
#include "raylib.h"

#include "UI/TextButton.h"
#include "Game.h"
#include "StateLibrary.h"

void MenuState::OnInit()
{
	m_PlayButton = new TextButton();
	m_PlayButton->SetText("Play");
	m_PlayButton->SetPosition({0.5f * (1280 - 150), 0.5f * (720 - 40)});

	m_ExitButton = new TextButton();
	m_ExitButton->SetText("Exit");
	m_ExitButton->SetPosition({0.5f * (1280 - 150), 0.5f * (720 + 60)});
}

void MenuState::OnUpdate()
{
	if(m_PlayButton->IsClicked())
	{
		TraceLog(TraceLogLevel::LOG_INFO, "Play Button Clicked");
		StateLibrary::Get().RequestStateChange(APP_STATE::PLAY);
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

	Vector2 textDim = MeasureTextEx(GetFontDefault(), "Tic Tac Toe", 64, 6.4f);
	DrawText("Tic Tac Toe", 0.5f * (1280 - textDim.x), 200, 64, LIGHTGRAY);

	m_PlayButton->Render();
	m_ExitButton->Render();
}

void MenuState::OnExit()
{
	delete m_PlayButton;
	delete m_ExitButton;
}
