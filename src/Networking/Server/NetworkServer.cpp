#include "NetworkServer.h"
#include <iostream>

#include "Networking/NetworkManager.h"
#include "Game.h"
#include "GameState/GameState.h"

#define MAX_CLIENTS 32

NetworkErrorCode NetworkServer::Init()
{
	ENetAddress address = {0};

	address.host = ENET_HOST_ANY; /* Bind the server to the default localhost.     */
	address.port = 7777; /* Bind the server to port 7777. */

	m_Host = enet_host_create(&address, MAX_CLIENTS, 2, 0, 0);

	if(m_Host == nullptr)
	{
		return NetworkErrorCode::ENET_HOST_CREATE_ERROR;
	}
	m_IsInitialized = true;
	return NetworkErrorCode::ENET_NO_ERROR;
}

void NetworkServer::ProcessEvents(const ENetEvent& event)
{
	switch(event.type)
	{
	case ENET_EVENT_TYPE_CONNECT: {

		std::cout << "A new client connected from " << std::hex << event.peer->address.host.u.Byte
				  << ":" << event.peer->address.port << "\n";

		/* Reset the peer's client information. */
		event.peer->data = "Client Information";
		break;
	}
	case ENET_EVENT_TYPE_RECEIVE: {
		std::cout << "A packet of length " << event.packet->dataLength << " containing "
				  << event.packet->data << " was received from " << event.peer->data
				  << " on channel" << event.channelID << "\n";

		std::vector<uint8_t> data;
		for(int i = 0; i < event.packet->dataLength; ++i)
		{
			data.push_back(event.packet->data[i]);
		}
		NetworkMessage message = msgpack::unpack<NetworkMessage>(data);
		GameState* gameState = Game::Get().GetGameState();
		if(gameState)
		{
			gameState->OnNetworkMessage(message);
		}
		OnMessage(event.peer, message);
		/* Clean up the packet now that we're done using it. */
		enet_packet_destroy(event.packet);
		break;
	}
	case ENET_EVENT_TYPE_DISCONNECT: {
		std::cout << event.peer->data << " disconnected.\n";
		GameState* gameState = Game::Get().GetGameState();
		if(gameState)
		{
			if(gameState->IsGameStarted())
			{
				NetworkMessage message;
				message.messageType = (uint8_t)NetworkMessageType::SA_GAME_OVER;
				message.state.push_back((uint8_t)GameOverReason::PLAYER_DISCONNECTED);
				SendAll(msgpack::pack(message));
			}
		}
		/* Reset the peer's client information. */
		event.peer->data = nullptr;
		break;
	}
	case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT: {
		std::cout << event.peer->data << " disconnected due to timeout.\n";
		/* Reset the peer's client information. */
		event.peer->data = nullptr;
		break;
	}
	case ENET_EVENT_TYPE_NONE:
	default: {
		break;
	}
	}
}

void NetworkServer::Send(const std::vector<uint8_t>& messageData)
{
	SendAll(messageData);
}

void NetworkServer::OnMessage(ENetPeer* peer, NetworkMessage message)
{
	switch((NetworkMessageType)message.messageType)
	{
	case NetworkMessageType::CS_PLAYER_READY: {
		GameState* gameState = Game::Get().GetGameState();
		if(gameState)
		{
			Send(peer,
				 gameState->CreateByteMessage(NetworkMessageType::SC_PLAYER_SYMBOL,
											  gameState->GetPlayerSymbol()));
		}
		break;
	}
	case NetworkMessageType::CS_PLAYER_MOVE: {
		GameState* gameState = Game::Get().GetGameState();
		if(gameState)
		{
			if(gameState->IsGameOver())
			{
				SendAll(gameState->CreateGameOverMessage());
				gameState->Reset();
			}
			else if(gameState->IsStateUpdatePending())
			{
				SendAll(gameState->CreateStateUpdateMesage());
			}
		}
		break;
	}
	}
}

void NetworkServer::Send(ENetPeer* peer, const std::vector<uint8_t>& messageData)
{
	/* Create a reliable packet of size 7 containing "packet\0" */
	ENetPacket* packet =
		enet_packet_create(messageData.data(), messageData.size(), ENET_PACKET_FLAG_RELIABLE);

	/* Send the packet to the peer over channel id 0. */
	enet_peer_send(peer, 0, packet);
}

void NetworkServer::SendAll(const std::vector<uint8_t>& messageData)
{
	/* Create a reliable packet of size 7 containing "packet\0" */
	ENetPacket* packet =
		enet_packet_create(messageData.data(), messageData.size(), ENET_PACKET_FLAG_RELIABLE);

	/* Send the packet to all over channel id 0. */
	enet_host_broadcast(m_Host, 0, packet);
}
