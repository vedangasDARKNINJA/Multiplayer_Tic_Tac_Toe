#pragma once
#include "../NetworkHost.h"

class NetworkServer : public NetworkHost
{
public:
	virtual NetworkErrorCode Init() override;
	virtual void ProcessEvents(const ENetEvent& event) override;
	virtual void Send(const std::vector<uint8_t>& messageData) override;
	virtual void OnMessage(ENetPeer* peer, NetworkMessage message);

protected:
	virtual void Send(ENetPeer* peer, const std::vector<uint8_t>& messageData) override;
	virtual void SendAll(const std::vector<uint8_t>& messageData) override;

private:
};
