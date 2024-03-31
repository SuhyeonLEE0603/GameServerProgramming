#pragma once
#include "stdafx.h"

class King {
private:
    int m_id;
    CImage m_king;
    Pos m_pos;

public:
    King(){}
    ~King();

    void Init();
    void Render(HDC);
    void Update(int, int);
    void SetId(int);
    int GetId() const;

};