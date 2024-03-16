#pragma once
#include "Headers.h"

constexpr short PORT = 4000;
constexpr int BUFSIZE = 256;
constexpr char SERVER_ADDR[] = "127.0.0.1";

class Client
{
public:
	//vector<SOCKET> m_clients_socket;

	Client();
	void Init();
	void Accept();
	DWORD Send();
	DWORD Recv();
	~Client();

	char buf[BUFSIZE];

private:
	WSABUF wsabuf[1];

	int m_player_num;
	WSADATA m_wsa;
	SOCKET m_client_socket;
	SOCKADDR_IN m_client_addr;
	DWORD recv_byte;

};

