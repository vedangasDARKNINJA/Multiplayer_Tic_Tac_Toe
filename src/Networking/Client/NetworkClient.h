#pragma once
#include "../NetworkHost.h"

class NetworkClient: public NetworkHost
{
public:
	virtual NetworkErrorCode Init() override;
	virtual void Destroy() override;
	virtual void ProcessEvents(const ENetEvent& event) override;

	virtual void Send(const std::vector<uint8_t>& messageData) override;
	virtual void OnMessage(ENetPeer* peer, NetworkMessage message) override;

protected:
	virtual void Send(ENetPeer* peer, const std::vector<uint8_t>& messageData)override;

private:
	ENetPeer* m_Peer = nullptr;
};
