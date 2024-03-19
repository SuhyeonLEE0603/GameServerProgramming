#pragma once
#include <map>

enum PacketType {
	WindowSize,
	KeyInput,
	PlayerPos
};

struct PacketWindowSize {
	int width;
	int height;
};

struct PacketKeyInput {
	char key;
};

struct PacketPos {
	int pos_x;
	int pos_y;
};

static std::map<PacketType, size_t> packet_size{
	{WindowSize, sizeof(PacketWindowSize)},
	{KeyInput, sizeof(PacketKeyInput)},
	{PlayerPos, sizeof(PacketPos)}
};