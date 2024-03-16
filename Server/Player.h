#pragma once
#include "Headers.h"

class Player
{
private:
    Pos pos;

public:
    Player() :pos(0, 0) {};
    void Move(int dx, int dy);
};

