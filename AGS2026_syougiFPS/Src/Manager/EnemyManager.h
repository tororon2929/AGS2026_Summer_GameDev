#pragma once
#include<DxLib.h>
#include<memory>

class Enemy;

class EnemyManager
{
public:
	virtual ~EnemyManager() = default;

	//
	virtual void Enter(Enemy* enemy) = 0;

	virtual void Update(Enemy* enemy, VECTOR playerPos) = 0;

	virtual void Exit(Enemy* enemy) {}
};

class EnemyStateKin : public EnemyManager
{
public:
	void Enter(Enemy* enemy) override;
	void Update(Enemy* enemy, VECTOR playerPos) override;
	void Exit(Enemy* enmy)override;

private:
	int textureHandle_ = -1;
};

class EnemyStateFu :public EnemyManager
{
public:
	void Enter(Enemy* enemy)override;
	void Update(Enemy* enemy, VECTOR playerPos)override;
	void Exit(Enemy* enemy)override;

private:
	int textureHandle_ = -1;
};

class EnemyStateGin :public EnemyManager
{
public:
	void Enter(Enemy* enemy)override;
	void Update(Enemy* enemy, VECTOR playerPos)override;
	void Exit(Enemy* enemy)override;

private:
	int textureHandle_ = -1;
};

class EnemyStateKousya :public EnemyManager
{
public:
	void Enter(Enemy* enemy)override;
	void Update(Enemy* enemy, VECTOR playerPos)override;
	void Exit(Enemy* enemy)override;

private:
	int textureHandle_ = -1;
};

class EnemyStateOu :public EnemyManager
{
public:
	void Enter(Enemy* enemy)override;
	void Update(Enemy* enemy, VECTOR playerPos)override;
	void Exit(Enemy* enemy)override;

private:
	int textureHandle_ = -1;
};

class EnemyStateKaku :public EnemyManager
{
public:
	void Enter(Enemy* enemy)override;
	void Update(Enemy* enemy, VECTOR playerPos)override;
	void Exit(Enemy* enemy)override;

private:
	int textureHandle_ = -1;
};

class EnemyStateKeima :public EnemyManager
{
public:
	void Enter(Enemy* enemy)override;
	void Update(Enemy* enemy, VECTOR playerPos)override;
	void Exit(Enemy* enemy)override;

private:
	int textureHandle_ = -1;
};

class EnemyStateGyoku :public EnemyManager
{
public:
	void Enter(Enemy* enemy)override;
	void Update(Enemy* enemy, VECTOR playerPos)override;
	void Exit(Enemy* enemy)override;

private:
	int textureHandle_ = -1;
};

class EnemyStateHisya :public EnemyManager
{
public:
	void Enter(Enemy* enemy)override;
	void Update(Enemy* enemy, VECTOR playerPos)override;
	void Exit(Enemy* enemy)override;

private:
	int textureHandle_ = -1;
};