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

    m_server_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, 0);

    if (m_server_socket == INVALID_SOCKET) {
        error_display("WSASocket", WSAGetLastError());
    }

    m_server_addr.sin_family = AF_INET;
    m_server_addr.sin_port = PORT;
    inet_pton(AF_INET, SERVER_ADDR, &m_server_addr.sin_addr);
}

void Client::Init()
{
    if (!WSAConnect(m_server_socket, reinterpret_cast<sockaddr*>(&m_server_socket), sizeof(m_server_socket), nullptr, nullptr, nullptr, nullptr)) {
        error_display("WSAConnect", WSAGetLastError());
    }
}

DWORD Client::Send()
{
    DWORD send_byte;
    wsabuf[0].buf = buf;
    wsabuf[0].len = sizeof(char);

    int res = WSASend(m_server_socket, &wsabuf[0], 1, &send_byte, 0, 0, 0);

    if (0 != res) {
        error_display("WSASend", WSAGetLastError());
    }

	return send_byte;
}

DWORD Client::Recv()
{
    wsabuf[0].buf = buf;
    wsabuf[0].len = sizeof(Pos);

    DWORD recv_flag = 0;
    
	int res = WSARecv(m_server_socket, wsabuf, 1, &recv_byte, &recv_flag, nullptr, nullptr);
    if (0 != res) {
        error_display("WSARecv", WSAGetLastError());
    }

    return recv_byte;
}

Client::~Client()
{
    std::cout << "Client Close" << std::endl;
    closesocket(m_server_socket);
    WSACleanup();
}
