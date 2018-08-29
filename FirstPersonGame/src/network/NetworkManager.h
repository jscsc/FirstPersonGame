#pragma once
#include <string>
#include <SFML/Network.hpp>

class NetworkManager final
{
	bool _IsHosting = false;
	bool _activeConnection = true;
	unsigned short _port;

	//host fields
	sf::TcpListener hostListener;
	bool _stopListenThread;

public:
	NetworkManager();
	~NetworkManager();

	void thread_listenForIncomingConnections()
	{
		//allow timeouts using the selector class
		hostListener.setBlocking(false);
		sf::SocketSelector selector;
		selector.add(hostListener);

		//keep listening for new connections in this thread
		while (true)
		{
			//does not block when setBlocking(false)
			hostListener.listen(_port);

			//wait on accept (ie block this thread)
			if (selector.wait(sf::seconds(1)))
			{
				if (selector.isReady(hostListener))
				{
					//connect a client
				}
			}

			//check if there is a pending shutdown
			if (_stopListenThread)
			{
				hostListener.close();
				_stopListenThread = false;
				threadCloseCheck();
				break;
			}
		}
	}

	void threadCloseCheck()
	{

	}

	void disconnect()
	{
		//TODO - make a test for this
	}

	bool isConnectionActive()
	{
		return _activeConnection;
	}

	void hostOnPort(unsigned short port)
	{
		// ignore if already hosting on this port
		if (isConnectionActive() && _IsHosting && _port == port)
		{
			return;
		}

		//disconnect if hosting/joined on another port
		if (isConnectionActive() && (_port != port))
		{
			//disconnect before connecting
			disconnect();
		}
		
		_IsHosting = true;
		_port = port;
		_activeConnection = true;

		//start listening thread
		
		
	}

	void connectToHost(std::string ip, unsigned short port)
	{

	}

private:

};

