#include "Cell.h"
#include "../Object/PieceBase.h"

Cell::Cell()
{
    mX = 0;
    mY = 0;

    mScreenX = 0;
    mScreenY = 0;

    mSelected = false;
    mMovePoint = false;

    mPiece = nullptr;

    mWorldPos = VGet(0, 0, 0);
}

void Cell::Init(int x, int y)
{
    mX = x;
    mY = y;
}

void Cell::SetPiece(PieceBase* piece)
{
    mPiece = piece;
}

PieceBase* Cell::GetPiece()
{
    return mPiece;
}

int Cell::GetX() const
{
    return mX;
}

int Cell::GetY() const
{
    return mY;
}

void Cell::SetScreenPos(int x, int y)
{
    mScreenX = x;
    mScreenY = y;
}

int Cell::GetScreenX() const
{
    return mScreenX;
}

int Cell::GetScreenY() const
{
    return mScreenY;
}

void Cell::SetSelected(bool flag)
{
    mSelected = flag;
}

bool Cell::IsSelected() const
{
    return mSelected;
}

void Cell::SetMovePoint(bool flag)
{
    mMovePoint = flag;
}

bool Cell::IsMovePoint() const
{
    return mMovePoint;
}

void Cell::SetWorldPos(VECTOR pos)
{
    mWorldPos = pos;
}

VECTOR Cell::GetWorldPos() const
{
    return mWorldPos;
}

void Cell::MoveScreenPos(int x, int y)
{
    mScreenX += x;
    mScreenY += y;
}