#pragma once
#include "PieceBase.h"

class Ou : public PieceBase
{
private:

    int mModelHandle;

public:

    Ou(int x, int y, bool isPlayer);
    ~Ou();

    void Draw() override;

    bool CanMove(int x, int y) override;
};