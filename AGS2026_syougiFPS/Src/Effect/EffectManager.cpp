// EffectManager.cpp
#include "EffectManager.h"

void EffectManager::Update(float deltaTime)
{
    // 各エフェクトの更新
    for (auto& effect : m_effects)
    {
        effect->Update(deltaTime);
    }

    // 終了フラグ(m_isDead)が立たったエフェクトを自動削除
    m_effects.erase(
        std::remove_if(m_effects.begin(), m_effects.end(),
            [](const std::unique_ptr<EffectBase>& e) { return e->IsDead(); }),
        m_effects.end()
    );
}

void EffectManager::Draw()
{
    // まとめて描画
    for (auto& effect : m_effects)
    {
        effect->Draw();
    }
}

void EffectManager::ClearAll()
{
    m_effects.clear();
}