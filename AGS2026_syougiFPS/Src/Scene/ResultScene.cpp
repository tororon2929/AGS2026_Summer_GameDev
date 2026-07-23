#include "ResultScene.h"
#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/SoundManager.h"
#include "../Manager/ResourceManager.h"
#include "../Application.h"

ResultScene::ResultScene()
{
    WinImage = -1;
    LoseImage = -1;

    // 画面の完全に真ん中の座標を初期値にする
    logoX_ = 940;
    logoY_ = 626;
    logoScale_ = 1.3;
}

ResultScene::~ResultScene()
{
}

void ResultScene::Init()
{
    auto& WinRes = ResourceManager::GetInstance().Load(ResourceManager::SRC::Win);
    WinImage = WinRes.handleId_;

    auto& LoseRes = ResourceManager::GetInstance().Load(ResourceManager::SRC::Lose);
    LoseImage = LoseRes.handleId_;
}

void ResultScene::Update()
{
    /* ----------------------------------------------------
     デバッグ用：位置とサイズ（スケール）の調整操作
     ----------------------------------------------------
     矢印キーで位置移動
    if (CheckHitKey(KEY_INPUT_LEFT))  logoX_ -= 2;
    if (CheckHitKey(KEY_INPUT_RIGHT)) logoX_ += 2;
    if (CheckHitKey(KEY_INPUT_UP))    logoY_ -= 2;
    if (CheckHitKey(KEY_INPUT_DOWN))  logoY_ += 2;

     Z / X キーで拡大・縮小
    if (CheckHitKey(KEY_INPUT_Z)) logoScale_ += 0.01;
    if (CheckHitKey(KEY_INPUT_X)) logoScale_ -= 0.01;

     スケールが小さくなりすぎないようにガード
    if (logoScale_ < 0.05) logoScale_ = 0.05;*/


    // ----------------------------------------------------
    // 通常のシーン遷移操作
    // ----------------------------------------------------
    int padInput = GetJoypadInputState(DX_INPUT_PAD1);

    // Aボタン(PAD_INPUT_1) または スペースキー、Enterキーでタイトルへ戻る
    if ((padInput & PAD_INPUT_1) || CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_RETURN))
    {
        SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
    }
}

void ResultScene::Draw()
{
    bool isClear = SceneManager::GetInstance().IsGameClear();

    if (isClear)
    {
        // 勝ち画像の描画
        if (WinImage != -1)
        {
            DrawRotaGraph(logoX_, logoY_, logoScale_, 0.0, WinImage, FALSE);
        }
        else
        {
            DrawFormatString(100, 100, GetColor(255, 255, 0), "WIN (画像ハンドルが -1 です)");
        }
    }
    else
    {
        // 負け画像の描画
        if (LoseImage != -1)
        {
            DrawRotaGraph(logoX_, logoY_, logoScale_, 0.0, LoseImage, TRUE);
        }
        else
        {
            DrawFormatString(100, 100, GetColor(255, 0, 0), "LOSE (画像ハンドルが -1 です)");
        }
    }

    //// ----------------------------------------------------
    //// デバッグ用情報の描画（画面の左上に現在の設定値を出す）
    //// ----------------------------------------------------
    //int textColor = GetColor(255, 255, 255);
    //DrawString(20, 20, "【DEBUG MODE】", GetColor(255, 0, 0));
    //DrawString(20, 40, "Move : Arrow Keys (上下左右)", textColor);
    //DrawString(20, 60, "Scale: Z key (拡大) / X key (縮小)", textColor);

    //// 現在の数値を表示（この値をあとでコードの初期値にコピペすれば確定できます）
    //DrawFormatString(20, 90, GetColor(0, 255, 255), "Current X    : %d", logoX_);
    //DrawFormatString(20, 110, GetColor(0, 255, 255), "Current Y    : %d", logoY_);
    //DrawFormatString(20, 130, GetColor(0, 255, 255), "Current Scale: %.2f", logoScale_);
}

void ResultScene::Release()
{
    ResourceManager::GetInstance().Release();

    WinImage = -1;
    LoseImage = -1;
}