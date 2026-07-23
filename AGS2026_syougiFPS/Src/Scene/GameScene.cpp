#include "GameScene.h"
#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Object/Grid.h"
#include "../Common/Camera.h"
#include "../Object/PlayBpard.h"
#include "../Manager/LightManager.h" 
#include "../Object/Ou.h"
#include "../Manager/SoundManager.h"
GameScene::GameScene(void) : SceneBase(), grid_(nullptr), playBoard_(nullptr), /*ou_(nullptr),*/ lightManager_(nullptr) {}

GameScene::~GameScene(void) {}

void GameScene::Init(void) {
    grid_ = new Grid();
    grid_->Init();

    playBoard_ = new PlayBpard();
    if (playBoard_) {
        playBoard_->Initialize();
    }

    // エラー解消：Ouのコンストラクタに合わせて引数 (x, y, isPlayer) を渡す
  /*  ou_ = new Ou(4, 0, true);*/

    lightManager_ = new LightManager();
    SoundManager::GetInstance().Init();
    SoundManager::GetInstance().PlayBGM(SoundManager::BGM::Game, true);

    PlayTime++;
    if (PlayTime>=60)
    {
        SoundManager::GetInstance().PlayBGM(SoundManager::BGM::sisi, true);
        PlayTime = 0;
    }
   }
   

void GameScene::Update(void) {
    if (grid_) grid_->Update();

    // 王の更新処理（必要であれば）
    // if (ou_) ou_->Update(); 

    if (playBoard_)
    {
        playBoard_->Update();
    }
    Camera* camera = SceneManager::GetInstance().GetCamera();
    if (camera) camera->Update();
}

void GameScene::Draw(void)
{
    Camera* camera = SceneManager::GetInstance().GetCamera();
    if (!camera) return;

    camera->SetBeforeDraw();

   
    if (lightManager_) {
        lightManager_->applyLighting();
    }

   /* if (grid_) grid_->Draw();*/

    if (playBoard_) {
        playBoard_->Draw();
    }

    camera->DrawDebug();

    // ======================================================
    // 3D描画終了
    // ======================================================

    SetDrawScreen(DX_SCREEN_BACK);

    // Zバッファ無効
    SetUseZBuffer3D(FALSE);

    // ======================================================
    // 2Dデバッグ表示
    // ======================================================

    /*DrawFormatString(
        1400,
        20,
        GetColor(255, 0, 0),
        "DEBUG DRAW OK"
    );*/

    // ======================================================
    // 黒マスク
    // ======================================================

   /*int sw = 1920;
    int sh = 1080;

    DrawBox(0, 0, 360, sh, GetColor(0, 0, 0), TRUE);

    DrawBox(sw - 760, 0, sw, sh, GetColor(0, 0, 0), TRUE);

    camera->DrawDebug();*/
}

void GameScene::Release(void) {
    if (grid_) {
        grid_->Release();
        delete grid_;
        grid_ = nullptr;
    }
    if (playBoard_) {
        delete playBoard_;
        playBoard_ = nullptr;
    }
    /*if (ou_) {
        delete ou_;
        ou_ = nullptr;
    }*/
    if (lightManager_) {
        delete lightManager_;
        lightManager_ = nullptr;
    }
    SoundManager::GetInstance().Release();

}