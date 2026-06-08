#include "Player.h"
#include <cmath>

Player::Player()
    : pos_({ 0.0f, 50.0f, 0.0f }) // 目線の高さ（Y=50）に初期設定
    , angleH_(0.0f)
    , angleV_(0.0f)
{
}

Player::~Player()
{
}

void Player::Init()
{
    // マウスカーソルを非表示にし、画面中央に固定する（FPSの基本設定）
    SetMouseDispFlag(FALSE);
    SetMousePoint(640, 360); 
}

void Player::Update()
{
    //マウス入力による視線（カメラ）の回転処理
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);

    // 画面中央からのズレを移動量として取得
    int deltaX = mouseX - 640;
    int deltaY = mouseY - 360;

    // マウスを中央に戻す
    SetMousePoint(640, 360);

    // 回転角の更新
    angleH_ += deltaX * turnSpeed_;
    angleV_ -= deltaY * turnSpeed_; // 上を向いたらプラス、下を向いたらマイナス

    // 垂直方向の回転制限（真上や真後ろを向けないようにする限制）
    if (angleV_ > DX_PI_F / 2.0f - 0.05f) angleV_ = DX_PI_F / 2.0f - 0.05f;
    if (angleV_ < -DX_PI_F / 2.0f + 0.05f) angleV_ = -DX_PI_F / 2.0f + 0.05f;

    
    //キーボード入力による移動処理（視線方向を基準に移動）
    
    // 現在向いている水平方向のベクトルを計算
    float sinH = sinf(angleH_);
    float cosH = cosf(angleH_);

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
    if (CheckHitKey(KEY_INPUT_D)) // 右ストレイフ
    {
        moveDir.x += cosH;
        moveDir.z -= sinH;
    }
    if (CheckHitKey(KEY_INPUT_A)) // 左ストレイフ
    {
        moveDir.x -= cosH;
        moveDir.z += sinH;
    }

    // 移動ベクトルがあれば正規化して座標に加算
    if (VSquareSize(moveDir) > 0.0f)
    {
        moveDir = VNorm(moveDir);
        pos_ = VAdd(pos_, VScale(moveDir, moveSpeed_));
    }
    
    // プレイヤーが見ている「注視点」の座標を計算
    VECTOR target;
    target.x = pos_.x + cosf(angleV_) * sinf(angleH_);
    target.y = pos_.y + sinf(angleV_);
    target.z = pos_.z + cosf(angleV_) * cosf(angleH_);

    // カメラの位置をプレイヤーの座標に、向きを注視点に設定
    SetCameraPositionAndTargetAndUpVec(pos_, target, VGet(0.0f, 1.0f, 0.0f));

    //射撃処理
    if (GetMouseInput() & MOUSE_INPUT_LEFT)
    {
        VECTOR lineStart = pos_;

        float sinH = sinf(angleH_);
        float cosH = cosf(angleH_);
        VECTOR lookDir;
        lookDir.x = cosf(angleV_) * sinH;
		lookDir.y = sinf(angleV_);
        lookDir.z = cosf(angleV_) * cosH;

        VECTOR lineEnd = VAdd(lineStart, VScale(lookDir, 10000.0f));
    }
}

void Player::Draw()
{
    // プレイヤーは見えないので描画処理はなし
}
   
void Player::Release()
{
    // 特にリソースを持っていないので解放処理はなし
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
