#include "Headers.h"
#include "Server.h"

int main()
{
	cout << "SERVER START" << endl;

	Server server;
	server.Init();
	
	SOCKET player_socket;

	while (1) {

		if (server.Accept()) {

		}

	}
}