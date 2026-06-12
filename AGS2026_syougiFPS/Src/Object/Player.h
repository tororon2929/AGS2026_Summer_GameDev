#pragma once
#include <DxLib.h>
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
    void GetShotLine(VECTOR* start, VECTOR* end)const;

private:
    VECTOR pos_;        // プレイヤーの現在座標
    float angleH_;      // 水平方向の回転角度
    float angleV_;      // 垂直方向の回転角度
    float velocityY_;

    
    const float turnSpeed_ = 0.005f; // マウス感度
	const float moveSpeed_ = 0.2f;// 移動速度
	const float gravity_ = -0.05f; // 重力加速度
};

