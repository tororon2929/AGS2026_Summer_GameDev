#pragma once
#include <DxLib.h>

class PieceBase;

class Cell
{
private:

    int mX;
    int mY;

    int mScreenX;
    int mScreenY;

    bool mSelected;
    bool mMovePoint;

    PieceBase* mPiece;

    // 3D座標
    VECTOR mWorldPos;

public:

    Cell();

    void Init(int x, int y);

    // Piece
    void SetPiece(PieceBase* piece);
    PieceBase* GetPiece();

    // 座標
    int GetX() const;
    int GetY() const;

    // 画面座標
    void SetScreenPos(int x, int y);

    int GetScreenX() const;
    int GetScreenY() const;

    // 選択
    void SetSelected(bool flag);
    bool IsSelected() const;

    // 移動可能
    void SetMovePoint(bool flag);
    bool IsMovePoint() const;

    // 3D座標
    void SetWorldPos(VECTOR pos);
    VECTOR GetWorldPos() const;
};