#pragma once
#include "IAppState.h"

class GameBoard;

class PlayState : public IAppState
{
public:
	// Inherited via IAppState
	virtual void OnInit() override;
	virtual void OnUpdate() override;
	virtual void OnRender() override;
	virtual void OnExit() override;

private:
	GameBoard* m_GameBoard = nullptr;
};
