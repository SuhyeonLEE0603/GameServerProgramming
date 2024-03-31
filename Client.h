#pragma once
#include "stdafx.h"
#include "Packet.h"

constexpr short PORT = 4000;
constexpr int BUFSIZE = 256;
constexpr char SERVER_ADDR[] = "127.0.0.1";

class Client
{
public:
	Client();
	bool Init();
	void Send(PacketType pt, void* packet);
	void SetRecv();
	errno_t KeyProcess(WPARAM&);
	SOCKET& GetSock();
	WSAOVERLAPPED& GetOver();
	WSABUF& GetWSABuf();
	~Client();

	char buf[BUFSIZE];

private:
	PacketType pt{};

	WSAOVERLAPPED m_wsaover;
	WSABUF wsabuf[2];
	WSADATA m_wsa;
	SOCKET m_server_socket;
	SOCKADDR_IN m_server_addr;

};

extern Client g_client_s;
extern int g_x, g_y;