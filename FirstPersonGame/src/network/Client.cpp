#include "Client.h"
#include <chrono>

// trust we will get an ID by design
void Client::thread_send()
{
	using namespace std::chrono_literals;

	while (needsIDFromNetwork)
	{
		std::this_thread::sleep_for(1s);

		if (stopThreads)
		{
			return;
		}
	}
	
	while (!stopThreads)
	{
		sp<sf::Packet> packet = sendQueue.dequeueCopy(); 

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
	if (!socket)
	{
		return;
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
				receiveQueue.enqueueCopy(packet);
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

Client::Client(short inID, sp<sf::TcpSocket> inSocket)
	: ID(inID), socket(inSocket)
{
	sendThread = sp<thread>(new thread(&Client::thread_send, this));
	receiveThread = sp<thread>(new thread(&Client::thread_receive, this));
}

Client::~Client()
{
	stopThreads = true;
	sendThread->join();
	receiveThread->join();
	socket->disconnect();
}
