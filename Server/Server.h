#pragma once
#include "Headers.h"

const short SERVER_PORT = 4000;
const int BUFSIZE = 256;

class Server
{
public:
	vector<SOCKET> m_clients_socket;

	Server();
	void Init();
	bool Accept();
	DWORD Send(SOCKET client_socket);
	DWORD Recv(SOCKET client_socket);
	~Server();

private:

	int m_player_num;
	WSADATA m_wsa;
	SOCKET m_s_socket;
	SOCKADDR_IN m_server_addr;

};

