#include "EnemyManager.h"
#include"../Object/Enemy.h"
#include<cmath>

//金
void EnemyStateKin::Enter(Enemy* enemy)
{
	//金のステータス
	enemy->SetMaxHp(250);
	enemy->SetMoveSpeed(0.02f);
	enemy->SetRadius(2.0f);

	//金テクスチャー適用
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

	//金AI
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
	// 歩兵のステータス設定
	enemy->SetMaxHp(100);
	enemy->SetMoveSpeed(0.03f);
	enemy->SetRadius(1.5f);

	// 歩兵テクスチャロード
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

//銀
void EnemyStateGin::Enter(Enemy* enemy)
{
	//銀のステータス
	enemy->SetMaxHp(150);
	enemy->SetMoveSpeed(0.03f);
	enemy->SetRadius(2.0f);

	//銀テクスチャー適用
	textureHandle_ = LoadGraph("Data/Enemy/Gin.png");
	if (textureHandle_ != -1)
	{
		enemy->ApplyTexture(textureHandle_);
	}
}

void EnemyStateGin::Update(Enemy* enemy, VECTOR playerPos)
{
	VECTOR currentPos = enemy->GetPos();
	VECTOR dir = VSub(playerPos, currentPos);
	dir.y = 0.0f;

	//銀AI
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

void EnemyStateGin::Exit(Enemy* enemy)
{
	if (textureHandle_ != -1)
	{
		DeleteGraph(textureHandle_);
		textureHandle_ = -1;
	}
}

//香車
void EnemyStateKousya::Enter(Enemy* enemy)
{
	//香車のステータス
	enemy->SetMaxHp(130);
	enemy->SetMoveSpeed(0.10f);
	enemy->SetRadius(0.8f);

	//香車テクスチャー適用
	textureHandle_ = LoadGraph("Data/Enemy/Kousya.png");
	if (textureHandle_ != -1)
	{
		enemy->ApplyTexture(textureHandle_);
	}
}

void EnemyStateKousya::Update(Enemy* enemy, VECTOR playerPos)
{
	VECTOR currentPos = enemy->GetPos();
	VECTOR dir = VSub(playerPos, currentPos);
	dir.y = 0.0f;

	//香車AI
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

void EnemyStateKousya::Exit(Enemy* enemy)
{
	if (textureHandle_ != -1)
	{
		DeleteGraph(textureHandle_);
		textureHandle_ = -1;
	}
}

//王
void EnemyStateOu::Enter(Enemy* enemy)
{
	//王のステータス
	enemy->SetMaxHp(300);
	enemy->SetMoveSpeed(0.08f);
	enemy->SetRadius(2.0f);

	//王テクスチャー適用
	textureHandle_ = LoadGraph("Data/Enemy/Ou.png");
	if (textureHandle_ != -1)
	{
		enemy->ApplyTexture(textureHandle_);
	}
}

void EnemyStateOu::Update(Enemy* enemy, VECTOR playerPos)
{
	VECTOR currentPos = enemy->GetPos();
	VECTOR dir = VSub(playerPos, currentPos);
	dir.y = 0.0f;

	//王AI
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

void EnemyStateOu::Exit(Enemy* enemy)
{
	if (textureHandle_ != -1)
	{
		DeleteGraph(textureHandle_);
		textureHandle_ = -1;
	}
}

//角
void EnemyStateKaku::Enter(Enemy* enemy)
{
	//角のステータス
	enemy->SetMaxHp(150);
	enemy->SetMoveSpeed(0.04f);
	enemy->SetRadius(4.0f);

	//角テクスチャー適用
	textureHandle_ = LoadGraph("Data/Enemy/Kaku.png");
	if (textureHandle_ != -1)
	{
		enemy->ApplyTexture(textureHandle_);
	}
}

void EnemyStateKaku::Update(Enemy* enemy, VECTOR playerPos)
{
	VECTOR currentPos = enemy->GetPos();
	VECTOR dir = VSub(playerPos, currentPos);
	dir.y = 0.0f;

	//角AI
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

void EnemyStateKaku::Exit(Enemy* enemy)
{
	if (textureHandle_ != -1)
	{
		DeleteGraph(textureHandle_);
		textureHandle_ = -1;
	}
}

//桂馬
void EnemyStateKeima::Enter(Enemy* enemy)
{
	//桂馬のステータス
	enemy->SetMaxHp(150);
	enemy->SetMoveSpeed(0.20f);
	enemy->SetRadius(0.3f);

	//桂馬テクスチャー適用
	textureHandle_ = LoadGraph("Data/Enemy/Keima.png");
	if (textureHandle_ != -1)
	{
		enemy->ApplyTexture(textureHandle_);
	}
}

void EnemyStateKeima::Update(Enemy* enemy, VECTOR playerPos)
{
	VECTOR currentPos = enemy->GetPos();
	VECTOR dir = VSub(playerPos, currentPos);
	dir.y = 0.0f;

	//桂馬AI
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

void EnemyStateKeima::Exit(Enemy* enemy)
{
	if (textureHandle_ != -1)
	{
		DeleteGraph(textureHandle_);
		textureHandle_ = -1;
	}
}

//玉
void EnemyStateGyoku::Enter(Enemy* enemy)
{
	//玉のステータス
	enemy->SetMaxHp(250);
	enemy->SetMoveSpeed(0.05f);
	enemy->SetRadius(2.0f);

	//玉テクスチャー適用
	textureHandle_ = LoadGraph("Data/Enemy/Gyoku.png");
	if (textureHandle_ != -1)
	{
		enemy->ApplyTexture(textureHandle_);
	}
}

void EnemyStateGyoku::Update(Enemy* enemy, VECTOR playerPos)
{
	VECTOR currentPos = enemy->GetPos();
	VECTOR dir = VSub(playerPos, currentPos);
	dir.y = 0.0f;

	//玉AI
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

void EnemyStateGyoku::Exit(Enemy* enemy)
{
	if (textureHandle_ != -1)
	{
		DeleteGraph(textureHandle_);
		textureHandle_ = -1;
	}
}

//飛車
void EnemyStateHisya::Enter(Enemy* enemy)
{
	//飛車のステータス
	enemy->SetMaxHp(100);
	enemy->SetMoveSpeed(0.08f);
	enemy->SetRadius(2.0f);

	//飛車テクスチャー適用
	textureHandle_ = LoadGraph("Data/Enemy/Hisya.png");
	if (textureHandle_ != -1)
	{
		enemy->ApplyTexture(textureHandle_);
	}
}

void EnemyStateHisya::Update(Enemy* enemy, VECTOR playerPos)
{
	VECTOR currentPos = enemy->GetPos();
	VECTOR dir = VSub(playerPos, currentPos);
	dir.y = 0.0f;

	//飛車AI
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

void EnemyStateHisya::Exit(Enemy* enemy)
{
	if (textureHandle_ != -1)
	{
		DeleteGraph(textureHandle_);
		textureHandle_ = -1;
	}
}
