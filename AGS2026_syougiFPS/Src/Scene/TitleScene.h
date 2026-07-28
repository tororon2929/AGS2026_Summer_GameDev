#pragma once
#include "SceneBase.h"

class TitleScene : public SceneBase
{
public:
	TitleScene(void);
	~TitleScene(void) override;

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:
	int bgGraphHandle_;// ↓元の変数はすべてそのまま残しています


	int titleGraphHandle_;

	int logoX_;
	int logoY_;
	double logoScale_;

	int boardModelHandle_;
	VECTOR boardPos_;
	float boardRotY_;
	float boardRotSpeed_;

	float boardRotPitch_;
	float boardRotYaw_;

	float cameraRadius_;
	float cameraPitch_;
	float cameraYaw_;
	int prevMouseX_;
	int prevMouseY_;

	unsigned int white = GetColor(255, 255, 255);
	unsigned int yellow = GetColor(255, 255, 0);
	unsigned int black = GetColor(0, 0, 0);

	// ========================================================
	// ★追加: 難易度選択の状態管理用の変数
	// ========================================================
	enum class State
	{
		Title,        // 「PRESS SPACE KEY」の画面
		SelectLevel   // 難易度を選んでいる画面
	};
	State mState;         // 現在の画面状態
	int mSelectLevelIdx;  // 選択中の難易度 (0: EASY, 1: NORMAL, 2: HARD)
};