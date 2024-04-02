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
	int id;
	char key;
};

struct PacketPos {
	int id;
	int pos_x;
	int pos_y;
};

static std::map<PacketType, int> packet_size{
	{WindowSize, sizeof(PacketWindowSize)},
	{KeyInput, sizeof(PacketKeyInput)},
	{PlayerPos, sizeof(PacketPos)}
};