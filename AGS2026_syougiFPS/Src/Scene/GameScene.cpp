#include "GameScene.h"
#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Object/Grid.h"
#include "../Common/Camera.h"

GameScene::GameScene(void) : SceneBase()
{
    grid_ = nullptr;
}

GameScene::~GameScene(void) {}

void GameScene::Init(void)
{
    grid_ = new Grid();
    grid_->Init();
}

void GameScene::Update(void)
{
    grid_->Update();

    Camera* camera = SceneManager::GetInstance().GetCamera();
    if (camera) camera->Update();
}

void GameScene::Draw(void)
{
    Camera* camera = SceneManager::GetInstance().GetCamera();

    // 3D•`‰æ‚Ì‘O‚ÉƒJƒƒ‰‚ðŠmŽÀ‚É”½‰f
    if (camera) camera->SetBeforeDraw();

    // 3D•`‰æ
    grid_->Draw();

    // 2DƒfƒoƒbƒOî•ñ‚ÍƒJƒƒ‰Ý’èŒã‚É•`‰æ
    if (camera) camera->DrawDebug();
}

void GameScene::Release(void)
{
    grid_->Release();
    delete grid_;
    grid_ = nullptr;
}