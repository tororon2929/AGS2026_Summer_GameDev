#include "Cursor.h"
#include "DxLib.h"

void Cursor::Update()
{
    if (CheckHitKey(KEY_INPUT_UP))    y--;
    if (CheckHitKey(KEY_INPUT_DOWN))  y++;
    if (CheckHitKey(KEY_INPUT_LEFT))  x--;
    if (CheckHitKey(KEY_INPUT_RIGHT)) x++;

    if (x < 0) x = 0;
    if (x > 8) x = 8;
    if (y < 0) y = 0;
    if (y > 8) y = 8;
}

void Cursor::Draw()
{
    int size = 50;

    DrawBox(x * size, y * size,
        x * size + size, y * size + size,
        GetColor(255, 0, 0), FALSE);
}