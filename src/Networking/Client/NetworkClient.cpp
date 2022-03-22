#include "NetworkClient.h"
#include <iostream>
#include <vector>

#include "Game.h"
#include "GameState/GameState.h"

NetworkErrorCode NetworkClient::Init()
{
	m_Host = enet_host_create(NULL /* create a client host */,
							  1 /* only allow 1 outgoing connection */,
							  2 /* allow up 2 channels to be used, 0 and 1 */,
							  0 /* assume any amount of incoming bandwidth */,
							  0 /* assume any amount of outgoing bandwidth */);
	if(m_Host == nullptr)
	{
		return NetworkErrorCode::ENET_HOST_CREATE_ERROR;
	}

	ENetAddress address = {0};
	m_Peer = {0};

	/* Connect to some.server.net:1234. */
	enet_address_set_host(&address, "127.0.0.1");
	address.port = 7777;

	/* Initiate the connection, allocating the two channels 0 and 1. */
	m_Peer = enet_host_connect(m_Host, &address, 2, 0);
	if(m_Peer == nullptr)
	{
		std::cout << "No available peers for initiating an ENet connection.\n";
		return NetworkErrorCode::ENET_PEER_CREATE_ERROR;
	}

	ENetEvent event;
	if(enet_host_service(m_Host, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
	{
		std::cout << "Connected Successfully to the server!\n";
		m_IsInitialized = true;
	}
	else
	{
		/* Either the 5 seconds are up or a disconnect event was */
		/* received. Reset the peer in the event the 5 seconds   */
		/* had run out without any significant event.            */
		enet_peer_reset(m_Peer);
		std::cout << "Connected Failed to the server!\n";
		return NetworkErrorCode::ENET_PEER_CONNECT_ERROR;
	}

	return NetworkErrorCode::ENET_NO_ERROR;
}

void NetworkClient::ProcessEvents(const ENetEvent& event)
{
	switch(event.type)
	{
	case ENET_EVENT_TYPE_RECEIVE: {

		std::cout << "A packet of length " << event.packet->dataLength << " containing "
				  << event.packet->data << " was received from " << event.peer->address.host.u.Byte
				  << ":" << event.peer->address.port << " on channel " << event.channelID << "\n";
		GameState* gameState = Game::Get().GetGameState();
		if(gameState)
		{
			std::vector<uint8_t> data;
			for(int i = 0; i < event.packet->dataLength; ++i)
			{
				data.push_back(event.packet->data[i]);
			}
			NetworkMessage message = msgpack::unpack<NetworkMessage>(data);
			Game::Get().GetGameState()->OnNetworkMessage(message);
			OnMessage(event.peer, message);
		}

		enet_packet_destroy(event.packet);
		break;
	}
	}
}

void NetworkClient::Send(const std::vector<uint8_t>& messageData)
{
	Send(m_Peer, messageData);
}

void NetworkClient::OnMessage(ENetPeer* peer, NetworkMessage message) 
{
	// ignore peer as peer would be server

}

void NetworkClient::Send(ENetPeer* peer, const std::vector<uint8_t>& messageData)
{
	if(!m_Peer)
	{
		return;
	}

	/* Create a reliable packet of size 7 containing "packet\0" */
	ENetPacket* packet =
		enet_packet_create(messageData.data(), messageData.size(), ENET_PACKET_FLAG_RELIABLE);

	/* Send the packet to the peer over channel id 0. */
	enet_peer_send(m_Peer, 0, packet);
}

void NetworkClient::Destroy()
{
	if(!IsInitialized())
	{
		return;
	}

	// Disconnect
	enet_peer_disconnect(m_Peer, 0);

	ENetEvent event;

	uint8_t disconnected = false;
	/* Allow up to 3 seconds for the disconnect to succeed
   * and drop any packets received packets.
   */
	while(enet_host_service(GetHost(), &event, 3000) > 0)
	{
		switch(event.type)
		{
		case ENET_EVENT_TYPE_RECEIVE:
			// Ignore packets after disconnection
			enet_packet_destroy(event.packet);
			break;
		case ENET_EVENT_TYPE_DISCONNECT:
			disconnected = true;
			break;
		}
	}

	// Drop connection, since disconnection didn't successed
	if(!disconnected)
	{
		enet_peer_reset(m_Peer);
	}

	NetworkHost::Destroy();
}
