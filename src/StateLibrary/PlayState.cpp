#include "PlayState.h"
#include "raylib.h"
#include "UI/GameBoard.h"

#include "Game.h"
#include "GameState/GameState.h"
#include "Networking/NetworkManager.h"

void PlayState::OnInit()
{
	m_GameBoard = new GameBoard();

	m_GameBoard->SetPosition({640 * 0.5f, 800 * 0.5f});
	m_GameBoard->SetPadding(10);
	m_GameBoard->SetBlockSize(76);
	m_GameBoard->SetSymbolSizePercent(0.5f);
	m_GameBoard->Init(3, 3);
}

void PlayState::OnUpdate()
{
	if(GameState* gamestate = Game::Get().GetGameState())
	{
		int selectedTile = m_GameBoard->Update(gamestate->GetState(),gamestate->CanMakeMove());
		if (selectedTile != -1)
		{
			NetworkManager::Get().Message(gamestate->CreatePlayerMoveMessage(selectedTile));
		}
	}
}

void PlayState::OnRender()
{
	DrawText("This is Play State", 0, 0, 32, LIGHTGRAY);
	if(GameState* gamestate = Game::Get().GetGameState())
	{
		if (gamestate->CanMakeMove())
		{
			DrawText("Your Turn", 0, 40, 32, LIGHTGRAY);
		}
		else
		{
			DrawText("Opponent's Turn", 0, 40, 32, LIGHTGRAY);
		}
	}
	m_GameBoard->Render();
}

void PlayState::OnExit()
{
	delete m_GameBoard;
}
