#include "pch.h"
#include "NetworkClient.h"

NetworkClient::NetworkClient()
	: INetwork{ "client" }
{}

ENetHost* NetworkClient::CreateHost(ENetAddress& address)
{
	return enet_host_create(
		nullptr,	/* Create a client host. */
		1,			/* Only allow 1 outgoing connection. */
		2,			/* Allow up to 2 channels to be used; 0 = reliable, 1 = unreliable. */
		0,			/* Assume any amount of incoming bandwidth. */
		0			/* Assume any amount of outgoing bandwidth. */
	);
}

ENetAddress NetworkClient::CreateAddress()
{
	return { 0, 0 };
}
