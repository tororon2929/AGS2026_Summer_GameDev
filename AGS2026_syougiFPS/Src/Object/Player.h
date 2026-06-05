#pragma once
#include <DxLib.h>
class Player
{
public:
    Player();
    ~Player();

    void Init();
    void Update();

    // 外部からプレイヤーの座標などを取得したい場合用
    VECTOR GetPos() const { return pos_; }

private:
    VECTOR pos_;        // プレイヤーの現在座標（足元または目線）
    float angleH_;      // 水平方向の回転角度（マウスの左右移動で変化）
    float angleV_;      // 垂直方向の回転角度（マウスの上下移動で変化）

    const float moveSpeed_ = 5.0f;  // 移動速度
    const float turnSpeed_ = 0.005f; // マウス感度（回転速度）
};

