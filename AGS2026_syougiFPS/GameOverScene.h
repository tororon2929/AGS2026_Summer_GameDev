#pragma once
#include "SceneBase.h"

class GameOverScene : public SceneBase {
    bool mGoNext = false;
    bool mWasPressed = false;
public:
    void Update() override;
    void Draw()   override;
    SceneBase* NextScene() override;
};