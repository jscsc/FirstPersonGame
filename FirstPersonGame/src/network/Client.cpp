#include "Client.h"
#include <chrono>
#include <iostream>

void Client::thread_connectToHost()
{
	using namespace std::chrono_literals;

	while (!stopThreads)
	{
		if (shouldAttemptConnect)
		{
			if (socket)
			{
				if (socket->connect(connectedIP, connectedPort) == sf::Socket::Status::Done)
				{
					isConnected = true;
				}
			}
			shouldAttemptConnect = false;
		}
		else
		{
			std::this_thread::sleep_for(1s);
		}
	}
}

// trust we will get an ID by design
void Client::thread_send()
{
	using namespace std::chrono_literals;

	// process all waits at the same location
	while (!isConnected || needsIDFromNetwork)
	{
		std::this_thread::sleep_for(1s);

		if (stopThreads)
		{
			return;
		}
	}
	
	while (!stopThreads)
	{
		sp<sf::Packet> packet = sendQueue.dequeue(); 

		if (packet)
		{
			if (socket)
			{
				socket->send(*packet);
			}
		}
		else
		{
			std::this_thread::sleep_for(166ms); // one frame
		}

	}

}

void Client::thread_receive()
{
	using namespace std::chrono_literals;
	if (!socket)
	{
		stopThreads = true;
		return;
	}

	//process all waits here
	while (!isConnected)
	{
		std::this_thread::sleep_for(1s);
		if (stopThreads)
		{
			return;
		}
	}

	if (needsIDFromNetwork)
	{
		sf::Packet packet;
		socket->receive(packet);
		getIDFromPacket(packet);
	}
	

	sf::SocketSelector timeoutManager;
	timeoutManager.add(*socket);

	while (!stopThreads)
	{

		if (timeoutManager.wait(sf::seconds(1)))
		{
			if (timeoutManager.isReady(*socket))
			{
				sp<sf::Packet> packet = new_sp<sf::Packet>();
				socket->receive(*packet);
				receiveQueue.enqueue(packet);
			}
		}

	}
}

void Client::getIDFromPacket(sf::Packet& packet)
{
	packet >> ID;
	needsIDFromNetwork = false;
}

Client::Client(sp<sf::TcpSocket> inSocket)
: socket(inSocket)
{
	needsIDFromNetwork = true;

	sendThread = sp<thread>(new thread(&Client::thread_send, this));
	receiveThread = sp<thread>(new thread(&Client::thread_receive, this));
}

Client::Client(IdType inID, sp<sf::TcpSocket> inSocket)
	: ID(inID), socket(inSocket)
{
	needsIDFromNetwork = false;

	sendThread = sp<thread>(new thread(&Client::thread_send, this));
	receiveThread = sp<thread>(new thread(&Client::thread_receive, this));
}

Client::~Client()
{
	stopThreads = true;
	
	//join threads because all threads should be joined before dtor, otherwise crash.
	if (sendThread)
	{
		sendThread->join();
	}
	if (receiveThread)
	{
		receiveThread->join();
	}
	if (connectThread)
	{
		connectThread->join();
	}

	socket->disconnect();
}

void Client::sendPacket(sf::Packet& packet, IdType sendToId/*= -1*/)
{
	sp<sf::Packet> packetCopy = new_sp<sf::Packet>(packet);
	sendQueue.enqueue(packetCopy);
}

void Client::connect(const sf::IpAddress& ip, unsigned short port)
{
	if (isConnected)
	{
		//disconnect();
		std::cerr << "already connected " << std::endl;
		return;
	}

	isConnected = false;
	connectedIP = ip;
	connectedPort = port;

	//make sure this flag is set after the new ip and port is set.
	shouldAttemptConnect = true;

	if (!connectThread)
	{
		//only make a connect thread if one is not yet made
		connectThread = sp<std::thread>(new thread(&Client::thread_connectToHost, this));
	}
}
