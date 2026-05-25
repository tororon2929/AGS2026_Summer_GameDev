#include "ResultScene.h"
#include <DxLib.h>
#include "../Manager/SceneManager.h"

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Init()
{
}

void ResultScene::Update()
{
    // Enter‚Åƒ^ƒCƒgƒ‹‚Ö–ß‚é
    if (CheckHitKey(KEY_INPUT_RETURN))
    {
        SceneManager::GetInstance().ChangeScene(
            SceneManager::SCENE_ID::TITLE
        );
    }
}

void ResultScene::Draw()
{
    DrawFormatString(
        700,
        400,
        GetColor(255, 255, 255),
        "GAME END"
    );

    DrawFormatString(
        620,
        500,
        GetColor(255, 255, 0),
        "PRESS ENTER TO TITLE"
    );
}

void ResultScene::Release()
{
}