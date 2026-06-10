#pragma once
#include "PieceBase.h"

class Hisha : public PieceBase
{
public:

    Hisha(int x, int y, bool isPlayer);
    ~Hisha();

    bool CanMove(int x, int y) override;

    void Draw() override;

private:

    int mModelHandle;
};