#pragma once
#include "SceneBase.h"
#include "Board.h"
#include "Cursor.h"

class GameScene : public SceneBase {
    bool mGoNext = false;
    bool mWasPressed = false;

    Board mBoard;
    Cursor mCursor;

    bool mSelected = false;
    int selX = 0;
    int selY = 0;

public:
    GameScene();

    void Update() override;
    void Draw() override;
    SceneBase* NextScene() override;
};