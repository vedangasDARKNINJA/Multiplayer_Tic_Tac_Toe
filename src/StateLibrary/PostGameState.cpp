#include "PostGameState.h"
#include "raylib.h"
#include "Game.h"
#include "GameState/GameState.h"

void PostGameState::OnInit()
{
	GameState* gameState = Game::Get().GetGameState();
	if(gameState)
	{
		GameOverReason gameOverReason = gameState->GetGameOverReason();
		if(gameOverReason == GameOverReason::PLAYER_WON)
		{
			if(gameState->DidWin())
			{
				m_GameOverReason = "You Won!";
			}
			else
			{
				m_GameOverReason = "You Lost.";
			}
		}
		else if(gameOverReason == GameOverReason::MATCH_TIED)
		{
			m_GameOverReason = "Match Tied.";
		}
		else if(gameOverReason == GameOverReason::PLAYER_DISCONNECTED)
		{
			m_GameOverReason = "Other player disconnected...";
		}
	}
}

void PostGameState::OnUpdate() {}

void PostGameState::OnRender()
{
	DrawText("This is Post Game State", 0, 0, 32, LIGHTGRAY);
	Vector2 textDim = MeasureTextEx(GetFontDefault(), m_GameOverReason.c_str(), 32, 6.4f);
	DrawText(m_GameOverReason.c_str(),
			 0.5f * (640 - textDim.x),
			 0.5f * (800 - textDim.y),
			 32,
			 LIGHTGRAY);
}

void PostGameState::OnExit() {}
