#pragma once
#include "Headers.h"

class Player
{
public:
    Pos pos;

    void Move(int, int);
    Pos GetPos();
};

