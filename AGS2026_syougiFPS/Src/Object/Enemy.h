#pragma once
#include "../Common/Transform.h"
#include <map>

class EnemyState;

class Enemy
{
public:
    Enemy();
    ~Enemy();

    void Init();
    void Update(VECTOR playerPos);
    void Draw();
    void Release();

    // ステート切り替え関数
    void ChangeState(std::unique_ptr<EnemyState> newState);

    // テクスチャ適用処理
    void ApplyTexture(int texHandle);

    // --- ステート側から操作するためのゲッター / セッター ---
    VECTOR GetPos() const { return transform_.pos; }
    void SetPos(const VECTOR& pos) { transform_.pos = pos; }

    void SetRotation(const Quaternion& rot) { transform_.quaRot = rot; }

    float GetMoveSpeed() const { return moveSpeed_; }
    void SetMoveSpeed(float speed) { moveSpeed_ = speed; }

    void SetMaxHp(int maxHp) { maxHp_ = maxHp; hp_ = maxHp; }
    int GetHp() const { return hp_; }

    float GetRadius() const { return radius_; }
    void SetRadius(float r) { radius_ = r; }

    void Damage(int value);
    bool IsDead() const { return hp_ <= 0; }
    
private:
    std::unique_ptr<EnemyState> currentState_ = nullptr;

    Transform transform_;
    int hp_ = 250;
    int maxHp_ = 250;
    float moveSpeed_ = 0.05f;
    float floorHeight_ = 26.0f;
    float radius_ = 2.0f;
    float velocityY_ = 0.0f;

};


