#include "CutInEffect.h"
#include "../Utility/AsoUtility.h"
#include <DxLib.h>

// コンストラクタの実装
CutInEffect::CutInEffect(int graphHandle, float duration)
    : EffectBase(duration), m_gh(graphHandle), m_x(3000), m_y(400)
{
}

// IsCutInの実装
bool CutInEffect::IsCutIn() const
{
    return true;
}

// Updateの実装
void CutInEffect::Update(float deltaTime)
{
    EffectBase::Update(deltaTime);

    float progress = m_time / m_duration;

    // 右から入って左へ抜ける演出ロジック
    if (progress < 0.25f) {
        m_x = AsoUtility::Lerp(3000, 960, progress / 0.25f);
    }
    else if (progress <= 0.75f) {
        m_x = 775;
    }
    else {
        m_x = AsoUtility::Lerp(960, -400, (progress - 0.75f) / 0.25f);
    }
}

// Drawの実装
void CutInEffect::Draw()
{
    if (m_gh != -1)
    {
        DrawRotaGraph(m_x, m_y, 1.0, 0.0, m_gh, TRUE);
    }
}