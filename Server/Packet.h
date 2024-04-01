#pragma once
#include <map>

enum PacketType {
	WindowSize,
	KeyInput,
	PlayerPos,
	Playerid
};

struct PacketWindowSize {
	int width;
	int height;
};

struct PacketKeyInput {
	//char id;
	char key;
};

struct PacketPos {
	//char id;
	int pos_x;
	int pos_y;
};

static std::map<PacketType, int> packet_size{
	{WindowSize, sizeof(PacketWindowSize)},
	{KeyInput, sizeof(PacketKeyInput)},
	{PlayerPos, sizeof(PacketPos)}
};