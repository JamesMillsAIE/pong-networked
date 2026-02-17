#pragma once

#include "INetwork.h"

/**
 * The server side implementation of the network.
 * Used for the server application.
 */
class NetworkServer : public INetwork
{
public:
	NetworkServer();

protected:
	/**
	 * Creates a sided implementation of the ENetHost. This is abstract
	 * and MUST be implemented.
	 * @param address The network address to connect to.
	 */
	ENetHost* CreateHost(ENetAddress& address) override;

	/**
	 * Constructs and returns the network address used when creating the host.
	 * @return The ENetAddress to bind or connect to.
	 */
	ENetAddress CreateAddress() override;

	/**
	 * Called when a packet is received from a remote peer.
	 * @param peer The peer that sent the packet.
	 * @param packet The packet containing the received data.
	 */
	void OnReceivePacket(ENetPeer* peer, ENetPacket* packet) override;

};