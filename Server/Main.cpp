#include "Headers.h"
#include "Server.h"
#include "Player.h"

int main()
{
	std::cout << "SERVER START" << std::endl;

	Server server;

	server.Init();

	for (int i = 1; i <= 10; ++i) {
		clients_sockets.try_emplace(i, i, server.Accept());
		clients_sockets[i].do_recv();
	}

	//while (1) {

	//	recv_size = server.Recv();
	//	if (recv_size == 0) {
	//		break;
	//	}

	//	if (server.pt == WindowSize) {

	//		x = *reinterpret_cast<int*>(&server.buf[0]);
	//		y = *reinterpret_cast<int*>(&server.buf[4]);

	//		std::cout << "Recv WindowSize : " << x << ", " << y << std::endl;
	//	}
	//	else if (server.pt == KeyInput) {
	//		PacketKeyInput key;

	//		key.id = id;
	//		key.key = server.buf[4];

	//		switch (key.key)
	//		{
	//		case VK_LEFT:
	//			std::cout << "Go Left" << std::endl;
	//			player.Move(-(x / 8), 0);
	//			break;
	//		case VK_RIGHT:
	//			std::cout << "Go Right" << std::endl;
	//			player.Move(x / 8, 0);
	//			break;
	//		case VK_UP:
	//			std::cout << "Go Up" << std::endl;
	//			player.Move(0, -(y / 8));
	//			break;
	//		case VK_DOWN:
	//			std::cout << "Go Down" << std::endl;
	//			player.Move(0, y / 8);
	//			break;
	//		}
	//		PacketType packet = PlayerPos;
	//		PacketPos pos;

	//		pos.id = id;
	//		pos.pos_x = player.pos.x;
	//		pos.pos_y = player.pos.y;

	//		server.Send(packet, (void*)&pos);
	//	}
	//}

	std::cout << "Client Close" << std::endl;
}