#pragma once
#pragma once
#include "TestBase.h"
#include <SFML/Network.hpp>
#include <thread>
#include "../network/NetworkManager.h"


class NetworkManagerConnectTest: public TestBase
{

public:

	NetworkManagerConnectTest() {}
	~NetworkManagerConnectTest() {}

	virtual bool run()
	{
		AutoLogger logger(_passedTest, "network connection");

		sf::IpAddress localAddress = sf::IpAddress::getLocalAddress();
		unsigned short port = 25565;

		NetworkManager host;
		host.hostOnPort(port);

		NetworkManager client;
		client.connectToHost(localAddress, port);

		_passedTest = false;
		return _passedTest;
	}

};

