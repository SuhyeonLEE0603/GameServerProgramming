#include "Server.h"

Server::Server()
{
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

Server::~Server()
{
    std::cout << "Server Close" << std::endl;
    clients_sockets.clear();
    closesocket(m_server_socket);
    closesocket(m_client_socket);
    WSACleanup();
}
