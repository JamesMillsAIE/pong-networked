#pragma once

#include "INetwork.h"

class NetworkServer : public INetwork
{
public:
	NetworkServer();

protected:
	ENetAddress CreateAddress() override;
	ENetHost* CreateHost(ENetAddress& address) override;

};