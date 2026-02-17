#pragma once

#include "INetwork.h"

class NetworkClient : public INetwork
{
public:
	NetworkClient();

protected:
	ENetHost* CreateHost(ENetAddress& address) override;
	ENetAddress CreateAddress() override;

};