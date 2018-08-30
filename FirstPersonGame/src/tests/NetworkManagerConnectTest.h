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

		NetworkManager host;
		host.hostOnPort(25565);

		NetworkManager client;
		client.connectToHost("125.125.125.125", 25565);

		_passedTest = false;
		return _passedTest;
	}

};

