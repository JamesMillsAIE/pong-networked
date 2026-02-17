#include "pch.h"

#include "Network/INetwork.h"

#include <Core/Debug.h>

int32 INetwork::Initialise()
{
	// Attempt to initialise the network system, printing a message if something failed
	if (enet_initialize() != 0)
	{
		Debug::LogLine("An error occurred while initializing ENet.");
		return NetworkFailedToInitialise;
	}

	// Attempt to create the host and address
	m_address = CreateAddress();
	m_host = CreateHost(m_address);

	// Validate the host
	if (m_host == nullptr)
	{
		// Create a buffer
		constexpr uint8 bufferSize = 128;
		int8 buffer[bufferSize];

		// Create a formatted message using the host name type and log it
		(void)sprintf_s(
			buffer, 
			bufferSize, 
			"An error occurred when while trying to create an ENet %s host.", 
			m_hostTypeName.c_str()
		);
		Debug::LogLine(buffer);

		// Invalidate the host and return an error code
		m_host = nullptr;
		return NetworkHostCreateFailed;
	}

	return EXIT_SUCCESS;
}

void INetwork::Shutdown()
{
	// If the host is valid, destroy it and invalidate
	if (m_host != nullptr)
	{
		enet_host_destroy(m_host);
		m_host = nullptr;
	}

	// Shut down the enet system
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