#pragma once
#include "Headers.h"
#include "Packet.h"

constexpr short PORT = 4000;
constexpr int BUFSIZE = 256;

class Server
{
public:
	//vector<SOCKET> m_clients_socket;
	char buf[BUFSIZE];

	Server();
	void Init();
	void Accept();
	DWORD Send(PacketType pt, void* packet);
	PacketType Recv();
	SOCKET GetClientSocket();
	void CloseServer();
	~Server();

private:
	WSABUF wsabuf[2];

	int m_player_num;
	WSADATA m_wsa;
	SOCKET m_server_socket;
	SOCKET m_client_socket;
	SOCKADDR_IN m_server_addr;

};

