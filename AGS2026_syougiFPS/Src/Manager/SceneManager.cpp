#include <chrono>
#include <DxLib.h>
#include "../Common/Fader.h"
#include "../Scene/TitleScene.h"
#include "../Common/Camera.h"
#include "MiniCamera.h"
#include "SceneManager.h"
#include "../Scene/GameScene.h"
#include "../Scene/ResultScene.h"
#include "../Scene/FPSBattleScene.h"
#include"../Manager/InputManager.h"
#include"../Object/PlayBpard.h"

SceneManager* SceneManager::instance_ = nullptr;

SceneManager::~SceneManager()
{
	ClearPlayBoard();
}

void SceneManager::ClearPlayBoard()
{
	if (mPlayBoard)
	{
		delete mPlayBoard;
		mPlayBoard = nullptr;
	}
}
void SceneManager::CreateInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new SceneManager();
	}
	instance_->Init();
}

SceneManager& SceneManager::GetInstance(void)
{
	return *instance_;

}

void SceneManager::Init(void)
{
	sceneId_ = SCENE_ID::TITLE;
	waitSceneId_ = SCENE_ID::NONE;

	// 変数の初期化
	isPaused_ = false;
	isEscapeKeyOld_ = false;
	pauseSelectIdx_ = 0;

	// --- 追加: 戦闘結果フラグの初期化 ---
	mIsPlayerWin = false;
	mHasBattleResult = false;

	// フェード機能の初期化
	fader_ = new Fader();
	fader_->Init();

	// カメラ
	camera_ = new Camera();
	camera_->Init();

	isSceneChanging_ = false;

	// デルタタイム
	preTime_ = std::chrono::system_clock::now();

	// 3D用の設定
	Init3D();

	// 初期シーンの設定
	DoChangeScene(SCENE_ID::TITLE);
}

void SceneManager::Init3D(void)
{
	SetBackgroundColor(BACKGROUND_COLOR_R, BACKGROUND_COLOR_G, BACKGROUND_COLOR_B);
	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);
	SetUseBackCulling(true);
	SetUseLighting(true);
	ChangeLightTypeDir({ 0.00f, -1.00f, 1.00f });
}

void SceneManager::Update(void)
{
	if (scene_ == nullptr)
	{
		return;
	}

	auto nowTime = std::chrono::system_clock::now();
	deltaTime_ = static_cast<float>(
		std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - preTime_).count() / 1000000000.0);
	preTime_ = nowTime;

	// パッドの入力を取得
	int padInput = GetJoypadInputState(DX_INPUT_PAD1);

	// ----------------------------------------------------
	// ポーズの切り替え (ESCキー または コントローラーのSTARTボタン相当)
	// ※一般的に DXライブラリの PAD_INPUT_M はSTARTボタンやOPTIONSボタンに割り当てられます
	// ----------------------------------------------------
	bool isEscapeKeyNow = (CheckHitKey(KEY_INPUT_ESCAPE) == 1) || ((padInput & PAD_INPUT_START) != 0);
	if (isEscapeKeyNow && !isEscapeKeyOld_)
	{
		if (sceneId_ == SCENE_ID::TITLE)
		{
			isPaused_ = !isPaused_;
			pauseSelectIdx_ = 2; // はい（ゲーム終了）
		}
		else
		{
			isPaused_ = !isPaused_;
			pauseSelectIdx_ = 0; // 閉じる

			if (!isPaused_)
			{
				ResetDeltaTime();
			}
		}
		WaitTimer(200); // ポーズがガタガタ高速で切り替わるのを防ぐ
	}
	isEscapeKeyOld_ = isEscapeKeyNow;

	// ----------------------------------------------------
	// ポーズ（一時停止）中のメニュー操作処理
	// ----------------------------------------------------
	if (isPaused_)
	{
		// 【上移動】Wキー または 十字キー上
		if ((CheckHitKey(KEY_INPUT_W) == 1) || ((padInput & PAD_INPUT_UP) != 0))
		{
			if (sceneId_ == SCENE_ID::TITLE)
			{
				pauseSelectIdx_ = (pauseSelectIdx_ == 0) ? 2 : 0;
			}
			else
			{
				pauseSelectIdx_ = (pauseSelectIdx_ - 1 + static_cast<int>(PauseMenu::Length)) % static_cast<int>(PauseMenu::Length);
			}
			WaitTimer(150);
		}

		// 【下移動】Sキー または 十字キー下
		if ((CheckHitKey(KEY_INPUT_S) == 1) || ((padInput & PAD_INPUT_DOWN) != 0))
		{
			if (sceneId_ == SCENE_ID::TITLE)
			{
				pauseSelectIdx_ = (pauseSelectIdx_ == 0) ? 2 : 0;
			}
			else
			{
				pauseSelectIdx_ = (pauseSelectIdx_ + 1) % static_cast<int>(PauseMenu::Length);
			}
			WaitTimer(150);
		}

		// 【決定】SPACE / ENTER / パッドのAボタン(決定)
		if ((CheckHitKey(KEY_INPUT_SPACE) == 1) || (CheckHitKey(KEY_INPUT_RETURN) == 1) || ((padInput & PAD_INPUT_A) != 0))
		{
			if (pauseSelectIdx_ == 0) // Resume
			{
				isPaused_ = false;
				ResetDeltaTime();
			}
			else if (pauseSelectIdx_ == 1) // GoToTitle
			{
				isPaused_ = false;
				ChangeScene(SCENE_ID::TITLE);
			}
			else if (pauseSelectIdx_ == 2) // ExitGame
			{
				DxLib_End();
				exit(0);
			}
			WaitTimer(150);
		}

		return; // ポーズ中はこれ以降のゲーム進行をスキップ
	}

	// 通常更新処理
	fader_->Update();
	if (isSceneChanging_)
	{
		Fade();
	}
	else
	{
		scene_->Update();
	}
}

void SceneManager::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();

	// 各シーンの描画処理
	scene_->Draw();

	// 暗転・明転
	fader_->Draw();

	// ----------------------------------------------------
	// ポーズメニュー UI の描画
	// ----------------------------------------------------
	if (isPaused_)
	{
		// 本番用のフォントサイズを指定 (標準的な24サイズで固定)
		SetFontSize(24);

		// 画面全体をうっすら暗くするマスク
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
		DrawBox(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		unsigned int white = GetColor(255, 255, 255);
		unsigned int yellow = GetColor(255, 255, 0);

		auto getMenuColor = [&](int idx) { return (pauseSelectIdx_ == idx) ? yellow : white; };
		auto getMenuArrow = [&](int idx) { return (pauseSelectIdx_ == idx) ? "-> " : "   "; };

		// 【パターンA】タイトルシーンでのESC（ゲーム終了確認）
		if (sceneId_ == SCENE_ID::TITLE)
		{
			DrawFormatString(640, 260, white, "ゲームを終了しますか?");

			char noStr[64], yesStr[64];
			sprintf_s(noStr, "%s いいえ", getMenuArrow(0));
			sprintf_s(yesStr, "%s はい", getMenuArrow(2));

			DrawFormatString(710, 360, getMenuColor(0), noStr);
			DrawFormatString(710, 410, getMenuColor(2), yesStr);
		}
		// 【パターンB】通常のポーズメニュー
		else
		{
			DrawFormatString(730, 380, white, "ポーズ");

			char closeStr[64], titleBackStr[64], exitStr[64];
			sprintf_s(closeStr, "%s 閉じる", getMenuArrow(0));
			sprintf_s(titleBackStr, "%s タイトルに戻る", getMenuArrow(1));
			sprintf_s(exitStr, "%s ゲームを終了する", getMenuArrow(2));

			DrawFormatString(670, 480, getMenuColor(0), closeStr);
			DrawFormatString(670, 540, getMenuColor(1), titleBackStr);
			DrawFormatString(670, 600, getMenuColor(2), exitStr);
		}

		// 操作説明
		DrawFormatString(500, 710, white, "PC[W/S]CL[上/下/十字]: 移動    PC[SPACE]CL[A]: 決定");
	}
}

void SceneManager::Destroy(void)
{
	scene_->Release();
	delete scene_;
	delete fader_;
	camera_->Release();
	delete camera_;
	delete instance_;
}

void SceneManager::ChangeScene(SCENE_ID nextId)
{
	waitSceneId_ = nextId;
	fader_->SetFade(Fader::STATE::FADE_OUT);
	isSceneChanging_ = true;
}

SceneManager::SCENE_ID SceneManager::GetSceneID(void)
{
	return sceneId_;
}

float SceneManager::GetDeltaTime(void) const
{
	return deltaTime_;
}

Camera* SceneManager::GetCamera(void) const
{
	return camera_;
}

SceneManager::SceneManager(void)
{
	sceneId_ = SCENE_ID::NONE;
	waitSceneId_ = SCENE_ID::NONE;
	scene_ = nullptr;
	fader_ = nullptr;
	isSceneChanging_ = false;
	deltaTime_ = 1.0f / 60.0f;
	camera_ = nullptr;
}

void SceneManager::ResetDeltaTime(void)
{
	deltaTime_ = 0.016f;
	preTime_ = std::chrono::system_clock::now();
}

void SceneManager::DoChangeScene(SCENE_ID sceneId)
{
	sceneId_ = sceneId;
	isPaused_ = false;
	if (scene_ != nullptr)
	{
		scene_->Release();
		delete scene_;
	}

	switch (sceneId_)
	{
	case SCENE_ID::TITLE:
		scene_ = new TitleScene();
		break;
	case SCENE_ID::GAME:
		scene_ = new GameScene();
		break;
	case SCENE_ID::FPS_BATTLE:
		scene_ = new FPSBattleScene();
		break;
	case SCENE_ID::RESULT:
		scene_ = new ResultScene();
		break;
	}

	scene_->Init();
	ResetDeltaTime();
	waitSceneId_ = SCENE_ID::NONE;
}

void SceneManager::Fade(void)
{
	Fader::STATE fState = fader_->GetState();
	switch (fState)
	{
	case Fader::STATE::FADE_IN:
		if (fader_->IsEnd())
		{
			fader_->SetFade(Fader::STATE::NONE);
			isSceneChanging_ = false;
		}
		break;
	case Fader::STATE::FADE_OUT:
		if (fader_->IsEnd())
		{
			DoChangeScene(waitSceneId_);
			fader_->SetFade(Fader::STATE::FADE_IN);
		}
		break;
	}
}