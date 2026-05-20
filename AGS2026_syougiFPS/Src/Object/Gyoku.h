#pragma once
#include "PieceBase.h"

class Gyoku : public PieceBase
{
private:

    int mModelHandle;
public:

    Gyoku(int x, int y, bool isPlayer);

    virtual ~Gyoku();

    virtual bool CanMove(int x, int y) override;

    virtual void Draw() override;
};