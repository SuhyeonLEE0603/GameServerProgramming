#pragma once
#include "../Packet.h"
#include "Player.h"

void CALLBACK send_callback(DWORD err, DWORD num_bytes, LPWSAOVERLAPPED send_over, DWORD recv_flag)
{
	int s_id = reinterpret_cast<int>(send_over->hEvent);
	clients_sockets[s_id].do_recv();
}
void CALLBACK recv_callback(DWORD err, DWORD num_bytes, LPWSAOVERLAPPED recv_over, DWORD recv_flag)
{
	int s_id = reinterpret_cast<int>(recv_over->hEvent);

	clients_sockets[s_id].SetId(s_id);
	clients_sockets[s_id].Process();
}

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

	Session() {
		std::cout << "Unexpected Constructor Call Error!\n";
		exit(-1);
	}

	Session(int id, SOCKET s) : m_id(id), m_socket(s) {
		m_recv_wsabuf[0].buf = reinterpret_cast<char*>(&pt);
		m_recv_wsabuf[0].len = sizeof(pt);
		m_recv_wsabuf[1].buf = m_recv_buf;
		m_recv_wsabuf[1].len = packet_size[pt];
	}

	~Session() { closesocket(m_socket); }

	void Send(PacketType pt, void* packet)
	{
		m_send_wsabuf[0].buf = reinterpret_cast<char*>(&pt);
		m_send_wsabuf[0].len = sizeof(pt);
		m_send_wsabuf[1].buf = reinterpret_cast<char*>(packet);
		m_send_wsabuf[1].len = packet_size[pt];

		ZeroMemory(&m_recv_over, sizeof(m_recv_over));
		m_recv_over.hEvent = reinterpret_cast<HANDLE>(m_id);

		int res = WSASend(m_socket, m_send_wsabuf, 2, 0, 0, &m_recv_over, send_callback);
		if (0 != res) {
			error_display("WSASend", WSAGetLastError());
			closesocket(m_socket);
		}
	}

	void do_recv() {
		DWORD recv_flag = 0;
		ZeroMemory(&m_recv_over, sizeof(m_recv_over));
		m_recv_over.hEvent = reinterpret_cast<HANDLE>(m_id);
		WSARecv(m_socket, m_recv_wsabuf, 2, 0, &recv_flag, &m_recv_over, recv_callback);
	}

	void SetId(int id)
	{
		m_id = id;
	}

	void Process()
	{
		if (pt == WindowSize) {

			x = *reinterpret_cast<int*>(&m_recv_buf[0]);
			y = *reinterpret_cast<int*>(&m_recv_buf[4]);

			std::cout << "Recv WindowSize : " << x << ", " << y << std::endl;
		}
		else if (pt == KeyInput) {
			PacketKeyInput key;

			key.id = m_id;
			key.key = m_recv_buf[4];

			switch (key.key)
			{
			case VK_LEFT:
				std::cout << "Go Left" << std::endl;
				player.Move(-(x / 8), 0);
				break;
			case VK_RIGHT:
				std::cout << "Go Right" << std::endl;
				player.Move(x / 8, 0);
				break;
			case VK_UP:
				std::cout << "Go Up" << std::endl;
				player.Move(0, -(y / 8));
				break;
			case VK_DOWN:
				std::cout << "Go Down" << std::endl;
				player.Move(0, y / 8);
				break;
			}
			PacketType packet = PlayerPos;
			PacketPos pos;

			pos.id = m_id;
			pos.pos_x = player.pos.x;
			pos.pos_y = player.pos.y;

			Send(packet, (void*)&pos);
		}
	}
};