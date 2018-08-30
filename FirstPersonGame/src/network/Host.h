#pragma once
#include "ConnectionObject.h"
#include "..\utilities\smart_ptr_typedefs.h"
#include <thread>


class Host : public ConnectionObject
{
	//scoped local typedefs
	using thread = std::thread;

private:
	//fields
	bool isHosting = false;
	bool activeConnection = true;
	unsigned short port;

	//host fields
	sp<thread> listenThread;
	sf::TcpListener hostListener;
	bool stopListenThread = false;

	//helper fields
	short startId = 0;

private:
	void thread_listenForIncomingConnections();
	void handleNewClientReceived(sp<sf::TcpSocket>& newClient);
	short hostGrantNewID();
	void threadCloseCheck();

public:
	void hostOnPort(unsigned short targetPort);
	bool isConnectionActive();
	virtual void disconnect() override;
	virtual void sendPacket(sf::Packet packet, short sendIdOverride = -1) override {}
	virtual bool isActive() override { return true; throw std::runtime_error("not implemented"); }
public:
	Host();
	~Host();
};

