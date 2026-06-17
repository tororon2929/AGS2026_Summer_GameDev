#pragma once

class EffectBase
{
protected:
    float m_time;       // 経過時間
    float m_duration;   // 演出の総生存時間（秒）
    bool  m_isDead;     // 終了フラグ

public:

    // EffectBase.h の class EffectBase 内に追加
public:
    virtual bool IsCutIn() const { return false; } // デフォルトはfalse
    EffectBase(float duration)
        : m_time(0.0f), m_duration(duration), m_isDead(false) {
    }
    virtual ~EffectBase() {}

    virtual void Update(float deltaTime)
    {
        m_time += deltaTime;
        if (m_time >= m_duration)
        {
            m_isDead = true;
        }
    }

    virtual void Draw() = 0; // 各エフェクトで固有の描画を書く

    bool IsDead() const { return m_isDead; }
};