#pragma once
#include "ConnectionObject.h"
#include "NetworkTypedefs.h"
#include "..\utilities\smart_ptr_typedefs.h"
#include "..\utilities\datastructure_typedefs.h"
#include <thread>

class Client;

class Host : public ConnectionObject
{
	//scoped local typedefs
	using thread = std::thread;
	using IdType = short;

private:
	//fields
	bool isHosting = false;
	bool activeConnection = false;
	unsigned short port;
	HashMap< IdType, sp<Client> > clients;

	//host fields
	sp<thread> listenThread;
	sf::TcpListener hostListener;
	bool stopListenThread = false;

	//helper fields
	IdType startId = 0;

private:
	void thread_listenForIncomingConnections();
	void handleNewClientReceived(sp<sf::TcpSocket>& newClient);
	IdType hostGrantNewID();
	void threadCloseCheck();

public:
	void hostOnPort(unsigned short targetPort);
	bool isConnectionActive();
	virtual void disconnect() override;
	virtual void sendPacket(sf::Packet& packet, IdType sendToId = -1) override {}
	virtual bool isActive() override { return true; throw std::runtime_error("not implemented"); }
public:
	Host();
	~Host();
};

