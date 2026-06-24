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
	// ★追加: タイトルシーン内での状態管理
	enum class State
	{
		Title,        // スペースキーを押す前の状態
		SelectLevel   // 難易度を選択している状態
	};
	State mState;     // 現在の状態

	// ★追加: 選択中の難易度インデックス (0:簡単, 1:普通, 2:難しい)
	int mSelectLevelIdx;

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
};