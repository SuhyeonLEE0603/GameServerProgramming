#pragma once

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

