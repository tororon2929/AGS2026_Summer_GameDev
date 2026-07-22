#include "EnemyState.h"
#include"../Object/Enemy.h"
#include<cmath>

//金
void EnemyStateKin::Enter(Enemy* enemy)
{
	enemy->SetMaxHp(250);
	enemy->SetMoveSpeed(0.05f);
	enemy->SetRadius(2.0f);

	textureHandle_ = LoadGraph("Data/Enemy/Kin.png");
	if (textureHandle_ != -1)
	{
		enemy->ApplyTexture(textureHandle_);
	}
}

void EnemyStateKin::Update(Enemy* enemy, VECTOR playerPos)
{
	VECTOR currentPos = enemy->GetPos();
	VECTOR dir = VSub(playerPos, currentPos);
	dir.y = 0.0f;

	if (VSquareSize(dir) > 0.0f)
	{
		dir = VNorm(dir);
		VECTOR newPos = VAdd(currentPos, VScale(dir, enemy->GetMoveSpeed()));
		enemy->SetPos(newPos);

		float angleY = atan2f(dir.x, dir.z);
		Quaternion rot = Quaternion::Euler(VGet(0.0f, angleY + (DX_PI_F / 2.0f), DX_PI_F / 2.0f));
		enemy->SetRotation(rot);
	}
}

void EnemyStateKin::Exit(Enemy* enemy)
{
	if (textureHandle_ != -1)
	{
		DeleteGraph(textureHandle_);
		textureHandle_ = -1;
	}
}

//歩
void EnemyStateFu::Enter(Enemy* enemy)
{
	// 歩兵用のステータス設定
	enemy->SetMaxHp(100);
	enemy->SetMoveSpeed(0.12f);
	enemy->SetRadius(1.5f);

	// 歩兵用テクスチャロード＆適用
	textureHandle_ = LoadGraph("Data/Enemy/Fu.png");
	if (textureHandle_ != -1)
	{
		enemy->ApplyTexture(textureHandle_);
	}
}

void EnemyStateFu::Update(Enemy* enemy, VECTOR playerPos)
{
	VECTOR currentPos = enemy->GetPos();
	VECTOR dir = VSub(playerPos, currentPos);
	dir.y = 0.0f;

	// 歩兵AI
	if (VSquareSize(dir) > 0.0f)
	{
		dir = VNorm(dir);
		VECTOR newPos = VAdd(currentPos, VScale(dir, enemy->GetMoveSpeed()));
		enemy->SetPos(newPos);

		float angleY = atan2f(dir.x, dir.z);
		Quaternion rot = Quaternion::Euler(VGet(0.0f, angleY + (DX_PI_F / 2.0f), DX_PI_F / 2.0f));
		enemy->SetRotation(rot);
	}
}

void EnemyStateFu::Exit(Enemy* enemy)
{
	if (textureHandle_ != -1)
	{
		DeleteGraph(textureHandle_);
		textureHandle_ = -1;
	}
}
