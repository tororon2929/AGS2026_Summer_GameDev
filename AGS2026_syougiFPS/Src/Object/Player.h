#pragma once
#include <DxLib.h>
#include"../Common/Transform.h"
class Camera;

class Player
{
public:
    Player();
    ~Player();

    void Init();
    void Update(Camera* camera);
	void Draw();
	void Release();

    void SetPos(const VECTOR& pos) { pos_ = pos; }

    //外部からプレイヤーの座標などを取得
    VECTOR GetPos() const { return pos_; }
    VECTOR GetLookDir(Camera* camera) const;
    void GetShotLine(Camera* camera, VECTOR* start, VECTOR* end) const;
    
    int GetHP() const { return hp_; }
    bool IsInvincible() const { return invincibleTimer_ > 0; }
    void Damage(int value);
   
private:
    VECTOR pos_;        // プレイヤーの現在座標
    float velocityY_;
    float floorHeight = 26.4f;
    float limitX = 25.0f;
    float limitZ = 25.0f;

    float fallLimitHeight = floorHeight - 50.0f;
    
	const float moveSpeed_ = 0.05f;// 移動速度
    const float dashSpeed_ = 0.15f;
	const float gravity_ = -0.05f; // 重力加速度
    const float deadZone = 0.2f;
    const int maxHp_ = 100;

    int hp_ = 100;
    int invincibleTimer_ = 0;
    int jumpCount_ = 0;
    int hHpBar_ = -1;
    int barWidth_ = 0;
    int barHeight_ = 0;
    int displayMaxWidth = 767;
    int drawX = 20;
    int drawY = 20;
};

