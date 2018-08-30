#pragma once
#include <SFML\Network.hpp>
class ConnectionObject
{
private:
protected:
public:
	virtual ~ConnectionObject() {}

	virtual void sendPacket(sf::Packet packet, short sendIdOverride = -1) = 0;
	virtual void disconnect() = 0;
	virtual bool isActive() = 0;
};

