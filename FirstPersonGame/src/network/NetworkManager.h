#pragma once
#include <string>
#include <SFML/Network.hpp>
#include "../utilities/smart_ptr_typedefs.h"
#include "Client.h"
#include "Host.h"
#include <iostream>

class NetworkManager final
{
	bool isHosting = true;
	sp<ConnectionObject> currentConnection = nullptr;

public:
	NetworkManager();
	~NetworkManager();

	void connectToHost(std::string ip, unsigned short port);

	void hostOnPort(unsigned short targetPort);

	
private:

};

