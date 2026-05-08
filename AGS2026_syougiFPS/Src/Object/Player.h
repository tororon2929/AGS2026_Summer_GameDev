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

	void Init(void);
	void Update(void);
	void Draw(void);

public:
	
};

