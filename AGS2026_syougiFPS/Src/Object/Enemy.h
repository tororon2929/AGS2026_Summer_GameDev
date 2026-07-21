#pragma once
#include "../Common/Transform.h"
#include <map>

enum class EnemyTextureState
{
    Normal,
    KIN,
};


class Enemy
{
public:
    int hp_ = 250;

    Enemy();
    ~Enemy();

    void Init();
    void Update(VECTOR playerPos);
    void Draw();
	void Release();

    VECTOR GetPos() const { return transform_.pos; }
    float GetRadius() const { return radius_; }
    void Damage(int value);
    bool IsDead() const { return hp_ <= 0; }

    // 外部からテクスチャ状態を切り替えるための関数
    //void SetTextureState(EnemyTextureState state);
    
private:
    std::map<EnemyTextureState, int>textureHandles_;
    int currentTextureHandle_;
    
    Transform transform_;
    float moveTimer_ = 0.0f;
    float moveSpeed = 0.05f;
	//地上の高さ
    float floorHeight = 26.0f;
	//敵の当たり判定の半径
    float radius_ = 2.0f;
    float velocityY_ = 0.0f;

    void ApplyCurrentTexture();

};


