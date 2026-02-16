#include "Network/INetwork.h"

#include <Core/Debug.h>

int32 INetwork::Initialise()
{
	if (enet_initialize() != 0)
	{
		Debug::LogLine("An error occurred while initializing ENet.");
		return NetworkFailedToInitialise;
	}

	m_address = CreateAddress();
	m_host = CreateHost(m_address);

	if (m_host == nullptr)
	{
		constexpr int bufferSize = 128;
		char buffer[bufferSize];

		(void)sprintf_s(
			buffer, 
			bufferSize, 
			"An error occurred when while trying to create an ENet %s host.", 
			m_hostTypeName.c_str()
		);

		Debug::LogLine(buffer);

		m_host = nullptr;
		return NetworkHostCreateFailed;
	}

	return EXIT_SUCCESS;
}

void INetwork::Shutdown()
{
	if (m_host != nullptr)
	{
		enet_host_destroy(m_host);
		m_host = nullptr;
	}

	enet_deinitialize();
}

INetwork::INetwork(string hostTypeName)
	: m_host{ nullptr }, m_address{  }, m_hostTypeName{ std::move(hostTypeName) }
{

}

INetwork::~INetwork() = default;

ENetAddress INetwork::CreateAddress()
{
	return { .host = 0, .port = 0 };
}