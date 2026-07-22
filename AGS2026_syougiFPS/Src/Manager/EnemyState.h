#pragma once
#include<DxLib.h>
#include<memory>

class Enemy;

class EnemyState
{
public:
	virtual ~EnemyState() = default;

	//
	virtual void Enter(Enemy* enmy) = 0;

	virtual void Update(Enemy* enmy, VECTOR playerPos) = 0;

	virtual void Exit(Enemy* enmy) {}
};

class EnemyStateKin : public EnemyState
{
public:
	void Enter(Enemy* enemy) override;
	void Update(Enemy* enemy, VECTOR playerPos) override;
	void Exit(Enemy* enmy)override;

private:
	int textureHandle_ = -1;
};

class EnemyStateFu :public EnemyState
{
public:
	void Enter(Enemy* enmy)override;
	void Update(Enemy* enmy, VECTOR playerPos)override;
	void Exit(Enemy* enmy)override;

private:
	int textureHandle_ = -1;
};



