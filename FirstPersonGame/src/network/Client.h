#pragma once
#include "ConnectionObject.h"
class Client : public ConnectionObject
{
private: 
	//ID
	//TCP socket
	//WriteThread
	//ReadThread

	//WritePacketQueue
	//ReceivedPacketQueue
public:
	Client();
	~Client();

	virtual bool isActive() override { return true; }
	virtual void disconnect() override  { throw std::runtime_error("not implemented"); }
	virtual void sendPacket(sf::Packet packet, short sendIdOverride = -1) override {}
};

