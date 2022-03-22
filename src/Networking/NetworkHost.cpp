#include "NetworkHost.h"

NetworkErrorCode NetworkHost::Init() 
{
	// To be handled by Network Client and Server
	return NetworkErrorCode::ENET_NO_ERROR;
}

void NetworkHost::Destroy()
{
	if (m_Host)
	{
		enet_host_destroy(m_Host);
	}
}

void NetworkHost::ProcessEvents(const ENetEvent& event) {}

bool NetworkHost::IsInitialized() const
{
	return m_IsInitialized;
}

void NetworkHost::Send(const std::vector<uint8_t>& messageData) {
	// for public API
}

void NetworkHost::OnMessage(ENetPeer* peer, NetworkMessage message) {}

void NetworkHost::Send(ENetPeer* peer,
					   const std::vector<uint8_t>& messageData)
{
	// to be overriden by child classes
}

void NetworkHost::SendAll(const std::vector<uint8_t>& messageData)
{
	// Only applicable for server
}

ENetHost* NetworkHost::GetHost() const
{
	return m_Host;
}
