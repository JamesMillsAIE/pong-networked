#pragma once

#include <Core/Common.h>

#include <enet/enet.h>

#include <string>

class INetwork
{
public:
	int32 Initialise();
	void Shutdown();

public:
	explicit INetwork(string hostTypeName);
	virtual ~INetwork();

protected:
	virtual ENetHost* CreateHost(ENetAddress& address) = 0;
	virtual ENetAddress CreateAddress();

private:
	ENetHost* m_host;
	ENetAddress m_address;

	string m_hostTypeName;

};