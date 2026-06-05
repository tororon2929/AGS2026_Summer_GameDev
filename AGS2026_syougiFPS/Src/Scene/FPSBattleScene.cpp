#include "FPSBattleScene.h"
#include <DxLib.h>
#include "../Manager/SceneManager.h"
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
        enemy_ = new Enemy();
		enemy_->Init();

        player_ = new Player();
        player_->Init();
}

void FPSBattleScene::Update()
{
    if(enemy_!=nullptr)
    {
        enemy_->Update();
	}

    if(player_!=nullptr)
    {
        player_->Update();
	}

    // ‰¼FEnter‚Å«Šû‚Ö–ß‚é

    if (CheckHitKey(KEY_INPUT_RETURN))
    {
        SceneManager::GetInstance().ChangeScene(
            SceneManager::SCENE_ID::GAME
        );
    }

	
}

void FPSBattleScene::Draw()
{
    // •`‰æˆ—
    if (enemy_ != nullptr)
    {
        enemy_->Draw();
    }

    DrawFormatString(
        700,
        400,
        GetColor(255, 255, 255),
        "FPS BATTLE"
    );

    DrawFormatString(
        600,
        500,
        GetColor(255, 255, 0),
        "PRESS ENTER TO RETURN"
    );
}

void FPSBattleScene::Release()
{
    if (enemy_ != nullptr)
    {
        delete enemy_;
        enemy_ = nullptr;
    }

    if(player_ != nullptr)
    {
        delete player_;
        player_ = nullptr;
	}
}