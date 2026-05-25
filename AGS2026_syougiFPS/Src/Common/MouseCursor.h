#pragma once

class MouseCursor
{
public:

    int mX;
    int mY;

    // ”Õî•ñ
    int boardStartX = 500;
    int boardStartY = 100;

    int cellSize = 120;

    void Update();

    int GetCellX() const;
    int GetCellY() const;

    bool IsOnBoard() const;
};