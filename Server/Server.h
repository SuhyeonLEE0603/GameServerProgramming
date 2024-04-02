#pragma once
#include "Headers.h"
#include "Session.h"
#include "../Packet.h"

constexpr short PORT = 4000;
constexpr int BUFSIZE = 256;

class Server
{
public:
	char buf[BUFSIZE];
	PacketType pt{};

	Server();
	void Init();
	SOCKET& Accept();
	DWORD Send(PacketType pt, void* packet);
	DWORD Recv();
	SOCKET& GetClientSocket();
	~Server();

private:
	WSABUF wsabuf[2];

	int m_player_num;
	WSADATA m_wsa;
	SOCKET m_server_socket;
	SOCKET m_client_socket;
	SOCKADDR_IN m_server_addr;

};

std::unordered_map<int, Session> clients_sockets;
