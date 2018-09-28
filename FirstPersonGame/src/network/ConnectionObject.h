#pragma once
#include <SFML\Network.hpp>
#include "NetworkTypedefs.h"

class ConnectionObject
{
private:
protected:
public:
	virtual ~ConnectionObject() {}

	virtual void sendPacket(sf::Packet& packet, IdType sendToId= -1) = 0;
	virtual void disconnect() = 0;
	virtual bool isActive() = 0;
};

