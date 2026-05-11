#include <cmath>
#include <DxLib.h>
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Object/Grid.h"
#include "TitleScene.h"

TitleScene::TitleScene(void) : SceneBase()
{
	grid_ = nullptr;
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{


	// グリッド初期化
	grid_ = new Grid();
	grid_->Init();
}

void TitleScene::Update(void)
{
	// グリッド更新
	grid_->Update();

	// InputManager を使って、スペースキーが「押された瞬間」だけ判定する
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
	{
		// シーン遷移を実行
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	}
}

void TitleScene::Draw(void)
{
	// グリッド描画
	grid_->Draw();
}

void TitleScene::Release(void)
{
	// グリッド解放
	grid_->Release();
	delete grid_;
}
