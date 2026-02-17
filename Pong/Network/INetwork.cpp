#include "pch.h"

#include "Network/INetwork.h"

#include <Core/Debug.h>

INetwork::INetwork(string hostTypeName)
	: m_host{ nullptr }, m_address{  }, m_hostTypeName{ std::move(hostTypeName) }
{

}

INetwork::~INetwork() = default;

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

void INetwork::Tick()
{
	// Read from the host service, if any events received, handle individually.
	ENetEvent event;
	if (enet_host_service(m_host, &event, 0) > 0)
	{
		switch (event.type)
		{
			// Either a new client host has connected to the server host or when an attempt to establish a
			// connection with a foreign host has succeeded. Only the "peer" field of the event structure is
			// valid for this event and contains the newly connected peer.
			case ENET_EVENT_TYPE_CONNECT:
			{
				OnClientConnect(event.peer);
				break;
			}
			// When a connected peer has either explicitly disconnected or timed out. Only the "peer" field of
			// the event structure is valid for this event and contains the peer that disconnected. Only the "data"
			// field of the peer is still valid on a disconnect event and must be explicitly reset.
			case ENET_EVENT_TYPE_DISCONNECT:
			{
				OnClientDisconnect(event.peer);
				break;
			}
			// The "peer" field contains the peer the packet was received from, "channelID" is the channel on
			// which the packet was sent, and "packet" is the packet that was sent. The packet contained in the
			// "packet" field must be destroyed with enet_packet_destroy() when you are done inspecting its contents.
			case ENET_EVENT_TYPE_RECEIVE:
			{
				OnReceivePacket(event.peer, event.packet);
				enet_packet_destroy(event.packet);
				break;
			}
			// No event occurred within the specified time limit.
			case ENET_EVENT_TYPE_NONE:
			{
				Debug::LogLine("None event received! This should not be possible!");
				break;
			}
		}
	}
}

void INetwork::OnClientConnect(ENetPeer* peer)
{}

void INetwork::OnReceivePacket(ENetPeer* peer, ENetPacket* packet)
{}

void INetwork::OnClientDisconnect(ENetPeer* peer)
{}

ENetAddress INetwork::CreateAddress()
{
	return { .host = 0, .port = 0 };
}