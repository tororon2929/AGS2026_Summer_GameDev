#include "MouseCursor.h"
#include "DxLib.h"

void MouseCursor::Update()
{
    GetMousePoint(&mX, &mY);
}

int MouseCursor::GetCellX() const
{
    return (mX - boardStartX) / cellSize;
}

int MouseCursor::GetCellY() const
{
    return (mY - boardStartY) / cellSize;
}

bool MouseCursor::IsOnBoard() const
{
    int cellX = GetCellX();
    int cellY = GetCellY();

    return (cellX >= 0 && cellX < 5 &&
        cellY >= 0 && cellY < 5);
}