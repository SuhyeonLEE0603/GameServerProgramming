#include "Server.h"

Server::Server()
{
    m_player_num = 0;

    std::wcout.imbue(std::locale("korean"));

    if (WSAStartup(MAKEWORD(2, 0), &m_wsa) != 0) {
        error_display("WSAStartup", WSAGetLastError());
        closesocket(m_client_socket);
    }

    m_server_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED);

    if (m_server_socket == INVALID_SOCKET) {
        error_display("WSASocket", WSAGetLastError());
        closesocket(m_client_socket);
    }

    m_server_addr.sin_family = AF_INET;
    m_server_addr.sin_port = PORT;
    m_server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
}

void Server::Init()
{
    if (bind(m_server_socket, reinterpret_cast<sockaddr*>(& m_server_addr), sizeof(m_server_addr)) == SOCKET_ERROR) {
        error_display("bind", WSAGetLastError());
        closesocket(m_client_socket);
    }

    if (listen(m_server_socket, SOMAXCONN) == SOCKET_ERROR) {
        error_display("listen", WSAGetLastError());
        closesocket(m_client_socket);
    }

}

SOCKET& Server::Accept()
{
    int addr_size = sizeof(m_server_addr);

    m_client_socket = WSAAccept(m_server_socket, reinterpret_cast<sockaddr*>(&m_server_addr), &addr_size, NULL, NULL);

    if (m_client_socket == SOCKET_ERROR) {
        error_display("WSAAccept", WSAGetLastError());
        closesocket(m_client_socket);
    }
    std::cout << "Client Accepted" << std::endl;

    return m_client_socket;
}

DWORD Server::Send(PacketType pt, void* packet)
{
    DWORD send_byte;
    wsabuf[0].buf = reinterpret_cast<char*>(&pt);
    wsabuf[0].len = sizeof(pt);
    wsabuf[1].buf = reinterpret_cast<char*>(packet);
    wsabuf[1].len = packet_size[pt];

    int res = WSASend(m_client_socket, wsabuf, 2, &send_byte, 0, 0, 0);
    
    if (0 != res) {
        error_display("WSASend", WSAGetLastError());
        closesocket(m_client_socket);
    }

	return send_byte;
}

DWORD Server::Recv()
{
    wsabuf[0].buf = reinterpret_cast<char*>(&pt);
    wsabuf[0].len = sizeof(pt);
    wsabuf[1].buf = buf;
    wsabuf[1].len = packet_size[pt];
    DWORD recv_flag = 0;
    DWORD recv_byte;

	int res = WSARecv(m_client_socket, wsabuf, 2, &recv_byte, &recv_flag, nullptr, nullptr);
    if (0 != res) {
        error_display("WSARecv", WSAGetLastError());
        closesocket(m_client_socket);
    }

    return recv_byte;
}

SOCKET& Server::GetClientSocket()
{
    return m_client_socket;
}

Server::~Server()
{
    std::cout << "Server Close" << std::endl;
    clients_sockets.clear();
    closesocket(m_server_socket);
    closesocket(m_client_socket);
    WSACleanup();
}
