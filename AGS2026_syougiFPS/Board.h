#pragma once
#include "Piece.h"

class Board
{
public:
    Piece board[9][9];

    void Init();
    void Draw();
};