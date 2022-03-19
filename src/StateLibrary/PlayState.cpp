#include "PlayState.h"
#include "raylib.h"
#include "UI/GameBoard.h"

void PlayState::OnInit() {
	m_GameBoard = new GameBoard();

	m_GameBoard->SetPosition({1280 * 0.5f, 720 * 0.5f});
	m_GameBoard->SetSymbolSizePercent(0.5f);
	m_GameBoard->Init(3,3);
}

void PlayState::OnUpdate() {
	
	int selectedTile = m_GameBoard->Update(nullptr);
}

void PlayState::OnRender() 
{
	DrawText("This is Play State", 0, 0, 32, LIGHTGRAY);
	m_GameBoard->Render();
}

void PlayState::OnExit()
{
	delete m_GameBoard;
}
