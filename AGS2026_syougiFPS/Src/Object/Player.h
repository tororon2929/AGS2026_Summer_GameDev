#pragma once
#include<DxLib.h>
class Player
{
private:
	// スピード
	static constexpr float SPEED_MOVE = 5.0f;
	static constexpr float SPEED_RUN = 10.0f;

	// ジャンプ力
	static constexpr float POW_JUMP = 35.0f;

	//モデルID
	int piece_model;

	// 状態
	enum class STATE
	{
		NONE,
		PLAY,
		WARP_RESERVE,
		WARP_MOVE,
		DEAD,
		VICTORY,
		END
	};

	enum class piece
	{
		HO,
		ROOK,
		KNIGHT,
		BISHOP,
		QUEEN,
		OU
	};

	Player(void);
	~Player(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

public:
	//状態管理
	STATE state;

	//移動スピード
	float speed;

	//移動方向
	VECTOR moveDir;

	// ジャンプ量
	VECTOR jumpPow_;

	// ジャンプ判定
	bool isJump_;
  

	// 状態遷移
	void ChangeState(STATE state);
	void ChangeStateNone(void);
	void ChangeStatePlay(void);

};

