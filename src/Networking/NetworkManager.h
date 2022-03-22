#pragma once
#include "NetworkingTypes.h"
#include <vector>
#include <ctype.h>

class NetworkHost;

class NetworkManager
{
public:
	static NetworkManager& Get();

	NetworkManager(const NetworkManager&) = delete;
	NetworkManager(NetworkManager&&) = delete;
	NetworkManager& operator =(const NetworkManager&) = delete;
	NetworkManager& operator =(NetworkManager&&) = delete;


	NetworkErrorCode Init(NetworkHostType hostType);
	void Shutdown();
	void PollEvents();
	void Message(const std::vector<uint8_t>& messageData);

private:
	NetworkManager() = default;
	~NetworkManager() = default;

private:
	NetworkHost* m_Host = nullptr;
};
