#include "TitleScene.h"
#include "GameScene.h"
#include "DxLib.h"

void TitleScene::Update() {
    // 今フレーム押されていて、前フレームは押されていなかった → 押した瞬間
    bool nowPress = (CheckHitKey(KEY_INPUT_SPACE) != 0);
    if (nowPress && !mWasPressed) {
        mGoNext = true;
    }
    mWasPressed = nowPress;
}

void TitleScene::Draw() {
    DrawString(200, 200, "=== TITLE ===", GetColor(255, 255, 255));
    DrawString(160, 260, "Press SPACE to Start", GetColor(200, 200, 200));
}

SceneBase* TitleScene::NextScene() {
    if (mGoNext) return new GameScene();
    return nullptr;
}