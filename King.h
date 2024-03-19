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
    void Render(HDC);
    void Update(int, int);
    //void Move(int dx, int dy);

    
};