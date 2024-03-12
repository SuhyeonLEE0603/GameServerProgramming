#include "ChessBoard.h"

ChessBoard::~ChessBoard() 
{
    if (!chessboard.IsNull())
    {
        chessboard.Destroy();
    }

}

void ChessBoard::Init()
{
    chessboard.Load(L"Resource//ChessBoard.bmp");

}

void ChessBoard::Render(HDC hdc)
{
    chessboard.Draw(hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}