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

void FPSBattleScene::AddBullet(VECTOR pos, VECTOR dir)
{
    bullets_.push_back(new Bullet(pos, dir));
}

void FPSBattleScene::Update()
{

	// カメラの更新
    if (camera_ != nullptr)
    {
        camera_->Update();
    }

	// エネミーの更新
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
        if (player_ != nullptr && camera_ != nullptr)
        {
            //弾のスタート位置をカメラ位置にする
            VECTOR start = camera_->GetPos();

            //カメラ角度から向いてる方向を取得する
            VECTOR angles = camera_->GetAngles();
            
            lookDir.x = cosf(angles.x) * sinf(angles.y);
            lookDir.y = -sinf(angles.x);
            lookDir.z = cosf(angles.x) * cosf(angles.y);

            start = VAdd(start, VScale(lookDir, 10.0f));

            bullets_.push_back(new Bullet(start, lookDir));
        }
    }

    //弾の更新処理
    for (auto it = bullets_.begin(); it != bullets_.end();)
    {
        (*it)->Update();

        bool isHit = false;
        if (enemy_ != nullptr)
        {
            //弾と敵の距離の計算
            float dist = VSize(VSub((*it)->GetPos(), enemy_->GetPos()));

            //ヒット判定
            if (dist < 7.0f)
            {
                isHit = true;
            }
        }

        if (isHit)
        {
            hitCount++;

            delete* it;
            it = bullets_.erase(it);
        }
        else if ((*it)->IsDead())
        {
            delete* it;
            it = bullets_.erase(it);
        }
        else {
            ++it;
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

    //弾の描画
    for (auto b : bullets_) {
        b->Draw();
    }

    DrawFormatString(0, 0, GetColor(255, 255, 255), "Bullet Count: %d", bullets_.size());

    DrawFormatString(0, 50, GetColor(0, 255, 0), "Hit Count: %d", hitCount);
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


