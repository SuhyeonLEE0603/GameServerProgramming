#pragma once
#include "../Packet.h"
#include "Player.h"

constexpr int BUFSIZE = 256;
std::unordered_map<int, Session> clients_sockets;

class Session {
private:
	int m_id;
	int x, y;

	PacketType pt;
	WSABUF m_recv_wsabuf[2];
	WSABUF m_send_wsabuf[2];
	WSAOVERLAPPED m_recv_over;
	SOCKET m_socket;

	Player player;
public:
	char m_recv_buf[BUFSIZE];

	Session();
	Session(int, SOCKET);
	~Session() { closesocket(m_socket); }

	void Send(PacketType pt, void* packet);
	void do_recv();

	void SetId(int id) { m_id = id; }
	void Process();

};