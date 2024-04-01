#pragma once
#include "stdafx.h"

class Object
{
private:
    int m_id;
    Pos m_pos;

public:
    Object() {}
    ~Object() {};

    virtual void Init();
    virtual void Render(HDC);
    virtual void Update(int, int);
    virtual void SetId(int);
    int GetId() const { return m_id; };

};

extern HDC g_hdc;
