#include "Host.h"



void Host::thread_listenForIncomingConnections()
{
	using sf::TcpSocket;

	//allow timeouts using the selector class
	hostListener.setBlocking(false);
	sf::SocketSelector selector;
	selector.add(hostListener);

	//does not block when setBlocking(false)
	hostListener.listen(port);

	//keep listening for new connections in this thread
	while (true)
	{
		//wait on accept (ie block this thread); return true means inbound request
		if (selector.wait(sf::seconds(1)))
		{
			if (selector.isReady(hostListener))
			{
				//connect a client
				sp<TcpSocket> newClient = new_sp<TcpSocket>();
				hostListener.accept(*newClient);
				handleNewClientReceived(newClient);

				//restart the listening process
				hostListener.listen(port);
			}
		}

		//check if there is a pending shutdown
		if (stopListenThread)
		{
			hostListener.close();
			stopListenThread = false;
			threadCloseCheck();
			break;
		}
	}
}

void Host::handleNewClientReceived(sp<sf::TcpSocket>& newClient)
{
	//assign an id
	short newId = hostGrantNewID();

	//create a client that will:
		//start a write thread
		//start a read thread
		//send newid over the write thread as the first message so client knows its id.

	//this should store the new client in a container
		//perhaps a hashmap/bst(map) keyed on id?
}

short Host::hostGrantNewID()
{
	//TODO: add a pool of IDs to get from first because people may disconnect from the server
	return startId++;
}

void Host::threadCloseCheck()
{

}

void Host::disconnect()
{
	//TODO - make a test for this
}

bool Host::isConnectionActive()
{
	return activeConnection;
}

void Host::hostOnPort(unsigned short targetPort)
{
	// ignore if already hosting on this port
	if (isConnectionActive() && isHosting && port == targetPort)
	{
		return;
	}

	//disconnect if hosting/joined on another port
	if (isConnectionActive() && (port != targetPort))
	{
		//disconnect before connecting
		disconnect();
	}

	isHosting = true;
	port = targetPort;
	activeConnection = true;
	stopListenThread = false;

	//start listening thread
	listenThread = sp<thread>(new thread(&Host::thread_listenForIncomingConnections, this));
}

Host::Host()
{
}

Host::~Host()
{
	//this call will block
	//thus, we want to make sure the thread is already closed before we destory this object
	stopListenThread = true;
	listenThread->join();
}
