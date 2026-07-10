#pragma once
#include <DxLib.h>
#include<vector>
#include "SceneBase.h"
#include "../Object/Enemy.h"
#include"../Object/Bullet.h"
#include"../Application.h"
#include"../Manager/LightManager.h"

class Enemy;
class Player;
class Camera;
class Stage;
class Bullet;

class FPSBattleScene : public SceneBase
{
public:

    FPSBattleScene();
    ~FPSBattleScene();

    void Init() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    int hitCount_ = 0;
   
    //íeÇí«â¡Ç∑ÇÈä÷êî
    void AddBullet(VECTOR pos, VECTOR dir);
private:
	Enemy* enemy_ = nullptr;
    Player* player_ = nullptr;
    Camera* camera_ = nullptr;
    Stage* stage_ = nullptr;
    LightManager lightManager_;

    VECTOR lookDir;
    std::vector<Bullet*> bullets_;

    float limitx = 25.0f;
    float limitz = 25.0f;
    float y = 25.0f;
    float time = GetNowCount() / 300.0f;

    int crosshairImg_ = -1;
    int centerX = Application::SCREEN_SIZE_X / 2;
    int centerY = Application::SCREEN_SIZE_Y / 2;
    unsigned int auraColor = GetColor(255, 0, 0);
   
};