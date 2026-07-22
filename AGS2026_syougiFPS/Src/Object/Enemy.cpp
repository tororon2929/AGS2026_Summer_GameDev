#include "Enemy.h"
#include "../Manager/EnemyState.h"
#include <DxLib.h>

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
    // モデル読み込み
    int modelId = MV1LoadModel("Data/Enemy/koma.mv1");
    if (modelId == -1)
    {
        return;
    }
    transform_.SetModel(modelId);

    // トランスフォーム基本設定
    transform_.scl = { 0.05f, 0.05f, 0.05f };
    MV1SetScale(transform_.modelId, transform_.scl);

    MV1SetMaterialDifColor(transform_.modelId, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
    MV1SetMaterialAmbColor(transform_.modelId, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));

    transform_.pos = { 0.0f, floorHeight_, 15.0f };
    transform_.quaRot = Quaternion::Euler(VGet(0.0f, -DX_PI_F / 2.0f, DX_PI_F / 2.0f));

    // 初期ステートの設定
    ChangeState(std::make_unique<EnemyStateKin>());

    transform_.Update();
    MV1SetPosition(transform_.modelId, transform_.pos);
}

void Enemy::ChangeState(std::unique_ptr<EnemyState> newState)
{
    if (!newState) return;

    // 現在のステートの後始末
    if (currentState_)
    {
        currentState_->Exit(this);
    }

    // 新しいステートに切り替え
    currentState_ = std::move(newState);

    // 新しいステートの初期化（パラメータ設定やテクスチャ変更）
    if (currentState_)
    {
        currentState_->Enter(this);
    }
}

void Enemy::Update(VECTOR playerPos)
{
    // 1. 各ステート固有のAI行動
    if (currentState_)
    {
        currentState_->Update(this, playerPos);
    }

    // 2. 共通の物理処理
    velocityY_ += -0.05f;
    transform_.pos.y += velocityY_;

    if (transform_.pos.y < floorHeight_)
    {
        transform_.pos.y = floorHeight_;
        velocityY_ = 0.0f;
    }

    // 3. 行列・表示の更新
    transform_.Update();
    MV1SetPosition(transform_.modelId, transform_.pos);
}

void Enemy::Draw()
{
    if (transform_.modelId != -1)
    {
        MV1DrawModel(transform_.modelId);
    }

    DrawSphere3D(transform_.pos, radius_, 10, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);
}

void Enemy::Release()
{
    // ステートのExitを呼び出してテクスチャ等を解放
    if (currentState_)
    {
        currentState_->Exit(this);
        currentState_.reset();
    }

    if (transform_.modelId != -1)
    {
        MV1DeleteModel(transform_.modelId);
        transform_.SetModel(-1);
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

// 正しいDXライブラリ仕様でのテクスチャ差し替え関数
void Enemy::ApplyTexture(int texHandle)
{
    if (transform_.modelId == -1 || texHandle == -1) return;

    int materialNum = MV1GetMaterialNum(transform_.modelId);
    for (int i = 0; i < materialNum; i++)
    {
        int texIndex = MV1GetMaterialDifMapTexture(transform_.modelId, i);
        if (texIndex != -1)
        {
            MV1SetTextureGraphHandle(transform_.modelId, texIndex, texHandle, FALSE);
        }
    }
}
