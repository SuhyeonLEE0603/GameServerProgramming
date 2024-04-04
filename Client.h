#pragma once
#include "stdafx.h"
#include "Packet.h"
#include "King.h"

constexpr short PORT = 4000;
constexpr int BUFSIZE = 256;
constexpr char SERVER_ADDR[] = "127.0.0.1";

class Client
{
public:
	Client();
	bool Init();
	void Send(PacketType pt, void* packet);
	void SetWSABuf1();
	void SetWSABuf2();
	errno_t KeyProcess(WPARAM&);
	SOCKET& GetSock();
	WSAOVERLAPPED& GetOver();
	WSABUF& GetWSABuf();
	PacketType GetPacketType() const;
	~Client();

	char buf[BUFSIZE];
	WSABUF wsabuf[2];

	int g_x, g_y, g_id;

private:
	PacketType pt{};

	WSAOVERLAPPED m_wsaover;
	WSADATA m_wsa;
	SOCKET m_server_socket;
	SOCKADDR_IN m_server_addr;

};

Client g_client_s;
extern King king;