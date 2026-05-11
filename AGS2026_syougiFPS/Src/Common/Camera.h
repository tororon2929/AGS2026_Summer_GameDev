#pragma once
#include <DxLib.h>
#include "../Common/Quaternion.h"

enum class CameraMode {
    TopDown,
    FPS,
};

class Camera
{
public:
    Camera(void);
    ~Camera(void);
    void Init(void);
    void Update(void);
    void SetBeforeDraw(void);
    void DrawDebug(void);
    void Release(void);

    const VECTOR& GetPos(void)    const;
    const VECTOR& GetAngles(void) const;
    const CameraMode& GetMode(void)   const;

private:
    // 宣言順とコンストラクタ初期化リストを必ず合わせる
    CameraMode mode_;
    VECTOR     pos_;
    VECTOR     angles_;
    Quaternion rot_;
    bool       prevMKey_;

    // 俯瞰視点パラメータ
    static constexpr float TOP_HEIGHT = 300.0f;
    static constexpr float TOP_MOVE_SPEED = 3.0f;
    static constexpr float TOP_ZOOM_SPEED = 5.0f;
    static constexpr float TOP_HEIGHT_MIN = 50.0f;
    static constexpr float TOP_HEIGHT_MAX = 800.0f;

    // FPS視点パラメータ
    static constexpr float FPS_MOVE_SPEED = 0.2f;
    static constexpr float FPS_ROT_SPEED = 0.002f;
    static constexpr float FPS_PITCH_LIMIT = 1.5f;
    static constexpr float FPS_EYE_HEIGHT = 10.0f;

    void UpdateTopDown(void);
    void UpdateFPS(void);
    void SwitchMode(void);
    void ApplyCamera(void);
};