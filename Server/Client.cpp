#include "Client.h"

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

Client::Client()
{
    m_player_num = 0;

    std::wcout.imbue(std::locale("korean"));

    if (WSAStartup(MAKEWORD(2, 2), &m_wsa) != 0) {
        error_display("WSAStartup", WSAGetLastError());
    }

    m_client_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, 0);

    if (m_client_socket == INVALID_SOCKET) {
        error_display("WSASocket", WSAGetLastError());
    }

    m_client_addr.sin_family = AF_INET;
    m_client_addr.sin_port = PORT;
    inet_pton(AF_INET, SERVER_ADDR, &m_client_addr.sin_addr);

}

void Client::Init()
{
    if (bind(m_client_socket, reinterpret_cast<sockaddr*>(& m_client_addr), sizeof(m_client_addr)) == SOCKET_ERROR) {
        error_display("bind", WSAGetLastError());
    }

    if (listen(m_client_socket, SOMAXCONN) == SOCKET_ERROR) {
        error_display("listen", WSAGetLastError());
    }

}

void Client::Accept()
{
    int addr_size = sizeof(m_client_addr);

    m_client_socket = WSAAccept(m_client_socket, reinterpret_cast<sockaddr*>(&m_client_addr), &addr_size, NULL, NULL);

    if (m_client_socket == SOCKET_ERROR) {
        error_display("WSAAccept", WSAGetLastError());
    }
}

DWORD Client::Send()
{
    DWORD send_byte;
    wsabuf[0].len = recv_byte;

    int res = WSASend(m_client_socket, &wsabuf[0], 1, &send_byte, 0, 0, 0);

    if (0 != res) {
        error_display("WSASend", WSAGetLastError());
    }

	return send_byte;
}

DWORD Client::Recv()
{
    wsabuf[0].buf = buf;
    wsabuf[0].len = BUFSIZE;

    DWORD recv_flag = 0;
    
	int res = WSARecv(m_client_socket, wsabuf, 1, &recv_byte, &recv_flag, nullptr, nullptr);
    if (0 != res) {
        error_display("WSARecv", WSAGetLastError());
    }

    return recv_byte;
}

Client::~Client()
{
    std::cout << "Client Close" << std::endl;
    closesocket(m_client_socket);
    closesocket(m_client_socket);
    WSACleanup();
}
