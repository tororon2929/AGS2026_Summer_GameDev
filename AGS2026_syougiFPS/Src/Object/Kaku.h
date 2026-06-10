#pragma once
#include "PieceBase.h"

class Kaku : public PieceBase
{
public:
    Kaku(int x, int y, bool isPlayer);
    ~Kaku();

    // Šp‚ÌˆÚ“®”»’èiÎ‚ß’¼ü‚Å‚ ‚ê‚Îtruej
    bool CanMove(int x, int y) override;

    void Draw() override;

private:
    int mModelHandle;
};