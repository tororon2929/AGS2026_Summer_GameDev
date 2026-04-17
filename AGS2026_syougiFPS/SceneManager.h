#pragma once
#include "SceneBase.h"
#include "Fade.h"

class SceneManager {
    SceneBase* mCurrent = nullptr;
    SceneBase* mNext = nullptr;   // Ø‘Öæ‚ğˆê•Û‘¶
    Fade       mFade;

public:
    explicit SceneManager(SceneBase* initialScene);
    ~SceneManager();

    void Update();
    void Draw();
    bool IsRunning() const { return mCurrent != nullptr; }
};