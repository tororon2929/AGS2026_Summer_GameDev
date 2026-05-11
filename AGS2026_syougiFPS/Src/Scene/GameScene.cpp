#include "GameScene.h"
#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Object/Grid.h"
#include "../Common/Camera.h"
#include "../Object/PlayBpard.h"

GameScene::GameScene(void) : SceneBase(), grid_(nullptr), playBoard_(nullptr) {}

// 【重要】デストラクタの中身（これがないとLNK2019が出ます）
GameScene::~GameScene(void) {}

void GameScene::Init(void) {
    grid_ = new Grid();
    grid_->Init();

    playBoard_ = new PlayBpard();
    if (playBoard_) {
        playBoard_->Initialize();
    }
}

void GameScene::Update(void) {
    if (grid_) grid_->Update();
    Camera* camera = SceneManager::GetInstance().GetCamera();
    if (camera) camera->Update();
}

void GameScene::Draw(void) {
    Camera* camera = SceneManager::GetInstance().GetCamera();
    if (!camera) return;

    camera->SetBeforeDraw();

    if (grid_) grid_->Draw();

    // 盤面の描画
    if (playBoard_) {
        playBoard_->Draw();
    }

    camera->DrawDebug();
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
}