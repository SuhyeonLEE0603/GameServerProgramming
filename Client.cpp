#include "Client.h"

HWND g_hWnd;
void CALLBACK recv_callback(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);
void CALLBACK send_callback(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);

void error_display(LPCWSTR msg, int err_no)
{
    WCHAR* lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, err_no,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<LPTSTR>(&lpMsgBuf), 0, NULL);
    MessageBox(g_hWnd, lpMsgBuf, msg, 0);
    while (true); // µð¹ö±ë¿ë
    LocalFree(lpMsgBuf);
}

void do_recv()
{
    int res;

    DWORD recv_flag = 0;

    g_client_s.SetRecv();

    res = WSARecv(g_client_s.GetSock(), &g_client_s.GetWSABuf(), 2, 0, &recv_flag, &g_client_s.GetOver(), recv_callback);
    if (0 != res) {
        int err_no = WSAGetLastError();
        if (WSA_IO_PENDING != err_no) {
            error_display(L"WSARecv", WSAGetLastError());
            closesocket(g_client_s.GetSock());
        }
    }

}

void CALLBACK send_callback(DWORD er, DWORD send_size, LPWSAOVERLAPPED pwsaover, DWORD send_flag)
{
    int res;
    g_client_s.SetRecv();

    res = WSARecv(g_client_s.GetSock(), &g_client_s.GetWSABuf(), 2, nullptr, &send_flag, pwsaover, recv_callback);
    if (0 != res) {
        int err_no = WSAGetLastError();
        if (WSA_IO_PENDING != err_no) {
            error_display(L"WSARecv", WSAGetLastError());
            closesocket(g_client_s.GetSock());
        }
    }
}

void CALLBACK recv_callback(DWORD er, DWORD recv_size, LPWSAOVERLAPPED pwsaover, DWORD recv_flag)
{
    switch (g_client_s.GetPacketType()) 
    {
    case PlayerPos:
        //g_id = (int)g_client_s.buf[0];
        g_x = *reinterpret_cast<int*>(&g_client_s.buf[0]);
        g_y = *reinterpret_cast<int*>(&g_client_s.buf[4]);
        break;
    }

}

Client::Client()
{
    std::wcout.imbue(std::locale("korean"));

    if (WSAStartup(MAKEWORD(2, 2), &m_wsa) != 0) {
        error_display(L"WSAStartup", WSAGetLastError());
        closesocket(m_server_socket);
    }

    m_server_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED);

    if (m_server_socket == INVALID_SOCKET) {
        error_display(L"WSASocket", WSAGetLastError());
        closesocket(m_server_socket);
    }

    m_server_addr.sin_family = AF_INET;
    m_server_addr.sin_port = PORT;
    inet_pton(AF_INET, SERVER_ADDR, &m_server_addr.sin_addr);
}

bool Client::Init()
{
    if (SOCKET_ERROR == connect(m_server_socket, reinterpret_cast<sockaddr*>(&m_server_addr), sizeof(m_server_addr))) {
        return false;
    }
    return true;
}

void Client::Send(PacketType pt, void* packet)
{
    wsabuf[0].buf = reinterpret_cast<char*>(&pt);
    wsabuf[0].len = sizeof(pt);
    wsabuf[1].buf = reinterpret_cast<char*>(packet);
    wsabuf[1].len = packet_size[pt];

    int res = WSASend(m_server_socket, wsabuf, 2, nullptr, 0, &m_wsaover, send_callback);
    if (0 != res) {
        error_display(L"WSASend", WSAGetLastError());
        closesocket(m_server_socket);
    }

}

void Client::SetRecv()
{
    ZeroMemory(&pt, sizeof(pt));
    ZeroMemory(&m_wsaover, sizeof(m_wsaover));

    wsabuf[0].buf = reinterpret_cast<char*>(&pt);
    wsabuf[0].len = sizeof(pt);

    wsabuf[1].buf = buf;
    wsabuf[1].len = packet_size[pt];

    m_wsaover.hEvent = WSACreateEvent();
}

errno_t Client::KeyProcess(WPARAM& wParam)
{
    PacketType packet_type;
    packet_type = KeyInput;
    PacketKeyInput ki;

    switch (wParam)
    {
    case VK_LEFT:
        ki.key = VK_LEFT;
        break;
    case VK_RIGHT:
        ki.key = VK_RIGHT;
        break;
    case VK_UP:
        ki.key = VK_UP;
        break;
    case VK_DOWN:
        ki.key = VK_DOWN;
        break;
    case VK_ESCAPE:
        return 1;
    default:
        return -1;
    }

    g_client_s.Send(packet_type, (void*)&ki);
    
    return 0;
}

SOCKET& Client::GetSock()
{
    return m_server_socket;
}

WSAOVERLAPPED& Client::GetOver()
{
    return m_wsaover;
}

WSABUF& Client::GetWSABuf()
{
    return wsabuf[0];
}

PacketType Client::GetPacketType() const
{
    return pt;
}

Client::~Client()
{
    closesocket(m_server_socket);
    WSACleanup();
}