#pragma once
#include "Headers.h"

constexpr short PORT = 4000;
constexpr int BUFSIZE = 256;

class Server
{
public:
	//vector<SOCKET> m_clients_socket;

	Server();
	void Init();
	void Accept();
	DWORD Send();
	DWORD Recv();
	~Server();

private:
	WSABUF wsabuf[1];

	int m_player_num;
	WSADATA m_wsa;
	SOCKET m_server_socket;
	SOCKET m_client_socket;
	SOCKADDR_IN m_server_addr;
	DWORD recv_byte;

};

