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
    std::wcout.imbue(std::locale("korean"));

    if (WSAStartup(MAKEWORD(2, 2), &m_wsa) != 0) {
        error_display("WSAStartup", WSAGetLastError());
        closesocket(m_server_socket);
    }

    m_server_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, 0);

    if (m_server_socket == INVALID_SOCKET) {
        error_display("WSASocket", WSAGetLastError());
        closesocket(m_server_socket);
    }

    m_server_addr.sin_family = AF_INET;
    m_server_addr.sin_port = PORT;
    inet_pton(AF_INET, SERVER_ADDR, &m_server_addr.sin_addr);
}

bool Client::Init()
{
    return SOCKET_ERROR != connect(m_server_socket, reinterpret_cast<sockaddr*>(&m_server_addr), sizeof(m_server_addr));
}

DWORD Client::Send(PacketType pt, void* packet)
{
    DWORD send_byte;
    wsabuf[0].buf = reinterpret_cast<char*>(&pt);
    wsabuf[0].len = sizeof(pt);
    wsabuf[1].buf = reinterpret_cast<char*>(packet);
    wsabuf[1].len = packet_size[pt];

    int res = WSASend(m_server_socket, wsabuf, 2, &send_byte, 0, 0, 0);

    if (0 != res) {
        error_display("WSASend", WSAGetLastError());
        closesocket(m_server_socket);
    }

	return send_byte;
}

PacketType Client::Recv()
{
    PacketType pt{};
    wsabuf[0].buf = reinterpret_cast<char*>(&pt);
    wsabuf[0].len = sizeof(pt);

    DWORD recv_flag = 0;
    DWORD recv_byte;

	int res = WSARecv(m_server_socket, &wsabuf[0], 1, &recv_byte, &recv_flag, nullptr, nullptr);
    if (0 != res) {
        error_display("WSARecv", WSAGetLastError());
        closesocket(m_server_socket);
    }

    wsabuf[1].buf = buf;
    wsabuf[1].len = packet_size[pt];

    res = WSARecv(m_server_socket, &wsabuf[1], 1, &recv_byte, &recv_flag, nullptr, nullptr);
    if (0 != res) {
        error_display("WSARecv", WSAGetLastError());
        closesocket(m_server_socket);
    }

    return pt;
}

Client::~Client()
{
    closesocket(m_server_socket);
    WSACleanup();
}