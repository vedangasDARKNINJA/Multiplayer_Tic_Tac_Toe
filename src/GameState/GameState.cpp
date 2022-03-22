#include "GameState.h"
#include "Game.h"
#include "StateLibrary/StateLibrary.h"
#include <iostream>

std::vector<uint8_t> GameState::CreateByteMessage(NetworkMessageType messageType, int data)
{
	static NetworkMessage message;
	message.messageType = (uint8_t)messageType;
	message.state.clear();
	message.state.push_back(data);
	return msgpack::pack(message);
}

std::vector<uint8_t> GameState::CreatePlayerMoveMessage(int selectedIndex)
{
	static NetworkMessage message;
	message.messageType = (uint8_t)NetworkMessageType::CS_PLAYER_MOVE;
	message.state.clear();
	message.state.push_back(selectedIndex);
	message.state.push_back(m_PlayerSymbol);
	return msgpack::pack(message);
}

std::vector<uint8_t> GameState::CreateGameOverMessage()
{
	static NetworkMessage message;
	message.messageType = (uint8_t)NetworkMessageType::SA_GAME_OVER;
	message.state.clear();
	message.state.push_back((int)m_GameOverReason);
	message.state.push_back(m_Winner);
	return msgpack::pack(message);
}

std::vector<uint8_t> GameState::CreateStateUpdateMesage()
{
	static NetworkMessage message;
	message.messageType = (uint8_t)NetworkMessageType::SA_STATE_UPDATE;
	message.state.clear();
	message.state.reserve(10);
	for(int i = 0; i < 9; ++i)
	{
		message.state.push_back(m_BoardState[i]);
	}
	message.state.push_back(m_Turn);

	if(m_StateUpdatePending)
	{
		m_StateUpdatePending = false;
	}
	return msgpack::pack(message);
}

int8_t GameState::GetPlayerSymbol()
{
	if(!Game::Get().IsClient())
	{
		m_PlayerSymbol++;
	}

	return m_PlayerSymbol;
}

void GameState::OnNetworkMessage(const NetworkMessage& message)
{
	switch((NetworkMessageType)message.messageType)
	{
	case NetworkMessageType::SA_GAME_READY: {
		StateLibrary::Get().RequestStateChange(APP_STATE::PLAY);
		break;
	}
	case NetworkMessageType::SA_STATE_UPDATE: {
		if(message.state.size() >= 10)
		{
			for(int i = 0; i < 9; ++i)
			{
				m_BoardState[i] = message.state[i];
			}

			m_Turn = message.state[9];
		}

		break;
	}
	case NetworkMessageType::SA_GAME_OVER: {
		m_GameOver = true;
		m_GameOverReason = (GameOverReason)message.state[0];
		if((m_GameOverReason == GameOverReason::PLAYER_WON) ||
		   (m_GameOverReason == GameOverReason::MATCH_TIED))
		{
			if(message.state.size() > 1)
			{
				m_Winner = message.state[1];
			}
		}
		StateLibrary::Get().RequestStateChange(APP_STATE::POSTGAME);
		break;
	}
	case NetworkMessageType::SC_PLAYER_SYMBOL: {
		m_PlayerSymbol = message.state[0];
		break;
	}
	case NetworkMessageType::CS_PLAYER_MOVE: {
		OnPlayerMove(message.state[0], message.state[1]);
		if(!CheckWinner())
		{
			ChangeTurn();
			m_StateUpdatePending = true;
		}
		break;
	}
	case NetworkMessageType::CS_PLAYER_READY: {
		m_PlayersConfirmed++;
		break;
	}
	case NetworkMessageType::INVALID:
	default: {
		break;
	}
	}
}

void GameState::OnPlayerMove(int location, int symbol)
{
	if(location >= 0 && location < 9)
	{
		if(m_BoardState[location] == 0)
		{
			m_BoardState[location] = symbol;
		}
	}
}

const int* GameState::GetState() const
{
	return m_BoardState;
}

int GameState::GetTurn() const
{
	return m_Turn;
}

int GameState::GetWinner() const
{
	return m_Winner;
}

bool GameState::DidWin() const
{
	return m_PlayerSymbol == m_Winner;
}

void GameState::StartGame()
{
	m_GameStarted = true;
	m_Turn = 1;
	for(int i = 0; i < 9; ++i)
	{
		m_BoardState[i] = 0;
	}
}

bool GameState::CheckWinner()
{
	bool player1Row1 = CheckSymbol(0, 1, 1);
	bool player1Row2 = CheckSymbol(3, 1, 1);
	bool player1Row3 = CheckSymbol(6, 1, 1);

	bool player1Col1 = CheckSymbol(0, 3, 1);
	bool player1Col2 = CheckSymbol(1, 3, 1);
	bool player1Col3 = CheckSymbol(2, 3, 1);

	bool player1Dia1 = CheckSymbol(0, 4, 1);
	bool player1Dia2 = CheckSymbol(2, 1, 1);

	bool player2Row1 = CheckSymbol(0, 1, 2);
	bool player2Row2 = CheckSymbol(3, 1, 2);
	bool player2Row3 = CheckSymbol(6, 1, 2);

	bool player2Col1 = CheckSymbol(0, 3, 2);
	bool player2Col2 = CheckSymbol(1, 3, 2);
	bool player2Col3 = CheckSymbol(2, 3, 2);

	bool player2Dia1 = CheckSymbol(0, 4, 2);
	bool player2Dia2 = CheckSymbol(2, 1, 2);

	if(player1Col1 || player1Col2 || player1Col3 || player1Dia1 || player1Dia2 || player1Row1 ||
	   player1Row2 || player1Row3)
	{
		m_Winner = 1;
		m_GameOver = true;
		m_GameOverReason = GameOverReason::PLAYER_WON;
		return true;
	}
	else if(player2Col1 || player2Col2 || player2Col3 || player2Dia1 || player2Dia2 ||
			player2Row1 || player2Row2 || player2Row3)
	{
		m_Winner = 2;
		m_GameOver = true;
		m_GameOverReason = GameOverReason::PLAYER_WON;
		return true;
	}
	else
	{
		int filledPlaces = 0;
		for(int i = 0; i < 9; ++i)
		{
			if(m_BoardState[i] != 0)
			{
				filledPlaces++;
			}
		}

		if(filledPlaces == 9)
		{
			m_Winner = 3;
			m_GameOver = true;
			m_GameOverReason = GameOverReason::MATCH_TIED;
			return true;
		}
	}

	return false;
}

bool GameState::CheckSymbol(int startLocation, int directionOffset, int symbol)
{
	bool hasMatch = true;
	int counts = 0;
	for(int i = startLocation; i < 9 && counts < 3; i += directionOffset)
	{
		if(m_BoardState[i] != symbol)
		{
			hasMatch = false;
		}
		else
		{
			counts++;
		}
	}

	return hasMatch;
}

void GameState::Reset() 
{
	for (int i = 0; i < 9; ++i)
	{
		m_BoardState[i] = 0;
	}
	m_GameOver = false;
	m_GameStarted = false;
	m_StateUpdatePending = false;
	m_PlayersConfirmed = 0;
	m_Winner = 0;
	m_PlayerSymbol = 0;
	m_Turn = 0;
}
