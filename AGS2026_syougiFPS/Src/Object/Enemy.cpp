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
            ResourceManager::SRC::Fu));

    transform_.pos = { 0.0f, 0.0f, 15.0f };

    transform_.scl = { 1.0f, 1.0f, 1.0f };

    transform_.quaRot = Quaternion::Euler(VGet(-DX_PI_F / 2.0f, 0.0f, 0.0f));

    transform_.Update();

    
}


void Enemy::Update()
{
    

    transform_.Update();
}

void Enemy::Draw()
{
    MV1DrawModel(transform_.modelId);
}

void Enemy::Release()
{
}