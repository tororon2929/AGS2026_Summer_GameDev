#pragma once
#include "SceneBase.h"

class TitleScene : public SceneBase {
    bool mGoNext = false;
    bool mWasPressed = false;   // 前フレームのスペース状態
public:
    void Update() override;
    void Draw()   override;
    SceneBase* NextScene() override;
};