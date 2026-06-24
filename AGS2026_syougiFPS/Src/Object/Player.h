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

    //外部からプレイヤーの座標などを取得
    VECTOR GetPos() const { return pos_; }
    VECTOR GetLookDir()const;
    void GetShotLine(VECTOR* start, VECTOR* end)const;
    
    int GetHP() const { return hp_; }
    bool IsInvincible() const { return invincibleTimer_ > 0; }
    void Damage(int value);
   
private:
    

    VECTOR pos_;        // プレイヤーの現在座標
    float angleH_;      // 水平方向の回転角度
    float angleV_;      // 垂直方向の回転角度
    float velocityY_;
    float floorHeight = 30.0f;
    float limitX = 25.0f;
    float limitZ = 25.0f;

    float fallLimitHeight = floorHeight - 50.0f;
    
    const float turnSpeed_ = 0.005f; // マウス感度
	const float moveSpeed_ = 0.1f;// 移動速度
	const float gravity_ = -0.05f; // 重力加速度


    int hp_ = 100;
    int invincibleTimer_ = 0;
    int jumpCount_ = 0;
    
};

