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

SceneManager* SceneManager::instance_ = nullptr;

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

	// ★ 変数の初期化
	isPaused_ = false;
	isEscapeKeyOld_ = false;
	pauseSelectIdx_ = 0;
	// フェード機能の初期化
	fader_ = new Fader();
	fader_->Init();

	// カメラ
	camera_ = new Camera();
	camera_->Init();

	//scene_ = new TitleScene();
	//scene_->Init();


	/*miniCamera_ = new MiniCamera(camera_);
	miniCamera_->Init();*/

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

	// 背景色設定
	SetBackgroundColor(
		BACKGROUND_COLOR_R, 
		BACKGROUND_COLOR_G, 
		BACKGROUND_COLOR_B);

	// Zバッファを有効にする
	SetUseZBuffer3D(true);

	// Zバッファへの書き込みを有効にする
	SetWriteZBuffer3D(true);

	// バックカリングを有効にする
	SetUseBackCulling(true);

	// ライトの設定
	SetUseLighting(true);

	// 正面から斜め下に向かったライト
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

	// ----------------------------------------------------
	// ★ ESCキーによるポーズ・終了確認の切り替え
	// ----------------------------------------------------
	bool isEscapeKeyNow = (CheckHitKey(KEY_INPUT_ESCAPE) == 1);
	if (isEscapeKeyNow && !isEscapeKeyOld_)
	{
		// タイトルシーンにいる場合
		if (sceneId_ == SCENE_ID::TITLE)
		{
			isPaused_ = !isPaused_; // 終了確認状態のON/OFF
			pauseSelectIdx_ = 1;    // タイトルでのESCは「ゲーム終了」に初期カーソルを合わせる
		}
		// それ以外のシーン（GAMEなど）にいる場合
		else
		{
			isPaused_ = !isPaused_; // ポーズ状態のON/OFF
			pauseSelectIdx_ = 0;    // カーソルを「ゲームに戻る」にリセット

			if (!isPaused_)
			{
				ResetDeltaTime(); // ポーズ解除時の時間補正
			}
		}
	}
	isEscapeKeyOld_ = isEscapeKeyNow;

	// ----------------------------------------------------
	// ★ ポーズ（一時停止）中のメニュー操作処理
	// ----------------------------------------------------
	if (isPaused_)
	{
		// Wキー or 上矢印キーでカーソルを上に
		if (CheckHitKey(KEY_INPUT_W) == 1 || CheckHitKey(KEY_INPUT_UP) == 1)
		{
			// タイトルシーンなら「タイトルに戻る」はないので、ゲームに戻る(0)と終了(2)の間だけ移動
			if (sceneId_ == SCENE_ID::TITLE)
			{
				pauseSelectIdx_ = (pauseSelectIdx_ == 0) ? 2 : 0;
			}
			else
			{
				pauseSelectIdx_ = (pauseSelectIdx_ - 1 + static_cast<int>(PauseMenu::Length)) % static_cast<int>(PauseMenu::Length);
			}
			// 連続入力を防ぐため簡易的なウェイト（本当はInputManager側でトリガー判定するのが理想です）
			WaitTimer(150);
		}
		// Sキー or 下矢印キーでカーソルを下に
		if (CheckHitKey(KEY_INPUT_S) == 1 || CheckHitKey(KEY_INPUT_DOWN) == 1)
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

		// SPACEキー or ENTERキーで決定
		if (CheckHitKey(KEY_INPUT_SPACE) == 1 || CheckHitKey(KEY_INPUT_RETURN) == 1)
		{
			if (pauseSelectIdx_ == 0) // Resume: ゲームに戻る
			{
				isPaused_ = false;
				ResetDeltaTime();
			}
			else if (pauseSelectIdx_ == 1) // GoToTitle: タイトルに戻る
			{
				isPaused_ = false;
				ChangeScene(SCENE_ID::TITLE); // タイトルシーンへ遷移
			}
			else if (pauseSelectIdx_ == 2) // ExitGame: ゲームを終了する
			{
				DxLib_End(); // DXライブラリの終了処理（アプリが閉じます）
				exit(0);
			}
			WaitTimer(150);
		}
		return; // ポーズ中はこれ以降のゲーム進行（Update）を完全にスキップ
	}

	// 通常時の更新処理
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
	
	//miniCamera_->DrawScreen();

	// 描画先グラフィック領域の指定
	// (３Ｄ描画で使用するカメラの設定などがリセットされる)
	SetDrawScreen(DX_SCREEN_BACK);

	// 画面を初期化
	ClearDrawScreen();

	// 各シーンの描画処理
	scene_->Draw();

	//// ミニカメラ
	//miniCamera_->Draw();

	// 暗転・明転
	fader_->Draw();

	// ----------------------------------------------------
	// ★ ポーズメニュー UI の描画
	// ----------------------------------------------------
	if (isPaused_)
	{
		// 画面全体をうっすら暗くするマスク
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
		DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		unsigned int white = GetColor(255, 255, 255);
		unsigned int yellow = GetColor(255, 255, 0);

		// 選択中かどうかに応じて色を変えるラムダ関数
		auto getMenuColor = [&](int idx) { return (pauseSelectIdx_ == idx) ? yellow : white; };
		auto getMenuArrow = [&](int idx) { return (pauseSelectIdx_ == idx) ? "-> " : "   "; };

		// 【パターンA】タイトルシーンでのESC（ゲーム終了確認）
		if (sceneId_ == SCENE_ID::TITLE)
		{
			DrawFormatString(630, 450, white, "ゲームを終了しますか?");

			DrawFormatString(680, 550, getMenuColor(0), "%s いいえ", getMenuArrow(0));
			DrawFormatString(680, 610, getMenuColor(2), "%s はい", getMenuArrow(2));
		}
		// 【パターンB】ゲームシーンなどでのESC（通常のポーズメニュー）
		else
		{
			DrawFormatString(900, 420, white, "ポーズ");

			DrawFormatString(680, 520, getMenuColor(0), "%s 閉じる", getMenuArrow(0));
			DrawFormatString(680, 580, getMenuColor(1), "%s タイトルに戻る", getMenuArrow(1));
			DrawFormatString(680, 640, getMenuColor(2), "%s ゲームを終了する", getMenuArrow(2));
		}

		DrawFormatString(810, 750, white, "[W/S]: 移動    [SPACE]: 決定");
	}

}

void SceneManager::Destroy(void)
{

	// シーンの解放
	scene_->Release();
	delete scene_;

	// フェード機能の解放
	delete fader_;

	camera_->Release();
	delete camera_;

	//miniCamera_->Release();
	//delete miniCamera_;

	// インスタンスのメモリ解放
	delete instance_;

}

void SceneManager::ChangeScene(SCENE_ID nextId)
{

	// フェード処理が終わってからシーンを変える場合もあるため、
	// 遷移先シーンをメンバ変数に保持
	waitSceneId_ = nextId;

	// フェードアウト(暗転)を開始する
	fader_->SetFade(Fader::STATE::FADE_OUT);
	isSceneChanging_ = true;

}

SceneManager::SCENE_ID SceneManager::GetSceneID(void)
{
	return sceneId_;
}

float SceneManager::GetDeltaTime(void) const
{
	//return 1.0f / 60.0f;
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

	// デルタタイム
	deltaTime_ = 1.0f / 60.0f;

	camera_ = nullptr;
	/*miniCamera_ = nullptr;*/

}

void SceneManager::ResetDeltaTime(void)
{
	deltaTime_ = 0.016f;
	preTime_ = std::chrono::system_clock::now();
}

void SceneManager::DoChangeScene(SCENE_ID sceneId)
{

	// シーンを変更する
	sceneId_ = sceneId;
	// ★ 新しいシーンが始まるのでポーズ状態を自動で解除する
	isPaused_ = false;
	// 現在のシーンを解放
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

	// 各シーンの初期化
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
		// 明転中
		if (fader_->IsEnd())
		{
			// 明転が終了したら、フェード処理終了
			fader_->SetFade(Fader::STATE::NONE);
			isSceneChanging_ = false;
		}
		break;
	case Fader::STATE::FADE_OUT:
		// 暗転中
		if (fader_->IsEnd())
		{
			// 完全に暗転してからシーン遷移
			DoChangeScene(waitSceneId_);
			// 暗転から明転へ
			fader_->SetFade(Fader::STATE::FADE_IN);
		}
		break;
	}

}


