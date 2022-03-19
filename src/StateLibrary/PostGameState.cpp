#include "PostGameState.h"
#include "raylib.h"

void PostGameState::OnInit() {}

void PostGameState::OnUpdate() {}

void PostGameState::OnRender() 
{
	DrawText("This is Post Game State", 0, 0, 32, LIGHTGRAY);
}

void PostGameState::OnExit() {}
