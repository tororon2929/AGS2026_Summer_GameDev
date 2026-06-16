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
	int titleGraphHandle_;

	int logoX_;
	int logoY_;
	double logoScale_;

	int boardModelHandle_;
	VECTOR boardPos_;
	float boardRotY_;
	float boardRotSpeed_;

	// --- 将棋盤のデバッグ回転用変数 ★追加 ---
	float boardRotPitch_; // X軸回転（縦回転）
	float boardRotYaw_;   // Y軸回転（横回転）

	// --- デバッグカメラ操作用変数 ---
	float cameraRadius_;
	float cameraPitch_;
	float cameraYaw_;
	int prevMouseX_;
	int prevMouseY_;
};