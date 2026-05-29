#pragma once
#include <DxLib.h>

enum PieceType
{
    PIECE_NONE,
    PIECE_FU,
    PIECE_OU,
    PIECE_GYOKU,
  
};

class PieceBase
{
protected:

    int mX;
    int mY;

    bool mIsPlayer;

    PieceType mType;

    // 3Dç¿ïW
    VECTOR mWorldPos;

public:

    PieceBase(int x, int y, bool isPlayer);
    virtual ~PieceBase();

    virtual void Draw() = 0;

    virtual bool CanMove(int x, int y) = 0;

    void SetPos(int x, int y);

    int GetX() const;
    int GetY() const;

    bool IsPlayer() const;

    PieceType GetType() const;

    // 3Dç¿ïW
    void SetWorldPos(VECTOR pos);
    VECTOR GetWorldPos() const;
};