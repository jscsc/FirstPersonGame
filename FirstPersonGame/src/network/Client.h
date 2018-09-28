#pragma once
#include "ConnectionObject.h"
#include "..\utilities\smart_ptr_typedefs.h"
#include <thread>
#include <SFML/Network.hpp>
#include "NetworkTypedefs.h"
#include "..\data_structures\ConcurrentQueue.h"

class Client : public ConnectionObject
{
	//scoped local typedefs
	using thread = std::thread;

private: 
	IdType ID;
	sp<sf::TcpSocket> socket;
	sf::IpAddress connectedIP;
	unsigned short connectedPort;

	// IO operations
	sp<thread> connectThread;
	void thread_connectToHost();
	sp<thread> sendThread;
	sp<thread> receiveThread;
	ConcurrentQueue<sf::Packet> sendQueue;
	ConcurrentQueue<sf::Packet> receiveQueue;
	void thread_send();
	void thread_receive();

	//state
	bool stopThreads = false;
	bool needsIDFromNetwork = false;
	bool isConnected = false;
	bool shouldAttemptConnect = false;

	void getIDFromPacket(sf::Packet& packet);

public:
	Client(sp<sf::TcpSocket> inSocket);
	Client(IdType inID, sp<sf::TcpSocket> inSocket);
	~Client();

	virtual bool isActive() override { return true; }
	virtual void disconnect() override  { throw std::runtime_error("not implemented"); }
	virtual void sendPacket(sf::Packet& packet, IdType sendToId= -1) override;
	void connect(const sf::IpAddress& ip, unsigned short port);
};

