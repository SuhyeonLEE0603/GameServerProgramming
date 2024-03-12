#include "ChessBoard.h"

extern int width, height;

ChessBoard::~ChessBoard() 
{
    if (!chessboard.IsNull())
    {
        chessboard.Destroy();
    }

}

void ChessBoard::Init()
{
    chessboard.Load(L"Resource//ChessBoard.png");

}

void ChessBoard::Render(HDC hdc)
{
    chessboard.Draw(hdc, 0, 0, width, height);
}