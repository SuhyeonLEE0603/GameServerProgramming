#include "Server.h"

void error_display(const char* msg, int err_no)
{
    WCHAR* lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, err_no,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<LPTSTR>(&lpMsgBuf), 0, NULL);
    std::cout << msg;
    std::wcout << L" 에러 " << lpMsgBuf << std::endl;
    while (true); // 디버깅용
    LocalFree(lpMsgBuf);
}

Server::Server()
{
    m_player_num = 0;

    std::wcout.imbue(std::locale("korean"));

    if (WSAStartup(MAKEWORD(2, 2), &m_wsa) != 0) {
        error_display("WSAStartup", WSAGetLastError());

    }

    m_server_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, 0);

    if (m_server_socket == INVALID_SOCKET) {
        error_display("WSASocket", WSAGetLastError());
    }

    DWORD optval = 1;

    setsockopt(m_server_socket, IPPROTO_TCP, TCP_NODELAY, (const char*)&optval, sizeof(optval));

    m_server_addr.sin_family = AF_INET;
    m_server_addr.sin_port = PORT;
    m_server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
}

void Server::Init()
{
    if (bind(m_server_socket, reinterpret_cast<sockaddr*>(& m_server_addr), sizeof(m_server_addr)) == SOCKET_ERROR) {
        error_display("bind", WSAGetLastError());
    }

    if (listen(m_server_socket, SOMAXCONN) == SOCKET_ERROR) {
        error_display("listen", WSAGetLastError());
    }

}

void Server::Accept()
{
    int addr_size = sizeof(m_server_addr);

    m_server_socket = WSAAccept(m_server_socket, reinterpret_cast<sockaddr*>(&m_server_addr), &addr_size, NULL, NULL);

    if (m_server_socket == SOCKET_ERROR) {
        error_display("WSAAccept", WSAGetLastError());
    }
}

DWORD Server::Send()
{
    DWORD send_byte;
    wsabuf[0].len = recv_byte;

    int res = WSASend(m_client_socket, &wsabuf[0], 1, &send_byte, 0, 0, 0);

    if (0 != res) {
        error_display("WSASend", WSAGetLastError());
    }

	return send_byte;
}

DWORD Server::Recv()
{
    char buf[BUFSIZE];
    wsabuf[0].buf = buf;
    wsabuf[0].len = BUFSIZE;

    DWORD recv_flag = 0;
    
	int res = WSARecv(m_client_socket, wsabuf, 1, &recv_byte, &recv_flag, nullptr, nullptr);
    if (0 != res) {
        error_display("WSARecv", WSAGetLastError());
    }

    return recv_byte;
}

Server::~Server()
{
    std::cout << "Server Close" << std::endl;
    closesocket(m_server_socket);
    closesocket(m_client_socket);
    WSACleanup();
}
