#pragma once
#include "PieceBase.h"

class Fu : public PieceBase
{
public:

    Fu(int x, int y, bool isPlayer);
    ~Fu();

    bool CanMove(int x, int y) override;

    void Draw() override;

private:

    int mModelHandle;
};