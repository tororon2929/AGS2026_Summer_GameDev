#include "GameScene.h"
#include <cmath>
#include <DxLib.h>
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Object/Grid.h"


GameScene::GameScene(void) : SceneBase()
{
	grid_ = nullptr;
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{

	// グリッド初期化
	grid_ = new Grid();
	grid_->Init();
}

void GameScene::Update(void)
{
	// グリッド更新
	grid_->Update();
}

void GameScene::Draw(void)
{
	// グリッド描画
	grid_->Draw();
}

void GameScene::Release(void)
{
	// グリッド解放
	grid_->Release();
	delete grid_;
}
