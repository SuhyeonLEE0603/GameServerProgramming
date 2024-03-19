#include "Headers.h"
#include "Server.h"
#include "Player.h"

int main()
{
	std::cout << "SERVER START" << std::endl;

	Server server;
	PacketType packet_type;
	Player player;

	server.Init();
	server.Accept();
	
	int x;
	int y;

	while (1) {

		if (server.GetClientSocket() == SOCKET_ERROR) {
			server.CloseServer();
			break;
		}

		packet_type = server.Recv();

		if (packet_type == WindowSize) {

			x = *reinterpret_cast<int*>(&server.buf[0]);
			y = *reinterpret_cast<int*>(&server.buf[4]);

			std::cout << "Recv WindowSize : " << x << ", " << y << std::endl;
		}
		else if (packet_type == KeyInput) {
			PacketKeyInput key;
			key.key = server.buf[0];

			switch (key.key)
			{
			case VK_LEFT:
				std::cout << "Go Left" << std::endl;
				player.Move(-(x / 8), 0);
				break;
			case VK_RIGHT:
				std::cout << "Go Right" << std::endl;
				player.Move(x / 8, 0);
				break;
			case VK_UP:
				std::cout << "Go Up" << std::endl;
				player.Move(0, -(y / 8));
				break;
			case VK_DOWN:
				std::cout << "Go Down" << std::endl;
				player.Move(0, y / 8);
				break;
			}
			PacketType packet = PlayerPos;
			PacketPos pos;

			pos.pos_x = player.pos.x;
			pos.pos_y = player.pos.y;

			server.Send(packet, (void*)&pos);
		}
	}
}