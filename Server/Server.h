#pragma once
#include "Headers.h"
#include "Session.h"
#include "../Packet.h"

constexpr short PORT = 4000;
constexpr int BUFSIZE = 256;

class Server
{
public:
	Server();
	void Init();
	SOCKET& Accept();
	~Server();

private:

	WSADATA m_wsa;
	SOCKET m_server_socket;
	SOCKET m_client_socket;
	SOCKADDR_IN m_server_addr;

};
