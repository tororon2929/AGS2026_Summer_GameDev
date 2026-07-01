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

	// ロゴの初期値（Drawで使用されている固定値を代入）
	logoX_ = 785;
	logoY_ = 225;
	logoScale_ = 0.5;

	boardModelHandle_ = -1;
	boardPos_ = VGet(53.0f, -1.0f, 15.0f); // 将棋盤が画面中央に見えるよう初期位置を少し下げています
	boardRotY_ = 0.0f;
	boardRotPitch_ = -0.58f;               // 将棋盤のX軸回転デバッグ用
	boardRotYaw_ = 0.64f;                 // 将棋盤のY軸回転デバッグ用
	boardRotSpeed_ = 0.01f;

	// --- カメラの初期設定（本番想定の固定位置） ---
	cameraRadius_ = 250.0f;
	cameraPitch_ = 0.84f;      // 上下30度
	cameraYaw_ = 0.58f;                  // 正面から
	prevMouseX_ = 0;
	prevMouseY_ = 0;

	mState = State::Title;
	mSelectLevelIdx = 0;

}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
	auto& titleRes = ResourceManager::GetInstance().Load(ResourceManager::SRC::Title);
	titleGraphHandle_ = titleRes.handleId_;

	boardModelHandle_ = ResourceManager::GetInstance().LoadModelDuplicate(ResourceManager::SRC::PlayBpard);

	// マウスカーソルを表示する
	SetMouseDispFlag(TRUE);

	SoundManager::GetInstance().Init();
	SoundManager::GetInstance().PlayBGM(SoundManager::BGM::Title, true);
}

void TitleScene::Update(void)
{
	// コントローラーの入力状態を取得
	int padInput = GetJoypadInputState(DX_INPUT_PAD1);

	//// 💡 Aボタン(PAD_INPUT_1) または Enterキーが押されたらゲームシーンへ
	//if ((padInput & PAD_INPUT_1) || CheckHitKey(KEY_INPUT_SPACE))
	//{
	//	SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	//}

	// --- 以下、既存の背景の将棋盤回転処理など ---
	boardRotY_ += boardRotSpeed_;
	if (boardRotY_ > DX_PI_F * 2) {
		boardRotY_ -= DX_PI_F * 2;
	}
	//else
	//{
	//	// 左クリックドラッグで将棋盤の角度をデバッグ微調整
	//	boardRotYaw_ -= deltaX * 0.005f;
	//	boardRotPitch_ += deltaY * 0.005f;
	//}

	//// --- デバッグ用カメラマウス操作（右クリックドラッグ） ---
	//if (mouseInput & MOUSE_INPUT_RIGHT)
	//{
	//	cameraYaw_ -= deltaX * 0.005f;   // 左右回転
	//	cameraPitch_ += deltaY * 0.005f;   // 上下回転

	//	// カメラ反転ガード
	//	if (cameraPitch_ > (DX_PI_F / 2.0f) - 0.05f)  cameraPitch_ = (DX_PI_F / 2.0f) - 0.05f;
	//	if (cameraPitch_ < -(DX_PI_F / 2.0f) + 0.05f) cameraPitch_ = -(DX_PI_F / 2.0f) + 0.05f;
	//}

	//// マウス位置の保存
	//prevMouseX_ = mouseX;
	//prevMouseY_ = mouseY;

	//// マウスホイールまたは [PageUp]/[PageDown] でカメラの距離を調整（ズーム）
	//int wheel = GetMouseWheelRotVol();
	//if (wheel > 0 || CheckHitKey(KEY_INPUT_PGUP)) { cameraRadius_ -= 2.0f; }
	//if (wheel < 0 || CheckHitKey(KEY_INPUT_PGDN)) { cameraRadius_ += 2.0f; }
	//if (cameraRadius_ < 5.0f) cameraRadius_ = 5.0f;

	//// --- 将棋盤の移動操作 ---
	//if (CheckHitKey(KEY_INPUT_LEFT)) { boardPos_.x -= 0.2f; }
	//if (CheckHitKey(KEY_INPUT_RIGHT)) { boardPos_.x += 0.2f; }
	//if (CheckHitKey(KEY_INPUT_UP)) { boardPos_.z += 0.2f; }
	//if (CheckHitKey(KEY_INPUT_DOWN)) { boardPos_.z -= 0.2f; }
	//if (CheckHitKey(KEY_INPUT_Q)) { boardPos_.y += 0.2f; }
	//if (CheckHitKey(KEY_INPUT_E)) { boardPos_.y -= 0.2f; }


	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_B))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::FPS_BATTLE);
	}

	// ========================================================
	// ★ 連続入力を絶対に阻止するキー判定（static変数を分離）
	// ========================================================
	static bool isWKeyOld = false;
	static bool isSKeyOld = false;
	static bool isSpaceKeyOld = false;

	bool isWKeyNow = (CheckHitKey(KEY_INPUT_W) == 1);
	bool isSKeyNow = (CheckHitKey(KEY_INPUT_S) == 1);
	bool isSpaceKeyNow = (CheckHitKey(KEY_INPUT_SPACE) == 1);

	// 押した瞬間だけのトリガー判定
	bool isWKeyTrg = (isWKeyNow && !isWKeyOld);
	bool isSKeyTrg = (isSKeyNow && !isSKeyOld);
	bool isSpaceKeyTrg = (isSpaceKeyNow && !isSpaceKeyOld);

	// 次のフレームのために保存
	isWKeyOld = isWKeyNow;
	isSKeyOld = isSKeyNow;
	isSpaceKeyOld = isSpaceKeyNow;

	// ========================================================
	// ★重要: switch-case、または互いに干渉しない if-else に修正
	// ========================================================
	if (mState == State::Title)
	{
		// タイトル画面でスペースが押されたら難易度選択へ
		if (isSpaceKeyTrg)
		{
			mState = State::SelectLevel;
			SoundManager::GetInstance().PlaySE(SoundManager::SE::Select);
		}
	}
	else if (mState == State::SelectLevel) // ★『else if』にすることで、上の処理で状態が変わってもこのフレーム内では絶対に実行されなくなります
	{
		// Wキーで上
		if (isWKeyTrg)
		{
			if (mSelectLevelIdx > 0) mSelectLevelIdx--;
			SoundManager::GetInstance().PlaySE(SoundManager::SE::Select);
		}
		// Sキーで下
		if (isSKeyTrg)
		{
			if (mSelectLevelIdx < 2) mSelectLevelIdx++;
			SoundManager::GetInstance().PlaySE(SoundManager::SE::Select);
		}

		// 難易度選択画面でスペースが押されたらゲーム開始
		if (isSpaceKeyTrg)
		{
			SceneManager::GetInstance().SetCpuLevel(mSelectLevelIdx);
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
		}
	}
	
}

void TitleScene::Draw(void)
{
	// --- 球面座標からカメラの3D位置を計算 ---
	float cx = cameraRadius_ * cosf(cameraPitch_) * sinf(cameraYaw_);
	float cy = cameraRadius_ * sinf(cameraPitch_);
	float cz = cameraRadius_ * cosf(cameraPitch_) * cosf(cameraYaw_);

	// カメラの注視点と位置（カメラ自体は固定、デバッグ時のみcx, cy, czが変化）
	VECTOR targetPos = VGet(0.0f, 0.0f, 0.0f);
	VECTOR cameraPos = VGet(cx, cy, cz);

	// カメラ設定を適用
	SetCameraPositionAndTargetAndUpVec(cameraPos, targetPos, VGet(0.0f, 1.0f, 0.0f));

	// --- 将棋盤(3Dモデル)の描画 ---
	if (boardModelHandle_ != -1)
	{
		// 自動回転(boardRotY_) + デバッグ回転(Pitch, Yaw)を合成
		Quaternion qAuto = Quaternion::Euler(0.0f, (double)boardRotY_, 0.0f);
		Quaternion qDebug = Quaternion::Euler((double)boardRotPitch_, (double)boardRotYaw_, 0.0f);
		Quaternion qTotal = qDebug.Mult(qAuto); // 回転の掛け合わせ

		MATRIX matRot = qTotal.ToMatrix();
		MATRIX matTrans = MGetTranslate(boardPos_);
		MATRIX matWorld = MMult(matRot, matTrans);

		MV1SetMatrix(boardModelHandle_, matWorld);
		MV1DrawModel(boardModelHandle_);
	}

	// タイトルロゴの描画
	if (titleGraphHandle_ != -1)
	{
		DrawRotaGraph(logoX_, logoY_, logoScale_, 0.0, titleGraphHandle_, TRUE);
	}
	// ========================================================
	// ★追加: 画面状態（State）に応じたテキストの描画
	// ========================================================
	unsigned int white = GetColor(255, 255, 255);
	unsigned int yellow = GetColor(255, 255, 0);

	if (mState == State::Title)
	{
		// 最初は元の文字をそのまま点滅なしで表示
		DrawFormatString(830, 650, white, "PRESS SPACE KEY TO START");
	}
	else if (mState == State::SelectLevel)
	{
		// 難易度選択のUIテキスト（相方のPCの解像度に合わせて座標を微調整してください）
		DrawFormatString(860, 500, white, "SELECT CPU LEVEL");

		// 現在カーソルが合っている難易度だけ黄色(yellow)にする
		unsigned int easyColor = (mSelectLevelIdx == 0) ? yellow : white;
		unsigned int normalColor = (mSelectLevelIdx == 1) ? yellow : white;
		unsigned int hardColor = (mSelectLevelIdx == 2) ? yellow : white;

		DrawFormatString(890, 580, easyColor, "%s EASY", (mSelectLevelIdx == 0) ? "-> " : "   ");
		DrawFormatString(890, 630, normalColor, "%s NORMAL", (mSelectLevelIdx == 1) ? "-> " : "   ");
		DrawFormatString(890, 680, hardColor, "%s HARD", (mSelectLevelIdx == 2) ? "-> " : "   ");

		DrawFormatString(810, 780, white, "[W/S]: Select    [SPACE]: Confirm");
	}
	//// 全デバッグ情報の表示
	//unsigned int white = GetColor(255, 255, 255);
	//unsigned int yellow = GetColor(255, 255, 0);
	//unsigned int green = GetColor(0, 255, 128);

	//DrawFormatString(20, 20, green, "[Board Rot] Pitch: %.2f, Yaw: %.2f", boardRotPitch_, boardRotYaw_);
	//DrawFormatString(20, 40, green, "[Board Pos] X: %.1f, Y: %.1f, Z: %.1f", boardPos_.x, boardPos_.y, boardPos_.z);
	//DrawFormatString(20, 60, green, "[Camera] Dist: %.1f, Pitch: %.2f, Yaw: %.2f", cameraRadius_, cameraPitch_, cameraYaw_);

	//DrawFormatString(20, 90, yellow, "Board Move   : [Arrow Keys] X/Z, [Q]/[E] Y");
	//DrawFormatString(20, 110, yellow, "Board Rotate : [Left Click + Drag] (Overrides auto-rotation)");
	//DrawFormatString(20, 130, yellow, "Camera Debug : [Right Click + Drag] to Rotate / [Wheel] to Zoom");
	//DrawFormatString(20, 160, white, "Press [Space] to GameScene");
}

void TitleScene::Release(void)
{
	SoundManager::GetInstance().Release();
}