#pragma once
#include <ctype.h>

#include "msgpack/msgpack.hpp"

enum class NetworkErrorCode : uint8_t
{
	ENET_NO_ERROR = 0,
	ENET_INIT_ERROR,
	ENET_INVALID_HOST_TYPE_ERROR,
	ENET_HOST_CREATE_ERROR,
	ENET_PEER_CREATE_ERROR,
	ENET_PEER_CONNECT_ERROR,
};

enum class NetworkHostType : uint8_t
{
	ENET_HOST_CLIENT,
	ENET_HOST_SERVER,
};

enum class NetworkMessageType : uint8_t
{
	INVALID = 0,
	SA_GAME_READY,
	SA_STATE_UPDATE,
	SA_GAME_OVER,
	SC_PLAYER_SYMBOL,

	CS_PLAYER_MOVE,
	CS_PLAYER_READY,
};

enum class GameOverReason : unsigned int
{
	PLAYER_DISCONNECTED = 1,
	PLAYER_WON,
	MATCH_TIED
};

struct NetworkMessage
{
	uint8_t messageType;
	std::vector<int> state;

	template <class T>
	void pack(T& pack)
	{
		pack(messageType,state);
	}
};