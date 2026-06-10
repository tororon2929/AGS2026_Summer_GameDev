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

    transform_.pos = { 100, 0, 100 };
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