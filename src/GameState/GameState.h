#pragma once
#include <vector>
#include <ctype.h>

#include "Networking/NetworkingTypes.h"

class GameState
{
public:
	std::vector<uint8_t> CreateByteMessage(NetworkMessageType messageType, int data);
	std::vector<uint8_t> CreatePlayerMoveMessage(int selectedIndex);
	std::vector<uint8_t> CreateGameOverMessage();
	std::vector<uint8_t> CreateStateUpdateMesage();

	int8_t GetPlayerSymbol();

	void OnNetworkMessage(const NetworkMessage& message);

	void OnPlayerMove(int location, int symbol);
	const int* GetState() const;
	int GetTurn() const;
	int GetWinner() const;
	bool DidWin() const;

	void StartGame();

	inline bool IsStateUpdatePending() const
	{
		return m_StateUpdatePending;
	}

	inline bool IsGameStarted() const
	{
		return m_GameStarted;
	}

	inline bool CanMakeMove() const
	{
		return m_PlayerSymbol == m_Turn;
	}

	inline bool IsGameReady() const
	{
		return m_PlayersConfirmed == 2;
	}

	inline GameOverReason GetGameOverReason() const
	{
		return m_GameOverReason;
	}

	inline bool IsGameOver() const
	{
		return m_GameOver;
	}

	inline void ChangeTurn() 
	{
		m_Turn++;
		if (m_Turn > 2)
		{
			m_Turn = 1;
		}
	}

	void Reset();
private:
	bool CheckWinner();
	bool CheckSymbol(int startLocation,int directionOffset,int symbol);

private:
	// Replicated Data
	int m_BoardState[9] = {0};
	int m_Turn = 0;

	GameOverReason m_GameOverReason;
	int m_PlayersConfirmed = 0;
	int m_Winner = 0;
	int m_PlayerSymbol = 0;

	bool m_GameStarted = false;
	bool m_GameOver = false;
	bool m_StateUpdatePending = false;
};
