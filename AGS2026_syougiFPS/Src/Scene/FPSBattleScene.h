#pragma once
#include <DxLib.h>
#include "SceneBase.h"
#include "../Object/Enemy.h"

class Enemy;
class Player;

class FPSBattleScene : public SceneBase
{
public:

    FPSBattleScene();
    ~FPSBattleScene();

    void Init() override;
    void Update() override;
    void Draw() override;
    void Release() override;
   

private:
	Enemy* enemy_ = nullptr;
    Player* player_ = nullptr;
};