#include "Player.h"
#include "../Application.h"

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
	piece_model = MV1LoadModel((Application::PATH_MODEL + "Piece.mv1").c_str());

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
