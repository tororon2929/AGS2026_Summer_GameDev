#include "GameOverScene.h"
#include "TitleScene.h"
#include "DxLib.h"

void GameOverScene::Update() {
    bool nowPress = (CheckHitKey(KEY_INPUT_SPACE) != 0);
    if (nowPress && !mWasPressed) {
        mGoNext = true;
    }
    mWasPressed = nowPress;
}

void GameOverScene::Draw() {
    DrawString(190, 200, "=== GAME OVER ===", GetColor(255, 80, 80));
    DrawString(150, 260, "Press SPACE to Title", GetColor(200, 200, 200));
}

SceneBase* GameOverScene::NextScene() {
    if (mGoNext) return new TitleScene();
    return nullptr;
}