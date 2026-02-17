#pragma once

#include <Core/Common.h>

#include <enet/enet.h>

#include <string>

/**
 * A base class for the network system, handles most base functionality, but
 * is abstract for creating the sided host.
 */
class INetwork
{
public:
	/**
	 * @param hostTypeName This is simply used for logging purposes.
	 */
	explicit INetwork(string hostTypeName);
	virtual ~INetwork();

public:
	/**
	 * Attempts to initialise enet and create the relevant variables.
	 * @return The success state of the initialisation.
	 */
	int32 Initialise();

	/** Attempt to shut down enet, destroying the host if possible. */
	void Shutdown();

	/** Run the network processing loop for a frame. */
	void Tick();

protected:
	/**
	 * Creates a sided implementation of the ENetHost. This is abstract
	 * and MUST be implemented.
	 * @param address The network address to connect to.
	 */
	virtual ENetHost* CreateHost(ENetAddress& address) = 0;

	/**
	 * Constructs and returns the network address used when creating the host.
	 * @return The ENetAddress to bind or connect to.
	 */
	virtual ENetAddress CreateAddress();

	/**
	 * Called when a remote client successfully connects to the host.
	 * @param peer The peer representing the newly connected client.
	 */
	virtual void OnClientConnect(ENetPeer* peer);

	/**
	 * Called when a packet is received from a remote peer.
	 * @param peer The peer that sent the packet.
	 * @param packet The packet containing the received data.
	 */
	virtual void OnReceivePacket(ENetPeer* peer, ENetPacket* packet);

	/**
	 * Called when a remote client disconnects or times out from the host.
	 * @param peer The peer representing the disconnected client.
	 */
	virtual void OnClientDisconnect(ENetPeer* peer);

private:
	ENetHost* m_host; /**< The ENet host instance managing all peer connections. */
	ENetAddress m_address; /**< The network address the host is bound to or connecting from. */
	string m_hostTypeName; /**< This is simply used for logging purposes. */

};