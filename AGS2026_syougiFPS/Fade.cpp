#include "Fade.h"
#include "DxLib.h"

void Fade::StartFadeOut() {
    mState = FadeState::FadeOut;
    mAlpha = 0;
}

void Fade::StartFadeIn() {
    mState = FadeState::FadeIn;
    mAlpha = 255;
}

void Fade::Update() {
    switch (mState) {

    case FadeState::FadeOut:
        mAlpha += mSpeed;
        if (mAlpha >= 255) {
            mAlpha = 255;
            mState = FadeState::Black;   // 真っ暗 → 1フレーム待つ
        }
        break;

    case FadeState::Black:
        // SceneManager 側で IsBlack() を検知してシーン切替 + StartFadeIn() を呼ぶ
        // ここでは何もしない（1フレーム止まる）
        break;

    case FadeState::FadeIn:
        mAlpha -= mSpeed;
        if (mAlpha <= 0) {
            mAlpha = 0;
            mState = FadeState::None;    // フェード完了
        }
        break;

    case FadeState::None:
    default:
        break;
    }
}

void Fade::Draw() const {
    if (mAlpha <= 0) return;

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, mAlpha);
    DrawBox(0, 0, 640, 480, GetColor(0, 0, 0), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}