#include "PieceBase.h"

PieceBase::PieceBase(int x, int y, bool isPlayer)
    : mX(x),
    mY(y),
    mIsPlayer(isPlayer),
    mType(PIECE_NONE)
{
    mWorldPos = VGet(0, 0, 0);
}

PieceBase::~PieceBase()
{
}

void PieceBase::SetPos(int x, int y)
{
    mX = x;
    mY = y;
}

int PieceBase::GetX() const
{
    return mX;
}

int PieceBase::GetY() const
{
    return mY;
}

bool PieceBase::IsPlayer() const
{
    return mIsPlayer;
}

PieceType PieceBase::GetType() const
{
    return mType;
}

void PieceBase::SetWorldPos(VECTOR pos)
{
    mWorldPos = pos;
}

VECTOR PieceBase::GetWorldPos() const
{
    return mWorldPos;
}