#include "FPSBattleScene.h"
#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Common/Camera.h"
#include "../Object/Stage.h"
#include "../Object/Enemy.h"
#include "../Object/Player.h"


FPSBattleScene::FPSBattleScene()
{
}

FPSBattleScene::~FPSBattleScene()
{
}

void FPSBattleScene::Init()
{
	// カメラの初期化
    camera_ = new Camera();
	camera_->Init();

	//カメラを強制的にFPSモードに切り替え
	camera_->ChangeMode(CameraMode::FPS);

	// ステージの初期化
    stage_ = new Stage();
    stage_->Init();

	// 敵の初期化
    enemy_ = new Enemy();
    enemy_->Init();

	// プレイヤーの初期化
    player_ = new Player();
    player_->Init();
}

void FPSBattleScene::Update()
{

	// カメラの更新
    if (camera_ != nullptr)
    {
        camera_->Update();
    }

	// ステージの更新
    if(enemy_!=nullptr)
    {
        enemy_->Update();
	}

	// プレイヤーの更新
    if(player_!=nullptr)
    {
        player_->Update(camera_);
	}

    if (GetMouseInput() & MOUSE_INPUT_LEFT)
    {
        if (player_!= nullptr && enemy_ != nullptr)
        {
            
        }
    }

    // 仮：Enterで将棋へ戻る

    if (CheckHitKey(KEY_INPUT_RETURN))
    {
        SceneManager::GetInstance().ChangeScene(
            SceneManager::SCENE_ID::GAME
        );
    }

	
}

void FPSBattleScene::Draw()
{
	// カメラの描画前処理
    if(camera_!= nullptr)
    {
        camera_->SetBeforeDraw();
	}

	// ステージのの描画
    if(stage_ != nullptr)
    {
        stage_->Draw();
	}

	// 敵の描画
    if (enemy_ != nullptr)
    {
        enemy_->Draw();
    }

	// プレイヤーの描画
    if (player_ != nullptr)
    {
        player_->Draw();
    }

    //DrawFormatString(
    //    700,
    //    400,
    //    GetColor(255, 255, 255),
    //    "FPS BATTLE"
    //);

    //DrawFormatString(
    //    600,
    //    500,
    //    GetColor(255, 255, 0),
    //    "PRESS ENTER TO RETURN"
    //);
}

void FPSBattleScene::Release()
{
	// カメラの解放
    if (stage_ != nullptr)
    {
        stage_->Release();
        delete stage_;
        stage_ = nullptr;
    }

	// 敵の解放
    if (enemy_ != nullptr)
    {
        delete enemy_;
        enemy_ = nullptr;
    }

	// プレイヤーの解放
    if(player_ != nullptr)
    {
        delete player_;
        player_ = nullptr;
	}

	// カメラの解放
    if (camera_ != nullptr) {
		camera_->Release();
		delete camera_;
		camera_ = nullptr;
    }

}