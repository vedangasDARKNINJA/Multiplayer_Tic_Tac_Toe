#include "Client.h"
#include "raylib.h"

Client::Client(int width, int height, const char* title)
{
	InitWindow(width, height, title);
	SetTargetFPS(60);
}

Client::~Client()
{
	CloseWindow();
}

void Client::Run()
{
	while(!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

		EndDrawing();
	}
}

void Client::Close()
{
	delete this;
}
