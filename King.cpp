#include "King.h"

extern int width, height;

King::~King()
{
    if (!m_king.IsNull())
    {
        m_king.Destroy();
    }
}

void King::Init()
{
    m_pos = { 0, 0 };
    m_id = 0;
    m_king.Load(L"Resource//King.png");
}


void King::Render(HDC hdc)
{
    char text[2];
    sprintf_s(text, "%d", m_id);
    m_king.Draw(hdc, m_pos.x, m_pos.y, width / 8, height / 8 );
    RECT rect = { m_pos.x,  m_pos.y, m_pos.x + width / 8,  m_pos.y + height / 8 };
    DrawTextA(hdc, text, -1, &rect, DT_CENTER);
}

void King::Update(int new_x, int new_y)
{
    m_pos.x = new_x;
    m_pos.y = new_y;
}

void King::SetId(int id)
{
    m_id = id;
}

int King::GetId() const
{
    return m_id;
}
