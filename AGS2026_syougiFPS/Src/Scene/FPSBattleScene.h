#pragma once
#include <DxLib.h>
#include "SceneBase.h"

class FPSBattleScene : public SceneBase
{
public:

    FPSBattleScene();
    ~FPSBattleScene();

    void Init() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};