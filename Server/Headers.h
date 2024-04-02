#pragma once

#include <WS2tcpip.h>
#pragma comment (lib, "WS2_32.LIB")

#include <iostream>
#include <vector>
#include <thread>
#include <unordered_map>

void error_display(const char* msg, int err_no)
{
    WCHAR* lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, err_no,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<LPTSTR>(&lpMsgBuf), 0, NULL);
    std::cout << msg;
    std::wcout << L" 에러 " << lpMsgBuf << std::endl;
    while (true); // 디버깅용
    LocalFree(lpMsgBuf);
}

struct Pos {
	int x{};
	int y{};

	Pos() {}

	Pos(int ix, int iy) {
		x = ix;
		y = iy;
	}

	Pos operator*(const float f) {
		Pos ret;
		ret.x = x * f;
		ret.y = y * f;
		return ret;
	}

	Pos operator-(const Pos& p) {
		Pos ret;
		ret.x = x - p.x;
		ret.y = y - p.y;
		return ret;
	}
	Pos operator+(const Pos& p) {
		Pos ret;
		ret.x = x + p.x;
		ret.y = y + p.y;
		return ret;
	}

	void operator-=(const Pos& p) {
		x -= p.x;
		y -= p.y;
	}
	void operator+=(const Pos& p) {
		x += p.x;
		y += p.y;
	}

	bool operator!=(const Pos& p) {
		return (x != p.x || y != p.y);
	}
};