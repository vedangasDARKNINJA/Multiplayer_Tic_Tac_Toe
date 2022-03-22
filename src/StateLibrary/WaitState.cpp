#include "WaitState.h"
#include "raylib.h"

#include "Game.h"
#include "StateLibrary.h"

void WaitState::OnInit()
{
	
}

void WaitState::OnUpdate()
{
	// TODO: Check game state
}

void WaitState::OnRender()
{
	DrawText("This is Wait State", 0, 0, 32, LIGHTGRAY);

	const char* text ="Waiting for other player...";
	Vector2 textDim = MeasureTextEx(GetFontDefault(), text, 32, 6.4f);
	DrawText(text, 0.5f * (640 - textDim.x), 0.5f * (800 - textDim.y), 32, LIGHTGRAY);

}

void WaitState::OnExit()
{

}
