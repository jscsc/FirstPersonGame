#pragma once
#include "ConnectionObject.h"
#include "..\utilities\smart_ptr_typedefs.h"
#include <thread>
#include <SFML/Network.hpp>
#include "..\data_structures\ConcurrentQueue.h"

class Client : public ConnectionObject
{

	//scoped local typedefs
	using thread = std::thread;

private: 
	short ID;
	sp<sf::TcpSocket> socket;
	sp<thread> sendThread;
	sp<thread> receiveThread;

	ConcurrentQueue<sf::Packet> sendQueue;
	ConcurrentQueue<sf::Packet> receiveQueue;

	bool stopThreads = false;
	bool needsIDFromNetwork = false;

	void thread_send();
	void thread_receive();

	void getIDFromPacket(sf::Packet& packet);

public:
	Client(sp<sf::TcpSocket> inSocket);
	Client(short inID, sp<sf::TcpSocket> inSocket);
	~Client();

	virtual bool isActive() override { return true; }
	virtual void disconnect() override  { throw std::runtime_error("not implemented"); }
	virtual void sendPacket(sf::Packet packet, short sendIdOverride = -1) override {}
};

