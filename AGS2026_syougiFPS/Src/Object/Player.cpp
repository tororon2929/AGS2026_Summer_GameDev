#include "Player.h"
#include "../Application.h"
#include "../Manager/InputManager.h"
#include "../Utility/AsoUtility.h"	

Player::Player(void)
	:piece_model(-1)
{
}
Player::~Player(void)
{
}

void Player::Init(void)
{
	//モデルの読み込み
	piece_model = MV1LoadModel((Application::PATH_MODEL + "Fu.mv1").c_str());

	//座標の決定
	pos = VGet(0.0f, 0.0f, 0.0f);

	//モデルの位置決定
	MV1SetPosition(piece_model, pos);
    
	//サイズ調整
	MV1SetScale(piece_model, VGet(1.0f, 1.0f, 1.0f));

}

void Player::Update(void)
{
	//モデルの位置更新
	MV1SetPosition(piece_model, pos);
}

void Player::Draw(void)
{
	//モデルの描画
	MV1DrawModel(piece_model);
}

void Player::Release(void)
{
	//モデルの解放
	MV1DeleteModel(piece_model);
}

void Player::ChangeState(STATE state)
{
}

void Player::ChangeStateNone(void)
{
}

void Player::ChangeStatePlay(void)
{
}

void Player::ProcessMove(void)
{
	auto& ins = InputManager::GetInstance();

	//移動量をゼロ
	movePow_ = AsoUtility::VECTOR_ZERO;

	VECTOR dir = AsoUtility::VECTOR_ZERO;

	//移動
	if (ins.IsNew(KEY_INPUT_W))
	{
		dir = AsoUtility::DIR_F;
	}

	if(ins.IsNew(KEY_INPUT_S))
	{
		dir = AsoUtility::DIR_B;
	}

	if(ins.IsNew(KEY_INPUT_A))
	{
		dir = AsoUtility::DIR_L;
	}

	if(ins.IsNew(KEY_INPUT_D))
	{
		dir = AsoUtility::DIR_R;
	}

	if (!AsoUtility::EqualsVZero(dir)) {

		//移動処理
		speed = SPEED_MOVE;
		moveDir = dir;
		movePow_ = VScale(moveDir, speed);
	}
	else
	{
		//移動していない場合は、移動量をゼロ
		speed = 0.0f;
		moveDir = AsoUtility::VECTOR_ZERO;
		movePow_ = AsoUtility::VECTOR_ZERO;
	}

}

void Player::ProcessJump(void)
{
	bool isHit = CheckHitKey(KEY_INPUT_SPACE);

	if (isHit && (isJump_))
	{
		isJump_ = true;
	}
}

void Player::Collision(void)
{
	//現在座標を起点に移動後の座標を決める
	movePow_ = VAdd(pos, movePow_);
}

void Player::CollisionGravity(void)
{
}
