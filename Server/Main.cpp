#include "Headers.h"
#include "Server.h"

int main()
{
	std::cout << "SERVER START" << std::endl;

	Server server;
	DWORD recv_byte{};

	server.Init();
	server.Accept();

	while (1) {

		recv_byte = server.Recv();

		if (server.buf[0] == VK_LEFT) {

		}
		else if (server.buf[0] == VK_RIGHT) {

		}
		else if (server.buf[0] == VK_UP) {

		}
		else if (server.buf[0] == VK_DOWN) {

		}
	}
}