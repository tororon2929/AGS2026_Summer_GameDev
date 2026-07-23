#include <cmath>
#include <DxLib.h>
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Common/Quaternion.h"
#include "TitleScene.h"
#include "../Manager/SoundManager.h"

TitleScene::TitleScene(void) : SceneBase()
{
	titleGraphHandle_ = -1;

	logoX_ = 785;
	logoY_ = 225;
	logoScale_ = 0.5;

	boardModelHandle_ = -1;
	boardPos_ = VGet(53.0f, -1.0f, 15.0f);
	boardRotY_ = 0.0f;
	boardRotPitch_ = -0.58f;
	boardRotYaw_ = 0.64f;
	boardRotSpeed_ = 0.01f;

	cameraRadius_ = 250.0f;
	cameraPitch_ = 0.84f;
	cameraYaw_ = 0.58f;
	prevMouseX_ = 0;
	prevMouseY_ = 0;

	mState = State::Title;
	mSelectLevelIdx = 0;

	// ========================================================
	// ★各UI画像の初期配置パラメータ（ここを画面見ながら調整！）
	// ========================================================
	uiSelect_ = { 1200.0f, 450.0f, 0.4f }; // 「難易度」
	uiEasy_ = { 1200.0f, 520.0f, 0.4f }; // 「簡単」
	uiNormal_ = { 1200.0f, 620.0f, 0.4f }; // 「普通」
	uiHard_ = { 1200.0f, 720.0f, 0.4f }; // 「難しい」
	uiCursor_ = { 1025.0f, 550.0f, 0.2f }; // 「矢印」
	uiControl_ = { 1215.0f, 795.0f, 0.2f }; // 「操作/決定説明」
	uiDecision_ = { 830.0f, 450.0f, 0.5f}; // 「決定」

	debugSelectTarget_ = 0;
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
	auto& titleRes = ResourceManager::GetInstance().Load(ResourceManager::SRC::Title);
	titleGraphHandle_ = titleRes.handleId_;

	boardModelHandle_ = ResourceManager::GetInstance().LoadModelDuplicate(ResourceManager::SRC::PlayBpard);

	SetMouseDispFlag(TRUE);

	SoundManager::GetInstance().Init();
	SoundManager::GetInstance().PlayBGM(SoundManager::BGM::Title, true);
}

void TitleScene::Update(void)
{
	int padInput = GetJoypadInputState(DX_INPUT_PAD1);

	boardRotY_ += boardRotSpeed_;
	if (boardRotY_ > DX_PI_F * 2) {
		boardRotY_ -= DX_PI_F * 2;
	}

	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_B))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::FPS_BATTLE);
	}

	// ========================================================
	// ★追加: リアルタイム調整用キー入力処理
	// ========================================================
	static bool isTabOld = false;
	bool isTabNow = (CheckHitKey(KEY_INPUT_TAB) == 1);
	if (isTabNow && !isTabOld)
	{
		// TABキーで調整ターゲットを切り替え (0:Select, 1:Easy, 2:Normal, 3:Hard, 4:Cursor, 5:Control)
		debugSelectTarget_ = (debugSelectTarget_ + 1) % 6;
	}
	isTabOld = isTabNow;

	// 調整対象のポインタ取得
	UITransform* targetUI = nullptr;
	switch (debugSelectTarget_) {
	case 0: targetUI = &uiSelect_; break;
	case 1: targetUI = &uiEasy_; break;
	case 2: targetUI = &uiNormal_; break;
	case 3: targetUI = &uiHard_; break;
	case 4: targetUI = &uiCursor_; break;
	case 5: targetUI = &uiControl_; break;
	}

	if (targetUI)
	{
		float speed = CheckHitKey(KEY_INPUT_LSHIFT) ? 5.0f : 1.0f;
		float scaleSpeed = CheckHitKey(KEY_INPUT_LSHIFT) ? 0.05f : 0.01f;

		// 矢印キーで位置移動
		if (CheckHitKey(KEY_INPUT_LEFT))  targetUI->x -= speed;
		if (CheckHitKey(KEY_INPUT_RIGHT)) targetUI->x += speed;
		if (CheckHitKey(KEY_INPUT_UP))    targetUI->y -= speed;
		if (CheckHitKey(KEY_INPUT_DOWN))  targetUI->y += speed;

		// Q / E または PageUp / PageDown で拡大縮小
		if (CheckHitKey(KEY_INPUT_Q) || CheckHitKey(KEY_INPUT_PGUP)) targetUI->scale += scaleSpeed;
		if (CheckHitKey(KEY_INPUT_E) || CheckHitKey(KEY_INPUT_PGDN)) targetUI->scale -= scaleSpeed;
		if (targetUI->scale < 0.05f) targetUI->scale = 0.05f;
	}


	// ========================================================
	// 画面進行ロジック
	// ========================================================
	if (mState == State::Title)
	{
		if (CheckHitKey(KEY_INPUT_SPACE) == 1 || (padInput & PAD_INPUT_A) != 0)
		{
			mState = State::SelectLevel;
			mSelectLevelIdx = 1;
			WaitTimer(200);
		}
	}
	else if (mState == State::SelectLevel)
	{
		// 難易度移動
		if (CheckHitKey(KEY_INPUT_W) == 1 || (padInput & PAD_INPUT_UP) != 0)
		{
			mSelectLevelIdx = (mSelectLevelIdx - 1 + 3) % 3;
			WaitTimer(150);
		}

		if (CheckHitKey(KEY_INPUT_S) == 1 || (padInput & PAD_INPUT_DOWN) != 0)
		{
			mSelectLevelIdx = (mSelectLevelIdx + 1) % 3;
			WaitTimer(150);
		}

		// 決定
		if (CheckHitKey(KEY_INPUT_SPACE) == 1 || (padInput & PAD_INPUT_A) != 0)
		{
			SceneManager::GetInstance().SetCpuLevel(mSelectLevelIdx);
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
			WaitTimer(200);
		}
	}
}

void TitleScene::Draw(void)
{
	// 3Dカメラ・将棋盤描画
	float cx = cameraRadius_ * cosf(cameraPitch_) * sinf(cameraYaw_);
	float cy = cameraRadius_ * sinf(cameraPitch_);
	float cz = cameraRadius_ * cosf(cameraPitch_) * cosf(cameraYaw_);

	VECTOR targetPos = VGet(0.0f, 0.0f, 0.0f);
	VECTOR cameraPos = VGet(cx, cy, cz);
	SetCameraPositionAndTargetAndUpVec(cameraPos, targetPos, VGet(0.0f, 1.0f, 0.0f));

	if (boardModelHandle_ != -1)
	{
		Quaternion qAuto = Quaternion::Euler(0.0f, (double)boardRotY_, 0.0f);
		Quaternion qDebug = Quaternion::Euler((double)boardRotPitch_, (double)boardRotYaw_, 0.0f);
		Quaternion qTotal = qDebug.Mult(qAuto);

		MATRIX matRot = qTotal.ToMatrix();
		MATRIX matTrans = MGetTranslate(boardPos_);
		MATRIX matWorld = MMult(matRot, matTrans);

		MV1SetMatrix(boardModelHandle_, matWorld);
		MV1DrawModel(boardModelHandle_);
	}

	// タイトルロゴ
	if (titleGraphHandle_ != -1)
	{
		DrawRotaGraph(logoX_, logoY_, logoScale_, 0.0, titleGraphHandle_, TRUE);
	}

	// ========================================================
	// 各種リソース画像の読み込み
	// ========================================================
	auto& rm = ResourceManager::GetInstance();
	int hSelect = rm.Load(ResourceManager::SRC::Select).handleId_;
	int hEasy = rm.Load(ResourceManager::SRC::Easy).handleId_;
	int hNormal = rm.Load(ResourceManager::SRC::Normal).handleId_;
	int hHard = rm.Load(ResourceManager::SRC::Head).handleId_; // 難しい(Head)
	int hCursor = rm.Load(ResourceManager::SRC::Cursor).handleId_;
	int hControl = rm.Load(ResourceManager::SRC::Control).handleId_; 
	int hDecision = rm.Load(ResourceManager::SRC::Decision).handleId_;

	if (mState == State::Title)
	{
		DrawRotaGraph((int)uiDecision_.x, (int)uiDecision_.y, uiDecision_.scale, 0.0, hDecision, TRUE);
	}
	else if (mState == State::SelectLevel)
	{
		// 1. 「難易度」見出し画像
		if (hSelect != -1) DrawRotaGraph((int)uiSelect_.x, (int)uiSelect_.y, uiSelect_.scale, 0.0, hSelect, TRUE);

		// 2. 「簡単」「普通」「難しい」画像（選択中のものは少し拡大するエフェクト付き）
		float easyScale = uiEasy_.scale * ((mSelectLevelIdx == 0) ? 1.15f : 1.0f);
		float normalScale = uiNormal_.scale * ((mSelectLevelIdx == 1) ? 1.15f : 1.0f);
		float hardScale = uiHard_.scale * ((mSelectLevelIdx == 2) ? 1.15f : 1.0f);

		if (hEasy != -1)   DrawRotaGraph((int)uiEasy_.x, (int)uiEasy_.y, easyScale, 0.0, hEasy, TRUE);
		if (hNormal != -1) DrawRotaGraph((int)uiNormal_.x, (int)uiNormal_.y, normalScale, 0.0, hNormal, TRUE);
		if (hHard != -1)   DrawRotaGraph((int)uiHard_.x, (int)uiHard_.y, hardScale, 0.0, hHard, TRUE);

		// 3. カーソル（矢印）画像（選択インデックスに合わせてY位置を自動追従調整）
		float targetY = uiEasy_.y;
		if (mSelectLevelIdx == 1) targetY = uiNormal_.y;
		if (mSelectLevelIdx == 2) targetY = uiHard_.y;

		if (hCursor != -1) DrawRotaGraph((int)uiCursor_.x, (int)targetY, uiCursor_.scale, 0.0, hCursor, TRUE);

		// 4. 「操作/決定」画像
		if (hControl != -1) DrawRotaGraph((int)uiControl_.x, (int)uiControl_.y, uiControl_.scale, 0.0, hControl, TRUE);
	}

	// ========================================================
	// ★追加: 画面左上にリアルタイム座標デバッグGUIを表示
	// ========================================================
	/*const char* targetNames[] = { "Select(難易度)", "Easy(簡単)", "Normal(普通)", "Hard(難しい)", "Cursor(矢印)", "Control(操作説明)" };
	UITransform* currentUI = nullptr;
	switch (debugSelectTarget_) {
	case 0: currentUI = &uiSelect_; break;
	case 1: currentUI = &uiEasy_; break;
	case 2: currentUI = &uiNormal_; break;
	case 3: currentUI = &uiHard_; break;
	case 4: currentUI = &uiCursor_; break;
	case 5: currentUI = &uiControl_; break;
	}

	unsigned int green = GetColor(0, 255, 128);
	unsigned int yellow = GetColor(255, 255, 0);

	DrawFormatString(20, 20, green, "=== UI POSITION EDITOR ===");
	DrawFormatString(20, 40, green, "[TAB] Switch Target | [Arrows] Move | [Q/E] Scale");
	DrawFormatString(20, 65, yellow, "TARGET : %s", targetNames[debugSelectTarget_]);
	if (currentUI) {
		DrawFormatString(20, 85, yellow, "X: %.1f | Y: %.1f | Scale: %.2f", currentUI->x, currentUI->y, currentUI->scale);
	}*/
}

void TitleScene::Release(void)
{
	SoundManager::GetInstance().Release();
}