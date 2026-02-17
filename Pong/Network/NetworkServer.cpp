#include "pch.h"

#include "NetworkServer.h"

NetworkServer::NetworkServer()
	: INetwork{ "server" }
{
}

ENetAddress NetworkServer::CreateAddress()
{
	return { ENET_HOST_ANY, 1234 };
}

ENetHost* NetworkServer::CreateHost(ENetAddress& address)
{
	return enet_host_create(
		&address,	/* The address to bind the server host to. */
		32,			/* Allow up th 32 clients and/or outgoing connections. */
		2,			/* Allow up to 2 channels to be used; 0 = reliable, 1 = unreliable. */
		0,			/* Assume any amount of incoming bandwidth. */
		0			/* Assume any amount of outgoing bandwidth. */
	);
}

void NetworkServer::OnReceivePacket(ENetPeer* peer, ENetPacket* packet)
{

}
