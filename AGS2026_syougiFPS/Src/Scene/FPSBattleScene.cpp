#include "FPSBattleScene.h"
#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/SoundManager.h"
#include "../Common/Camera.h"
#include "../Object/Stage.h"
#include "../Object/Enemy.h"
#include "../Object/Player.h"
#include"../Application.h"


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

    lightManager_.setBrightness(1.5f);
    lightManager_.setAmbient(0.8f);
    lightManager_.setDirection(0.0f, -1.0f, 1.0f);
    lightManager_.applyLighting();

    crosshairImg_ = LoadGraph("Data/UI/crosshair.png");

    SoundManager::GetInstance().Init();
    SoundManager::GetInstance().PlayBGM(SoundManager::BGM::fps, true);

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
    if(enemy_ != nullptr && player_ != nullptr)
    {
        enemy_->Update(player_->GetPos());
	}

	// プレイヤーの更新
    if(player_!=nullptr)
    {
        player_->Update(camera_);
	}


	//プレイヤーと敵の当たり判定
    if (enemy_ != nullptr && player_ != nullptr)
    {
        SoundManager::GetInstance().PlaySE(SoundManager::SE::Damage);
        if (!player_->IsInvincible())
        {
            float dist = VSize(VSub(enemy_->GetPos(), player_->GetPos()));
            if (dist < enemy_->GetRadius()) 
            {
                player_->Damage(20); // 20ダメージ与えて自動で無敵化
            }
        }
    }

    //弾のタイマーを減らす
    if (shotTimer_ > 0)
    {
        shotTimer_--;
    }
    //射撃処理
    bool isShoot = false;
    if (shotTimer_ <= 0)
    {
        if (GetMouseInput() & MOUSE_INPUT_LEFT) { isShoot = true; }

        if (InputManager::GetInstance().IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::R_TRIGGER)) {
            isShoot = true;
        }
    }

    if (isShoot)
    {
        SoundManager::GetInstance().PlaySE(SoundManager::SE::Attack);
        if (player_ != nullptr && camera_ != nullptr)
        {
			shotTimer_ = SHOT_INTERVAL;

            // (既存の射撃処理をそのまま利用)
            VECTOR start = camera_->GetPos();
            VECTOR angles = camera_->GetAngles();
            
            lookDir.x = cosf(angles.x) * sinf(angles.y);
            lookDir.y = -sinf(angles.x);
            lookDir.z = cosf(angles.x) * cosf(angles.y);

            start = VAdd(start, VScale(lookDir, startpoint));
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
            if (dist < enemy_->GetRadius())
            {
                SoundManager::GetInstance().PlaySE(SoundManager::SE::Damage);
                isHit = true;

                //敵にダメージ
                enemy_->Damage(2);

                hitCount_++;
            }
        }
       
        if (isHit||(*it)->IsDead())
        {
            delete* it;
            it = bullets_.erase(it);
        }
        else {
            ++it;
        }

        
    }

	//ゲームオーバー判定
    if (player_ != nullptr && player_->GetHP() <= 0)
    {
        SceneManager::GetInstance().SetGameClear(false);

        SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::RESULT);
        return;
    }

    //ゲームクリア判定
    if (enemy_ != nullptr && enemy_->IsDead())
    {
        SceneManager::GetInstance().SetGameClear(false);

        SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::RESULT);
        return;
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

    for (int i = 0; i < 40; i++)
    {
        int alpha = 255 - (i * 6);
        if (alpha < 0)alpha = 0;

        SetDrawBlendMode(DX_BLENDMODE_ADD,alpha);
        float currentY = y + (i * 0.15f) + sinf(time + i * 0.1f) * 1.5f;

        DrawLine3D(VGet(-limitx, currentY, -limitz), VGet(limitx, currentY, -limitz), auraColor);
        DrawLine3D(VGet(limitx, currentY, -limitz), VGet(limitx, currentY, limitz), auraColor);
        DrawLine3D(VGet(limitx, currentY, limitz), VGet(-limitx, currentY, limitz), auraColor);
        DrawLine3D(VGet(-limitx, currentY, limitz), VGet(-limitx, currentY, -limitz), auraColor);
    }

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

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

    if (player_ != nullptr)
    {
        int hpX = 50;
        int hpY = Application::SCREEN_SIZE_Y - 100;
        unsigned int color = player_->IsInvincible() ? GetColor(255, 165, 0) : GetColor(0, 255, 0); // 無敵中はオレンジ

        DrawFormatString(hpX, hpY, color, "PLAYER HP: %d / 100 %s",
            player_->GetHP(), player_->IsInvincible() ? "[INVINCIBLE]" : "");
    }

    if (crosshairImg_ != -1)
    {
        DrawRotaGraph(centerX, centerY, 1.0, 0.0, crosshairImg_, TRUE);
    }

    DrawFormatString(0, 0, GetColor(255, 255, 255), "Bullet Count: %d", bullets_.size());
    DrawFormatString(0, 50, GetColor(0, 255, 0), "Hit Count: %d", hitCount_);

    if (enemy_ != nullptr)
    {
        DrawFormatString(0, 75, GetColor(255, 0, 0),"ENEMY HP: %d / 500", enemy_->hp_);
    }


    
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

    if (crosshairImg_ != -1)
    {
        DeleteGraph(crosshairImg_);
        crosshairImg_ = -1;
    }

    SoundManager::GetInstance().Release();

}


