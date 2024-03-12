#pragma once
#include "stdafx.h"

class ChessBoard {
private:
    CImage chessboard;

public:
    ChessBoard() {};
    ~ChessBoard();

    void Init();
    void Render(HDC hdc);

};