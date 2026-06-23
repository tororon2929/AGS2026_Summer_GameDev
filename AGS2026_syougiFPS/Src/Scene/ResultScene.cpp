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
    bool isClear = SceneManager::GetInstance().IsGameClear();

    if (isClear)
    {
        DrawString(100, 100, "GAME CLEAR", GetColor(255, 255, 0));

    }
    else
    {
        DrawString(100, 100, "GAME OVER", GetColor(255, 0, 0));
    }
}

void ResultScene::Release()
{
}