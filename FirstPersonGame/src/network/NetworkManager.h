#pragma once
#include <string>
#include <SFML/Network.hpp>
#include "../utilities/smart_ptr_typedefs.h"
#include "Client.h"
#include "Host.h"
#include <iostream>

class NetworkManager final //maybe not best name? this switches between being able host and join as client
{
	bool isHosting = true;
	sp<ConnectionObject> currentConnection = nullptr;

public:
	NetworkManager();
	~NetworkManager();

	void connectToHost(const sf::IpAddress& ip, unsigned short port);

	void hostOnPort(unsigned short targetPort);

	
private:

};

