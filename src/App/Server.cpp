#include "Server.h"
#include <iostream>
#include <conio.h>
#include "Game.h"
#include "GameState/GameState.h"
#include "Networking/NetworkManager.h"

void Server::Run()
{
	while(!m_ShouldClose)
	{
		if(_kbhit())
		{
			int code = _getch();
			if(code == 'q')
			{
				m_ShouldClose = true;
			}
		}
		NetworkManager::Get().PollEvents();
		GameState* gameState = Game::Get().GetGameState();
		if(gameState)
		{
			if(gameState->IsGameReady() && !gameState->IsGameStarted())
			{
				NetworkMessage message;
				message.messageType = (uint8_t)NetworkMessageType::SA_GAME_READY;
				NetworkManager::Get().Message(msgpack::pack(message));

				gameState->StartGame();
				NetworkManager::Get().Message(gameState->CreateStateUpdateMesage());
			}
		}
	}
}

void Server::Quit()
{
	m_ShouldClose = true;
}

void Server::Shutdown() {}
