#pragma once
#include "PieceBase.h"

class Gin : public PieceBase
{
public:
    Gin(int x, int y, bool isPlayer);
    ~Gin();

    // 銀の移動判定（前、または斜め4方向の1マスならtrue）
    bool CanMove(int x, int y) override;

    void Draw() override;

private:
    int mModelHandle;
};