#pragma once
#include "PieceBase.h"

class Kin : public PieceBase
{
public:
    Kin(int x, int y, bool isPlayer);
    ~Kin();

    // 金の移動判定（前・斜め前・横・後ろの1マスならtrue）
    bool CanMove(int x, int y) override;

    void Draw() override;

private:
    int mModelHandle;
};