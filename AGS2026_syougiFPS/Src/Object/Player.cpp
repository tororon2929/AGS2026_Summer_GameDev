#include "Player.h"
#include"../Common/Camera.h"
#include"../Application.h"
#include"../Manager/InputManager.h"
#include"../Manager/SoundManager.h"
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
   hHpBar_ = LoadGraph("Data/UI/HPbar.png");

   if (hHpBar_ != -1)
   {
       GetGraphSize(hHpBar_, &barWidth_, &barHeight_);
   }
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

    auto padState = InputManager::GetInstance().GetJPadInputState(InputManager::JOYPAD_NO::PAD1);
    float padX = padState.AKeyLX / 1000.0f;
    float padY = -(padState.AKeyLY / 1000.0f);

    if (fabsf(padX) > deadZone || fabsf(padY) > deadZone) {
        moveDir.x += (padX * cosH + padY * sinH);
        moveDir.z += (-padX * sinH + padY * cosH);
    }
    // 移動ベクトルがあれば正規化して座標に加算
    if (VSquareSize(moveDir) > 0.0f)
    {
        moveDir = VNorm(moveDir);

        bool isDash = CheckHitKey(KEY_INPUT_LSHIFT) ||
            InputManager::GetInstance().IsPadBtnNew(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::L_TRIGGER);
        float currentSpeed = isDash ? dashSpeed_ : moveSpeed_;
        pos_ = VAdd(pos_, VScale(moveDir, currentSpeed));
    }

    static bool preBtnPressed = false;
    bool currentBtnPressed = CheckHitKey(KEY_INPUT_SPACE) ||
        InputManager::GetInstance().IsPadBtnNew(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN);

    // 重力を適用
    velocityY_ += gravity_;

    // Y座標に重力を適用
    pos_.y += velocityY_;

	//プレイヤーが将棋盤の上にいるかどうかの判定
    if (pos_.x >= -limitX && pos_.x <= limitX && pos_.z >= -limitZ && pos_.z <= limitZ) {
        if (pos_.y < floorHeight) {
            pos_.y = floorHeight;
            velocityY_ = 0.0f;
            jumpCount_ = 0;
        }
    }
    else if (pos_.y < (floorHeight - 50.0f)) {
        hp_ = 0;
    }

    // ジャンプ開始
    if (currentBtnPressed && !preBtnPressed) {
        SoundManager::GetInstance().PlaySE(SoundManager::SE::Jamp);
        if (pos_.y <= floorHeight) {
            velocityY_ = 1.2f;
            jumpCount_ = 1;
        }
    }
    else if (jumpCount_ == 1 && currentBtnPressed) { // 2段ジャンプ的な挙動
        velocityY_ = 1.0f;
        jumpCount_ = 2;
    }
    preBtnPressed = currentBtnPressed;


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

    invincibleTimer_ = 120;

    
}

void Player::Draw()
{
	// HPバーの描画
    if (hHpBar_ != -1)
    {
        int displayHeight = (int)((float)displayMaxWidth * barHeight_ / barWidth_);

        float hpRatio = (float)hp_ / maxHp_;
        if (hpRatio < 0.0f) hpRatio = 0.0f;

        int srcWidth = (int)(barWidth_ * hpRatio);
        int drawWidth = (int)(displayMaxWidth * hpRatio);

        if (srcWidth > 0 && drawWidth > 0)
        {
            DrawRectExtendGraph(
                drawX, drawY, drawX + drawWidth, drawY + displayHeight,
                0, 0, srcWidth, barHeight_,
                hHpBar_, TRUE);
        }
    }
}
   
void Player::Release()
{
    if (hHpBar_ != -1)
    {
        DeleteGraph(hHpBar_);
        hHpBar_ = -1;
    }

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


