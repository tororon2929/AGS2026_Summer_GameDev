#pragma once

// フェードの状態
enum class FadeState {
    None,       // フェードなし（通常状態）
    FadeOut,    // 暗転中
    Black,      // 真っ暗（シーン切替タイミング）
    FadeIn,     // 明転中
};

class Fade {
    FadeState mState = FadeState::None;
    int       mAlpha = 0;       // 現在のアルファ値 0?255
    int       mSpeed = 8;       // 1フレームの変化量

public:
    // フェードアウト開始
    void StartFadeOut();

    // 毎フレーム呼ぶ
    void Update();

    // 半透明黒矩形を画面に描画
    void Draw() const;

    // シーンを切り替えていいタイミングか（真っ暗になった瞬間）
    bool IsBlack()    const { return mState == FadeState::Black; }

    // フェードが完全に終わったか
    bool IsFinished() const { return mState == FadeState::None && mAlpha == 0; }

    // フェード中か（None以外）
    bool IsFading()   const { return mState != FadeState::None; }

    // フェードインを開始（SceneManager が切替後に呼ぶ）
    void StartFadeIn();

    FadeState GetState() const { return mState; }
};