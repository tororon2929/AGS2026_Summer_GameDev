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
    transform_.SetModel(
        ResourceManager::GetInstance().LoadModelDuplicate(
            ResourceManager::SRC::ENEMY_FU));

    transform_.pos = {0.0f, 50.0f, 15.0f };

    transform_.scl = { 1.0f, 1.0f, 1.0f };

    //transform_.quaRot = Quaternion::Euler(VGet(-DX_PI_F / 2.0f, 0.0f, 0.0f));

    transform_.Update();

    
}


void Enemy::Update(VECTOR playerPos)
{
    VECTOR dir = VSub(playerPos, transform_.pos);

    dir.y = 0.0f;

    if (VSquareSize(dir) > 0.0f)
    {
        dir = VNorm(dir);
        transform_.pos = VAdd(transform_.pos, VScale(dir, moveSpeed));
    }

    velocityY_ += -0.05f;
    transform_.pos.y += velocityY_;

    if (transform_.pos.y < floorHeight)
    {
        transform_.pos.y = floorHeight;
		velocityY_ = 0.0f;
    }

    transform_.Update();
}

void Enemy::Draw()
{
    //•`‰æ
    MV1DrawModel(transform_.modelId);

    DrawSphere3D(transform_.pos, radius_, 10, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);
}

void Enemy::Release()
{
}

void Enemy::Damage(int value)
{
    hp_ -= value;
    if (hp_ < 0)
    {
        hp_ = 0;
    }
}
