#include "Enemy.h"
#include <DxLib.h>
Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
    modelHandle = MV1LoadModel("Data/Enemy/Fu_Enemy.mv1");
        transform_.SetModel(modelHandle);

    transform_.pos = {0.0f, 50.0f, 15.0f };

    transform_.scl = { 0.05f, 0.05f, 0.05f };
    MV1SetScale(transform_.modelId, transform_.scl);

    MV1SetMaterialDifColor(transform_.modelId, 0, GetColorF(0.8f, 0.6f, 0.4f, 1.0f));

    transform_.pos = { 0.0f, floorHeight, 15.0f };
    MV1SetPosition(transform_.modelId, transform_.pos);

    transform_.quaRot = Quaternion::Euler(VGet(0.0f, -DX_PI_F / 2.0f, DX_PI_F / 2.0f));

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
    //描画
    MV1DrawModel(transform_.modelId);

    DrawSphere3D(transform_.pos, radius_, 10, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);
}

void Enemy::Release()
{
    if (transform_.modelId != -1)
    {
        MV1DeleteModel(transform_.modelId);
        transform_.SetModel(-1);
    }
    else
    {
        DrawFormatString(0, 120, GetColor(255, 0, 0), "敵のモデルの読み込みに失敗しました");
        DrawFormatString(0, 140, GetColor(255, 0, 0), "ファイルの場所や名前が正しいか確認してください。");
    }
}

void Enemy::Damage(int value)
{
    hp_ -= value;
    if (hp_ < 0)
    {
        hp_ = 0;
    }
}
