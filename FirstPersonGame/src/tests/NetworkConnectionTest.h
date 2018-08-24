#pragma once
#include "TestBase.h"
#include <SFML/Network.hpp>
#include <thread>


class NetworkConnectionTest : public TestBase
{

public:

	NetworkConnectionTest(){}
	~NetworkConnectionTest(){}

	static void runHost(bool* passed)
	{

		sf::TcpListener hostListener;
		*passed = true;

		if (hostListener.listen(53000) != sf::Socket::Done)
		{
			*passed = false;
			return;
		}

		sf::TcpSocket clientSocket;
		if (hostListener.accept(clientSocket) != sf::Socket::Done)
		{
			*passed = false;
			return;
		}

		sf::Packet recievePacket;
		clientSocket.receive(recievePacket);

		sf::Uint16 x;
		recievePacket >> x;
		if (x != 10)
		{
			*passed = false;
		}

		std::string s = "hello";
		double d = 0.6;
		sf::Packet sendPacket;
		sendPacket << s << d;

		clientSocket.send(sendPacket);
	}

	static void runClient(bool* passed)
	{
		*passed = true;

		sf::TcpSocket hostSocket;
		sf::IpAddress localAddress = sf::IpAddress::getLocalAddress();
		sf::Socket::Status status = hostSocket.connect(localAddress, 53000);

		if (status != sf::Socket::Done)
		{
			*passed = false;
			return;
		}

		sf::Uint16 x = 10;
		sf::Packet sendPacket;
		sendPacket << x;
		hostSocket.send(sendPacket);

		std::string s;
		double d;
		sf::Packet receivePacket;
		hostSocket.receive(receivePacket);
		receivePacket >> s >> d;

		// floats/doubles *should* be exact bits
		if (s != "hello" || d != 0.6)
		{
			*passed = false;
		}

	}

	virtual bool run()
	{
		AutoLogger logger(_passedTest, "network connection");


		bool hostPassed = false;
		bool clientPassed = false;

		std::thread hostThread(&NetworkConnectionTest::runHost, &hostPassed);
		std::thread clientThread(&NetworkConnectionTest::runClient, &clientPassed);

		hostThread.join();
		clientThread.join();

		_passedTest = hostPassed && clientPassed;

		return _passedTest;
	}

};

