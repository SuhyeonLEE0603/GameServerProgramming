#pragma once
#include "Headers.h"

class Player
{
private:
    int x;
    int y;

public:
    Player() :x{}, y{} {};
    void Move(int dx, int dy);
};

