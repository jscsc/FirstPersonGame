#include "Client.h"
#include <chrono>

// trust we will get an ID by design
void Client::thread_writingThread()
{
	using namespace std::chrono_literals;

	while (needsIDFromNetwork)
	{
		std::this_thread::sleep_for(1s);
	}
	
	while (true)
	{
		sp<sf::Packet> packet = writeQueue.dequeueCopy(); 

		if (packet)
		{
			if (socket)
			{
				socket->send(*packet);
			}
		}
		else
		{
			std::this_thread::sleep_for(166ms);
		}

		if (stopThreads)
		{
			break;
		}

	}

}

void Client::thread_readingThread()
{
	// wait for ID if flag true
	
	// while not shutdown:
	//  listen for incoming packet (use selector to sleep for X time)
	//  store packet in queue
	//  check for shutdown
}

Client::Client(sp<sf::TcpSocket> inSocket)
: socket(inSocket)
{
	needsIDFromNetwork = true;

	writeThread = sp<thread>(new thread(&Client::thread_writingThread, this));
	readThread = sp<thread>(new thread(&Client::thread_readingThread, this));
}

Client::Client(short inID, sp<sf::TcpSocket> inSocket)
	: ID(inID), socket(inSocket)
{
	writeThread = sp<thread>(new thread(&Client::thread_writingThread, this));
	readThread = sp<thread>(new thread(&Client::thread_readingThread, this));
}

Client::~Client()
{
	stopThreads = true;
	writeThread->join();
	readThread->join();
	socket->disconnect();
}
