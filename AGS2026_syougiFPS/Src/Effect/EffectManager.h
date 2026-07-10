// EffectManager.h
#pragma once
#include <vector>
#include <memory>
#include "EffectBase.h"

class EffectManager
{
private:
    // メモリリーク防止のためスマートポインタ(std::unique_ptr)での管理がおすすめ
    std::vector<std::unique_ptr<EffectBase>> m_effects;

    EffectManager() {} // シングルトン化

public:

    bool IsCutInActive() const
    {
        for (const auto& effect : m_effects)
        {
            if (effect && effect->IsCutIn() && !effect->IsDead())
            {
                return true; // 現在カットイン演出が進行中
            }
        }
        return false;
    }
    static EffectManager& GetInstance()
    {
        static EffectManager instance;
        return instance;
    }

    // エフェクトの追加
    void AddEffect(std::unique_ptr<EffectBase> effect)
    {
        m_effects.push_back(std::move(effect));
    }

    void Update(float deltaTime);
    void Draw();
    void ClearAll(); // シーン切り替え時用
};