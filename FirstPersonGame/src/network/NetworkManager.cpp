#include "NetworkManager.h"
#include <xutility>



NetworkManager::NetworkManager()
{
}


NetworkManager::~NetworkManager()
{
}

void NetworkManager::connectToHost(std::string ip, unsigned short port)
{
	sp<sf::TcpSocket> socket = new_sp<sf::TcpSocket>();
	//sp<Client> client = new_sp<Client>(std::move(socket));

}

void NetworkManager::hostOnPort(unsigned short targetPort)
{
	//if there isn't a current connection, then host
	if (!currentConnection || !currentConnection->isActive())
	{
		sp<Host> host = new_sp<Host>();
		host->hostOnPort(targetPort);
		isHosting = true;
		currentConnection = host;
	}
	else
	{
		std::cerr << "attempt to connect but already connected, please disconnect first" << std::endl;
	}
}
