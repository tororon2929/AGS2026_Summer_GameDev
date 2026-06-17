#pragma once
#include "EffectBase.h"

class CutInEffect : public EffectBase
{
private:
    int m_gh; // グラフィックハンドル
    int m_x, m_y;

public:
    // コンストラクタ
    CutInEffect(int graphHandle, float duration);

    // 仮想関数のオーバーライド宣言
    bool IsCutIn() const override;
    void Update(float deltaTime) override;
    void Draw() override;
};