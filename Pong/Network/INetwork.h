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
	 *
	 * @param address
	 * @return
	 */
	virtual ENetHost* CreateHost(ENetAddress& address) = 0;

	/**
	 * 
	 * @return 
	 */
	virtual ENetAddress CreateAddress();

	/**
	 * 
	 * @param peer 
	 */
	virtual void OnClientConnect(ENetPeer* peer);

	/**
	 * 
	 * @param peer 
	 * @param packet 
	 */
	virtual void OnReceivePacket(ENetPeer* peer, ENetPacket* packet);

	/**
	 * 
	 * @param peer 
	 */
	virtual void OnClientDisconnect(ENetPeer* peer);

private:
	ENetHost* m_host; /**< . */
	ENetAddress m_address; /**< . */
	string m_hostTypeName; /**< This is simply used for logging purposes. */

};