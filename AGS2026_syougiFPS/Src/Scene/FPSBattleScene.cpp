#include "FPSBattleScene.h"
#include <DxLib.h>
#include "../Manager/SceneManager.h"

FPSBattleScene::FPSBattleScene()
{
}

FPSBattleScene::~FPSBattleScene()
{
}

void FPSBattleScene::Init()
{
}

void FPSBattleScene::Update()
{
    // âºÅFEnterÇ≈è´ä˚Ç÷ñﬂÇÈ

    if (CheckHitKey(KEY_INPUT_RETURN))
    {
        SceneManager::GetInstance().ChangeScene(
            SceneManager::SCENE_ID::GAME
        );
    }
}

void FPSBattleScene::Draw()
{
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
}