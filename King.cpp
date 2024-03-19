#include "King.h"

extern int width, height;

King::~King()
{
    if (!king.IsNull())
    {
        king.Destroy();
    }
}

void King::Init()
{
    pos = { 0, 0 };

    king.Load(L"Resource//King.png");
}


void King::Render(HDC hdc)
{

    king.Draw(hdc, pos.x, pos.y, width / 8, height / 8 );

}

void King::Update(int new_x, int new_y)
{
    pos.x = new_x;
    pos.y = new_y;
}

//void King::Move(int dx, int dy)
//{
//    if (pos.x + dx < 0 || pos.x + dx > 1100 
//        || pos.y + dy < 0 || pos.y + dy > 1000) {
//        return;
//    }
//    pos.x += dx;
//    pos.y += dy;
//}
