#include "Player.h"
#include"../Common/Camera.h"
#include <cmath>

Player::Player()
    : pos_({ 0.0f, 10.0f, 0.0f })
    , velocityY_(0.0f)
{
}

Player::~Player()
{
}

void Player::Init()
{
   
}

void Player::Update(Camera* camera)
{
    if (camera == nullptr)return;

    if (invincibleTimer_ > 0)
    {
        invincibleTimer_--;
    }

    // 現在向いている水平方向のベクトルを計算
    VECTOR cameraAngles = camera->GetAngles();
    float sinH = sinf(cameraAngles.y);
    float cosH = cosf(cameraAngles.y);

    VECTOR moveDir = { 0.0f, 0.0f, 0.0f };

    if (CheckHitKey(KEY_INPUT_W)) // 前進
    {
        moveDir.x += sinH;
        moveDir.z += cosH;
    }
    if (CheckHitKey(KEY_INPUT_S)) // 後退
    {
        moveDir.x -= sinH;
        moveDir.z -= cosH;
    }
    if (CheckHitKey(KEY_INPUT_D)) // 右移動
    {
        moveDir.x += cosH;
        moveDir.z -= sinH;
    }
    if (CheckHitKey(KEY_INPUT_A)) // 左移動
    {
        moveDir.x -= cosH;
        moveDir.z += sinH;
    }

    // 移動ベクトルがあれば正規化して座標に加算
    if (VSquareSize(moveDir) > 0.0f)
    {
        moveDir = VNorm(moveDir);
        //ダッシュの判定
        float currentSpeed = moveSpeed_;
        if (CheckHitKey(KEY_INPUT_LSHIFT))
        {
            currentSpeed = dashSpeed_;
        }


        if (CheckHitKey(KEY_INPUT_LSHIFT)) {
            DrawString(10, 100, "SHIFT PUSHED: DASH SPEED ACTIVE", GetColor(255, 255, 0));
        }
        else {
            DrawString(10, 100, "NORMAL SPEED ACTIVE", GetColor(255, 255, 255));
        }

        pos_ = VAdd(pos_, VScale(moveDir, currentSpeed));
    }

    static bool preSpacePressed = false;
    bool currentSpacePressed = CheckHitKey(KEY_INPUT_SPACE);

    // 重力を適用
    velocityY_ += gravity_;

    // Y座標に重力を適用
    pos_.y += velocityY_;

	//プレイヤーが将棋盤の上にいるかどうかの判定
    if (pos_.x >= -limitX && pos_.x <= limitX && pos_.z >= -limitZ && pos_.z <= limitZ)
    {

        if (pos_.y < floorHeight)
        {
            pos_.y = floorHeight;
            velocityY_ = 0.0f; // 床に着地したら垂直速度をリセット

            jumpCount_ = 0;
        } 
    }
    else
    {
        float fallLimitHeight = floorHeight - 50.0f;
        if (pos_.y < fallLimitHeight)
        {
            hp_ = 0;
        }
    }

    if (currentSpacePressed && !preSpacePressed)
    {
        if (pos_.y <= floorHeight)
        {
            velocityY_ = 1.2f;
            jumpCount_ = 1;
        }
    }
    else if (jumpCount_ == 1)
    {
        velocityY_ = 1.0f;
        jumpCount_ = 2;
    }
    preSpacePressed = currentSpacePressed;


    VECTOR cameraPos = pos_;
    cameraPos.y += 0.3f;

	//カメラの位置をプレイヤーの位置に合わせる
    camera->Setpos(cameraPos);

    
    
}

void Player::Damage(int value)
{
    if (IsInvincible()) return;

    hp_ -= value;
    if (hp_ < 0) hp_ = 0;

    invincibleTimer_ = 60;

    
}

void Player::Draw()
{
}
   
void Player::Release()
{
}

VECTOR Player::GetLookDir() const
{
    float sinH = sinf(angleH_);
    float cosH = cosf(angleH_);
    return{ cosf(angleV_) * sinH,sinf(angleV_),cosf(angleV_) * cosH };
}

void Player::GetShotLine(VECTOR* start, VECTOR* end) const
{
    *start = pos_;

    float sinH = sinf(angleH_);
	float cosH = cosf(angleH_);
    VECTOR lookDir = {
        cosf(angleV_) * sinH,
        sinf(angleV_),
        cosf(angleV_) * cosH
    };

    *end = VAdd(pos_, VScale(lookDir, 10000.0f));
}


