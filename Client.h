#pragma once
#include "stdafx.h"
#include "Packet.h"

constexpr short PORT = 4000;
constexpr int BUFSIZE = 256;
constexpr char SERVER_ADDR[] = "127.0.0.1";

class Client
{
public:
	//vector<SOCKET> m_clients_socket;

	Client();
	bool Init();
	DWORD Send(PacketType pt, void* packet);
	PacketType Recv();
	SOCKET GetServerSocket();
	void CloseClient();
	~Client();

	char buf[BUFSIZE];

private:
	WSABUF wsabuf[2];

	WSADATA m_wsa;
	SOCKET m_server_socket;
	SOCKADDR_IN m_server_addr;

};

