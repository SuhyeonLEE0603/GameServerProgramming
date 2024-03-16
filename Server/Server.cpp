#include "Server.h"

void error_display(const char* msg, int err_no)
{
    WCHAR* lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, err_no,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf, 0, NULL);
    std::cout << msg;
    std::wcout << L" 에러 " << lpMsgBuf << std::endl;
    while (true); // 디버깅용
    LocalFree(lpMsgBuf);
}

Server::Server()
{
    m_player_num = 0;

    if (WSAStartup(MAKEWORD(2, 2), &m_wsa) != 0) {
        exit(1);
    }

    m_s_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED);

    if (m_s_socket == INVALID_SOCKET) {
        exit(1);
    }

    DWORD optval = 1;

    setsockopt(m_s_socket, IPPROTO_TCP, TCP_NODELAY, (const char*)&optval, sizeof(optval));

    ZeroMemory(&m_server_addr, sizeof(m_server_addr));
    m_server_addr.sin_family = AF_INET;
    m_server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_server_addr.sin_port = htons(SERVER_PORT);
}

void Server::Init()
{
    if (bind(m_s_socket, reinterpret_cast<sockaddr*>(& m_server_addr), sizeof(m_server_addr))
        == SOCKET_ERROR) {
        exit(1);
    }

    if (listen(m_s_socket, SOMAXCONN) == SOCKET_ERROR) {
        exit(1);
    }

}

bool Server::Accept()
{
    int addr_size = sizeof(m_server_addr);
    SOCKET client_socket;

    if (client_socket = WSAAccept(m_s_socket, reinterpret_cast<sockaddr*>(&m_server_addr), &addr_size, NULL, NULL))
    {
        m_clients_socket.reserve(++m_player_num);
        m_clients_socket.emplace_back(client_socket);
        return true;
    }
    else {
        return false;
    }
}

DWORD Server::Send(SOCKET client_socket)
{
    WSABUF buf{};     // 좌표 보낼 버퍼
    DWORD send_byte;

    WSASend(client_socket, &buf, 1, &send_byte, 0, 0, 0);
	return send_byte;
}

DWORD Server::Recv(SOCKET client_socket)
{
    WSABUF buf{};     // 키 입력 받을 버퍼
    DWORD recv_byte;
    DWORD recv_flag = 0;
    
	WSARecv(client_socket, &buf, 1, &recv_byte, &recv_flag, 0, 0);
    
    return recv_byte;
}



Server::~Server()
{
    if (!closesocket(m_s_socket))
    {
        cout << "Server Close" << endl;
    }
    WSACleanup();
}
