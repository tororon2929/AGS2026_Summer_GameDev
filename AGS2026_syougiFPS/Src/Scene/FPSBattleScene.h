#pragma once
#include <DxLib.h>
#include<vector>
#include "SceneBase.h"
#include "../Object/Enemy.h"
#include"../Object/Bullet.h"

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

    int hitCount = 0;
   
    //íeÇí«â¡Ç∑ÇÈä÷êî
    void AddBullet(VECTOR pos, VECTOR dir);
private:
	Enemy* enemy_ = nullptr;
    Player* player_ = nullptr;
    Camera* camera_ = nullptr;
    Stage* stage_ = nullptr;


    VECTOR lookDir;
    std::vector<Bullet*> bullets_;
};