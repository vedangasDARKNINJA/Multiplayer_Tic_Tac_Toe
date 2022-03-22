#pragma once

#include "NetworkingTypes.h"

#include "enet.h"

#include <vector>
#include <ctype.h>


class NetworkHost
{
public:
	virtual NetworkErrorCode Init();
	virtual void Destroy();

	virtual void ProcessEvents(const ENetEvent& event);
	virtual bool IsInitialized() const;
	virtual void Send(const std::vector<uint8_t>& messageData);
	virtual void OnMessage(ENetPeer* peer, NetworkMessage message);

	ENetHost* GetHost()const;
protected:
	virtual void Send(ENetPeer* peer, const std::vector<uint8_t>& messageData);
	virtual void SendAll(const std::vector<uint8_t>& messageData);

protected:
	bool m_IsInitialized = false;
	ENetHost* m_Host = nullptr;
};
