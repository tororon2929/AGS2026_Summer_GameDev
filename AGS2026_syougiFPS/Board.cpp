#include "Board.h"
#include "DxLib.h"

void Board::Init()
{
    for (int y = 0; y < 9; y++)
        for (int x = 0; x < 9; x++)
            board[y][x] = Piece();

    // テスト用
    board[6][4] = Piece(PAWN, true);
    board[2][4] = Piece(PAWN, false);
}

void Board::Draw()
{
    int size = 50;

    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            int px = x * size;
            int py = y * size;

            DrawBox(px, py, px + size, py + size, GetColor(200, 170, 100), FALSE);

            if (board[y][x].type != EMPTY)
            {
                const char* text = (board[y][x].type == PAWN) ? "P" : "K";
                DrawString(px + 15, py + 15, text, GetColor(0, 0, 0));
            }
        }
    }
}