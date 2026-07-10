#include "ResultScene.h"
#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include"../Manager/InputManager.h"

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
    int padInput = GetJoypadInputState(DX_INPUT_PAD1);

    // 💡 Aボタン(PAD_INPUT_1) または Enterキーでタイトルへ戻る
    if ((padInput & PAD_INPUT_1) || CheckHitKey(KEY_INPUT_SPACE))
    {
        SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
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