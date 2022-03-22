#include "NetworkManager.h"

#define ENET_IMPLEMENTATION
#include <enet.h>

#include "Client/NetworkClient.h"
#include "Server/NetworkServer.h"

NetworkManager& NetworkManager::Get()
{
	static NetworkManager instance;
	return instance;
}

NetworkErrorCode NetworkManager::Init(NetworkHostType hostType)
{
	if(enet_initialize() != 0)
	{
		return NetworkErrorCode::ENET_INIT_ERROR;
	}

	switch(hostType)
	{
	case NetworkHostType::ENET_HOST_CLIENT: {
		m_Host = new NetworkClient();
		break;
	}
	case NetworkHostType::ENET_HOST_SERVER: {
		m_Host = new NetworkServer();
		break;
	}
	default:
		break;
	}

	if (m_Host)
	{
		return m_Host->Init();
	}

	return NetworkErrorCode::ENET_INVALID_HOST_TYPE_ERROR;
}

void NetworkManager::Shutdown()
{
	m_Host->Destroy();
	delete m_Host;

	enet_deinitialize();
}

void NetworkManager::PollEvents()
{
	if (!m_Host->IsInitialized())
	{
		return;
	}

	ENetEvent event;

	while(enet_host_service(m_Host->GetHost(), &event, 0) > 0)
	{
		m_Host->ProcessEvents(event);
	}
}

void NetworkManager::Message(const std::vector<uint8_t>& messageData)
{
	m_Host->Send(messageData);
}
