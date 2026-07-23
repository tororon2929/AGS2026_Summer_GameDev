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

	float boardRotPitch_;
	float boardRotYaw_;

	float cameraRadius_;
	float cameraPitch_;
	float cameraYaw_;
	int prevMouseX_;
	int prevMouseY_;

	enum class State
	{
		Title,        // 「PRESS SPACE KEY」の画面
		SelectLevel   // 難易度を選んでいる画面
	};
	State mState;
	int mSelectLevelIdx;

	// ========================================================
	// ★追加: 画像描画用＆リアルタイム調整用デバッグ変数
	// ========================================================
	struct UITransform {
		float x;
		float y;
		float scale;
	};

	// 各UI画像のTransform（位置・スケール）
	UITransform uiSelect_;   // 「難易度」画像
	UITransform uiEasy_;     // 「簡単」画像
	UITransform uiNormal_;   // 「普通」画像
	UITransform uiHard_;     // 「難しい」画像
	UITransform uiCursor_;   // 「矢印」画像
	UITransform uiControl_;  // 「操作/決定」説明画像
	UITransform uiDecision_; // 「決定」画像

	int debugSelectTarget_;  // 現在キーボード調整中の対象 (0～5)
};