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

	}
}