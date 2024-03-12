#pragma once
#include "stdafx.h"


class King {
private:
    CImage king;
    Pos pos;

public:
    King(){}
    ~King();

    void Init();

    void Render(HDC hdc);

    void Move(int dx, int dy);

    
};