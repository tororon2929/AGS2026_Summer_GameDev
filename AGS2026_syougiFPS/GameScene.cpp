#include "GameScene.h"
#include "GameOverScene.h"
#include "DxLib.h"

void GameScene::Update() {
    bool nowPress = (CheckHitKey(KEY_INPUT_SPACE) != 0);
    if (nowPress && !mWasPressed) {
        mGoNext = true;
    }
    mWasPressed = nowPress;
}

void GameScene::Draw() {
    DrawString(200, 200, "=== GAME ===", GetColor(100, 255, 100));
    DrawString(140, 260, "Press SPACE to Game Over", GetColor(200, 200, 200));
}

SceneBase* GameScene::NextScene() {
    if (mGoNext) return new GameOverScene();
    return nullptr;
}