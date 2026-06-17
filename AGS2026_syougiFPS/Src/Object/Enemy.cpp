#include "Enemy.h"
#include "../Manager/ResourceManager.h"



Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
    /*transform_.SetModel(
        ResourceManager::GetInstance().LoadModelDuplicate(
            ResourceManager::SRC::Fu));*/

    transform_.pos = {0.0f, 30.0f, 15.0f };

    transform_.scl = { 1.0f, 1.0f, 1.0f };

    //transform_.quaRot = Quaternion::Euler(VGet(-DX_PI_F / 2.0f, 0.0f, 0.0f));

    transform_.Update();

    
}


void Enemy::Update()
{
   
    transform_.Update();
}

void Enemy::Draw()
{
    if (isDummy_) {
        DrawSphere3D(
            transform_.pos, 5.0f, 16, GetColor(255, 255, 0), 
            GetColor(255, 255, 255), TRUE);

        //âÊñ ÇÃìKìñÇ»èÍèäÇ…ç¿ïWÇï\é¶Ç∑ÇÈ
        DrawFormatString(0, 50, GetColor(255, 255, 255), "Enemy Pos: x:%.1f y:%.1f z:%.1f",
            transform_.pos.x, transform_.pos.y, transform_.pos.z);
    }
    else
    {
        if (transform_.modelId != -1) {
            MV1DrawModel(transform_.modelId);
        }
    };
}

void Enemy::Release()
{
}