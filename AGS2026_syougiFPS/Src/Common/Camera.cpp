#include "../Common/Camera.h"
#include "../Utility/AsoUtility.h"
#include <DxLib.h>

Camera::Camera(void)
    : mode_(CameraMode::TopDown)    // 宣言順1番目
    , pos_{ 0.0f, 0.0f, 0.0f }     // 宣言順2番目
    , angles_{ 0.0f, 0.0f, 0.0f }  // 宣言順3番目
    , rot_(Quaternion::Identity())  // 宣言順4番目
    , prevMKey_(false)              // 宣言順5番目
{
}

Camera::~Camera(void) {}

void Camera::Init(void)
{
    pos_ = VGet(0.0f, TOP_HEIGHT, 0.0f);
    angles_ = VGet(DX_PI_F / 2.0f, 0.0f, 0.0f);
    rot_ = Quaternion::Euler(angles_);

    SetMouseDispFlag(TRUE);

    // 初期状態をDXLibに反映
    SetCameraNearFar(1.0f, 10000.0f);
    VECTOR target = VGet(pos_.x, 0.0f, pos_.z);
    SetCameraPositionAndTargetAndUpVec(
        pos_,
        target,
        VGet(0.0f, 0.0f, 1.0f)
    );
}

// ─────────────────────────────────────────────────────────
//  メイン更新
// ─────────────────────────────────────────────────────────
void Camera::Update(void)
{
    SwitchMode();

    switch (mode_) {
    case CameraMode::TopDown: UpdateTopDown(); break;
    case CameraMode::FPS:     UpdateFPS();     break;
    }

    ApplyCamera();
}

// ─────────────────────────────────────────────────────────
//  Mキーでモード切替
// ─────────────────────────────────────────────────────────
void Camera::SwitchMode(void)
{
    bool nowM = (CheckHitKey(KEY_INPUT_M) != 0);

    if (nowM && !prevMKey_) {
        if (mode_ == CameraMode::TopDown) {
            // FPS へ切替
            mode_ = CameraMode::FPS;
            pos_.y = FPS_EYE_HEIGHT;
            angles_ = VGet(0.0f, angles_.y, 0.0f);
            rot_ = Quaternion::Euler(angles_);

            SetMouseDispFlag(FALSE);
            SetMousePoint(320, 240);
        }
        else {
            // 俯瞰へ切替
            mode_ = CameraMode::TopDown;
            pos_.y = TOP_HEIGHT;
            angles_ = VGet(DX_PI_F / 2.0f, 0.0f, 0.0f);
            rot_ = Quaternion::Euler(angles_);

            SetMouseDispFlag(TRUE);
        }
    }

    prevMKey_ = nowM;
}

// ─────────────────────────────────────────────────────────
//  俯瞰視点の更新
//  WASD : XZ平行移動
//  QE   : ズームイン/アウト（高度変更）
// ─────────────────────────────────────────────────────────
void Camera::UpdateTopDown(void)
{
    if (CheckHitKey(KEY_INPUT_W)) pos_.z += TOP_MOVE_SPEED;
    if (CheckHitKey(KEY_INPUT_S)) pos_.z -= TOP_MOVE_SPEED;
    if (CheckHitKey(KEY_INPUT_A)) pos_.x -= TOP_MOVE_SPEED;
    if (CheckHitKey(KEY_INPUT_D)) pos_.x += TOP_MOVE_SPEED;

    if (CheckHitKey(KEY_INPUT_Q)) pos_.y += TOP_ZOOM_SPEED;
    if (CheckHitKey(KEY_INPUT_E)) pos_.y -= TOP_ZOOM_SPEED;

    // 高度クランプ
    if (pos_.y < TOP_HEIGHT_MIN) pos_.y = TOP_HEIGHT_MIN;
    if (pos_.y > TOP_HEIGHT_MAX) pos_.y = TOP_HEIGHT_MAX;

    // 常に真下を向く
    angles_ = VGet(DX_PI_F / 2.0f, 0.0f, 0.0f);
    rot_ = Quaternion::Euler(angles_);
}

// ─────────────────────────────────────────────────────────
//  FPS視点の更新
//  WASD     : 前後左右移動（向いている方向基準）
//  マウス移動 : 視点回転（yaw / pitch）
// ─────────────────────────────────────────────────────────
void Camera::UpdateFPS(void)
{
    // マウスで視点回転
    int mx, my;
    GetMousePoint(&mx, &my);

    float deltaX = static_cast<float>(mx - 320) * FPS_ROT_SPEED;
    float deltaY = static_cast<float>(my - 240) * FPS_ROT_SPEED;

    angles_.y += deltaX;
    angles_.x += deltaY;

    // ピッチをクランプ
    if (angles_.x > FPS_PITCH_LIMIT) angles_.x = FPS_PITCH_LIMIT;
    if (angles_.x < -FPS_PITCH_LIMIT) angles_.x = -FPS_PITCH_LIMIT;

    // マウスを中央に戻す
    SetMousePoint(320, 240);

    // Yaw → Pitch の順に合成（ジンバルロック回避）
    Quaternion qYaw = Quaternion::AngleAxis(
        angles_.y, VGet(0.0f, 1.0f, 0.0f));
    Quaternion qPitch = Quaternion::AngleAxis(
        angles_.x, VGet(1.0f, 0.0f, 0.0f));
    rot_ = Quaternion::Mult(qYaw, qPitch);

    // 移動方向をクォータニオンで変換
    VECTOR forward = rot_.GetForward();
    VECTOR right = rot_.GetRight();

    // XZ平面に投影（空中浮遊しない）
    forward.y = 0.0f;
    right.y = 0.0f;
    forward = AsoUtility::VNormalize(forward);
    right = AsoUtility::VNormalize(right);

    if (CheckHitKey(KEY_INPUT_W)) pos_ = VAdd(pos_, VScale(forward, FPS_MOVE_SPEED));
    if (CheckHitKey(KEY_INPUT_S)) pos_ = VAdd(pos_, VScale(forward, -FPS_MOVE_SPEED));
    if (CheckHitKey(KEY_INPUT_D)) pos_ = VAdd(pos_, VScale(right, FPS_MOVE_SPEED));
    if (CheckHitKey(KEY_INPUT_A)) pos_ = VAdd(pos_, VScale(right, -FPS_MOVE_SPEED));

    // 高さ固定
    pos_.y = FPS_EYE_HEIGHT;
}

// ─────────────────────────────────────────────────────────
//  DXLib へカメラを反映（共通処理）
// ─────────────────────────────────────────────────────────
void Camera::ApplyCamera(void)
{
    // Near/Far は位置設定より前に呼ぶ
    SetCameraNearFar(1.0f, 10000.0f);

    if (mode_ == CameraMode::TopDown)
    {
        // 俯瞰：真下を向くとupが縮退するので補正
        VECTOR target = VGet(pos_.x, 0.0f, pos_.z);
        SetCameraPositionAndTargetAndUpVec(
            pos_,
            target,
            VGet(0.0f, 0.0f, 1.0f)  // up を Z軸に固定
        );
    }
    else
    {
        VECTOR forward = rot_.GetForward();
        VECTOR up = rot_.GetUp();
        VECTOR target = VAdd(pos_, forward);
        SetCameraPositionAndTargetAndUpVec(pos_, target, up);
    }
}

// ─────────────────────────────────────────────────────────
//  Draw() の直前に呼ぶ（3D描画にカメラを確実に反映）
// ─────────────────────────────────────────────────────────
void Camera::SetBeforeDraw(void)
{
    SetCameraNearFar(1.0f, 10000.0f);

    if (mode_ == CameraMode::TopDown)
    {
        VECTOR target = VGet(pos_.x, 0.0f, pos_.z);
        SetCameraPositionAndTargetAndUpVec(
            pos_,
            target,
            VGet(0.0f, 0.0f, 1.0f)
        );
    }
    else
    {
        VECTOR forward = rot_.GetForward();
        VECTOR up = rot_.GetUp();
        VECTOR target = VAdd(pos_, forward);
        SetCameraPositionAndTargetAndUpVec(pos_, target, up);
    }
}

// ─────────────────────────────────────────────────────────
//  デバッグ描画
// ─────────────────────────────────────────────────────────
void Camera::DrawDebug(void)
{
    int y = 10;
    const int         LINE = 20;
    const unsigned int COL = GetColor(0, 255, 0);

    const char* modeName =
        (mode_ == CameraMode::TopDown) ? "TopDown" : "FPS";

    DrawFormatString(10, y, COL,
        "Camera Mode : %s  (M:切替)", modeName);
    y += LINE;
    DrawFormatString(10, y, COL,
        "Pos  (%.1f, %.1f, %.1f)", pos_.x, pos_.y, pos_.z);
    y += LINE;
    DrawFormatString(10, y, COL,
        "Angles (deg)  P:%.1f  Y:%.1f",
        angles_.x * (180.0f / DX_PI_F),
        angles_.y * (180.0f / DX_PI_F));
    y += LINE;

    if (mode_ == CameraMode::TopDown) {
        DrawFormatString(10, y, COL,
            "WASD:移動  QE:ズーム  高さ%.1f", pos_.y);
    }
    else {
        DrawFormatString(10, y, COL,
            "WASD:移動  Mouse:視点回転");
    }
}

void Camera::Release(void) {}

const VECTOR& Camera::GetPos(void)    const { return pos_; }
const VECTOR& Camera::GetAngles(void) const { return angles_; }
const CameraMode& Camera::GetMode(void)   const { return mode_; }