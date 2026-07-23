#include <DxLib.h>
#include "InputManager.h"

InputManager* InputManager::instance_ = nullptr;

void InputManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new InputManager();
	}
	instance_->Init();
}

InputManager& InputManager::GetInstance(void)
{
	if (instance_ == nullptr)
	{
		InputManager::CreateInstance();
	}
	return *instance_;
}

void InputManager::Init(void)
{


	// ゲームで使用したいキーを、
	// 事前にここで登録しておいてください
	InputManager::GetInstance().Add(KEY_INPUT_SPACE);
	InputManager::GetInstance().Add(KEY_INPUT_N);
	InputManager::GetInstance().Add(KEY_INPUT_Z);
	InputManager::GetInstance().Add(KEY_INPUT_W);
	InputManager::GetInstance().Add(KEY_INPUT_A);
	InputManager::GetInstance().Add(KEY_INPUT_S);
	InputManager::GetInstance().Add(KEY_INPUT_D);
	InputManager::GetInstance().Add(KEY_INPUT_SPACE);
	InputManager::GetInstance().Add(KEY_INPUT_B);
	InputManager::GetInstance().Add(KEY_INPUT_LSHIFT);



	InputManager::MouseInfo info;

	// 左クリック
	info = InputManager::MouseInfo();
	info.key = MOUSE_INPUT_LEFT;
	info.keyOld = false;
	info.keyNew = false;
	info.keyTrgDown = false;
	info.keyTrgUp = false;
	mouseInfos_.emplace(info.key, info);

	// 右クリック
	info = InputManager::MouseInfo();
	info.key = MOUSE_INPUT_RIGHT;
	info.keyOld = false;
	info.keyNew = false;
	info.keyTrgDown = false;
	info.keyTrgUp = false;
	mouseInfos_.emplace(info.key, info);

}

void InputManager::Update(void)
{

	// キーボード検知
	for (auto& p : keyInfos_)
	{
		p.second.keyOld = p.second.keyNew;
		p.second.keyNew = CheckHitKey(p.second.key);
		p.second.keyTrgDown = p.second.keyNew && !p.second.keyOld;
		p.second.keyTrgUp = !p.second.keyNew && p.second.keyOld;
	}

	// マウス検知
	mouseInput_ = GetMouseInput();
	GetMousePoint(&mousePos_.x, &mousePos_.y);

	for (auto& p : mouseInfos_)
	{
		p.second.keyOld = p.second.keyNew;
		p.second.keyNew = mouseInput_ == p.second.key;
		p.second.keyTrgDown = p.second.keyNew && !p.second.keyOld;
		p.second.keyTrgUp = !p.second.keyNew && p.second.keyOld;
	}

	// パッド情報
	SetJPadInState(JOYPAD_NO::KEY_PAD1);
	SetJPadInState(JOYPAD_NO::PAD1);
	SetJPadInState(JOYPAD_NO::PAD2);
	SetJPadInState(JOYPAD_NO::PAD3);
	SetJPadInState(JOYPAD_NO::PAD4);
	// ========================================================
	// ★ 追加：パッド操作をマウス操作に擬似変換して吸収するロジック
	// ========================================================
	if (isPadMouseConvertEnabled_)
	{

		// パッドの入力を取得 (DX_INPUT_PAD1 = 1Pのコントローラー)
		int padInput = GetJoypadInputState(DX_INPUT_PAD1);

		// 現在の入力から、このフレームで「新しく押されたボタン(トリガー)」を計算
		int padTrg = padInput & ~padOldInput_;
		padOldInput_ = padInput; // 次フレームのために保存

		// 十字キーまたは左スティックの入力で擬似カーソルを移動 (縦7マス×横5マス)
		if (padTrg & PAD_INPUT_LEFT) { padCursorX_--; }
		if (padTrg & PAD_INPUT_RIGHT) { padCursorX_++; }
		if (padTrg & PAD_INPUT_UP) { padCursorY_--; }
		if (padTrg & PAD_INPUT_DOWN) { padCursorY_++; }

		// 将棋盤の範囲（横5マス、縦7マス）から出ないようにクランプ
		if (padCursorX_ < 0) padCursorX_ = 0;
		if (padCursorX_ > 4) padCursorX_ = 4;
		if (padCursorY_ < 0) padCursorY_ = 0;
		if (padCursorY_ > 6) padCursorY_ = 6;

		// パッドが少しでも操作された、または決定ボタン（PAD_INPUT_A または PAD_INPUT_1など環境による）が押されている場合
		// ※ここでは一般的にDxLibでボタン1（Aボタン等）に割り当てられる PAD_INPUT_A / PAD_INPUT_1 を判定します
		if ((padInput & (PAD_INPUT_LEFT | PAD_INPUT_RIGHT | PAD_INPUT_UP | PAD_INPUT_DOWN)) || (padInput & PAD_INPUT_1))
		{
			// PlayBpard.cpp の基準座標から、各マスの中心点の画面座標を計算
			// 基準: 左上(485, 0), マス目サイズ: 横116, 縦123
			int targetMouseX = 485 + (padCursorX_ * 116) + (116 / 2);
			int targetMouseY = 0 + (padCursorY_ * 123) + (123 / 2);

			// 1. マウス位置の書き換え
			mousePos_.x = static_cast<float>(targetMouseX);
			mousePos_.y = static_cast<float>(targetMouseY);
			// DxLib自体のマウスカーソルもその位置に同期（見た目のズレを防ぐ場合）
			SetMousePoint(targetMouseX, targetMouseY);

			// 2. 決定ボタンが押されたら、マウスの左クリックが押されたことにする
			if (padInput & PAD_INPUT_1) // PAD_INPUT_1 は通常Aボタン等に相当
			{
				// InputManager内部のマウス状態を「左クリック中」に強制上書き
				mouseInput_ |= MOUSE_INPUT_LEFT;

				if (mouseInfos_.count(MOUSE_INPUT_LEFT) > 0)
				{
					auto& info = mouseInfos_[MOUSE_INPUT_LEFT];
					info.keyNew = true;
					// 前フレームで押されていなければトリガーダウンを成立させる
					if (!info.keyOld) {
						info.keyTrgDown = true;
					}
				}
			}
		}
	}
	if (isPadMouseConvertEnabled_) // ★ 将棋画面の時だけ動くようにフラグチェックを追加！
	{
		// パッドの入力を取得 (DX_INPUT_PAD1 = 1Pのコントローラー)
		int padInput = GetJoypadInputState(DX_INPUT_PAD1);

		int padTrg = padInput & ~padOldInput_;
		padOldInput_ = padInput;

		if (padTrg & PAD_INPUT_LEFT) { padCursorX_--; }
		if (padTrg & PAD_INPUT_RIGHT) { padCursorX_++; }
		if (padTrg & PAD_INPUT_UP) { padCursorY_--; }
		if (padTrg & PAD_INPUT_DOWN) { padCursorY_++; }

		if (padCursorX_ < 0) padCursorX_ = 0;
		if (padCursorX_ > 4) padCursorX_ = 4;
		if (padCursorY_ < 0) padCursorY_ = 0;
		if (padCursorY_ > 6) padCursorY_ = 6;

		if ((padInput & (PAD_INPUT_LEFT | PAD_INPUT_RIGHT | PAD_INPUT_UP | PAD_INPUT_DOWN)) || (padInput & PAD_INPUT_1))
		{
			int targetMouseX = 485 + (padCursorX_ * 116) + (116 / 2);
			int targetMouseY = 0 + (padCursorY_ * 123) + (123 / 2);

			mousePos_.x = static_cast<float>(targetMouseX);
			mousePos_.y = static_cast<float>(targetMouseY);
			SetMousePoint(targetMouseX, targetMouseY);

			if (padInput & PAD_INPUT_1)
			{
				mouseInput_ |= MOUSE_INPUT_LEFT;
				if (mouseInfos_.count(MOUSE_INPUT_LEFT) > 0)
				{
					auto& info = mouseInfos_[MOUSE_INPUT_LEFT];
					info.keyNew = true;
					if (!info.keyOld) {
						info.keyTrgDown = true;
					}
				}
			}
		}
	}
}

void InputManager::Destroy(void)
{
	// インスタンスのメモリ解放
	delete instance_;
}

void InputManager::Add(int key)
{
	InputManager::Info info = InputManager::Info();
	info.key = key;
	info.keyOld = false;
	info.keyNew = false;
	info.keyTrgDown = false;
	info.keyTrgUp = false;
	keyInfos_.emplace(key, info);
}

void InputManager::Clear(void)
{
	keyInfos_.clear();
}

bool InputManager::IsNew(int key) const
{
	return Find(key).keyNew;
}

bool InputManager::IsTrgDown(int key) const
{
	return Find(key).keyTrgDown;
}

bool InputManager::IsTrgUp(int key) const
{
	return Find(key).keyTrgUp;
}

Vector2 InputManager::GetMousePos(void) const
{
	return mousePos_;
}

int InputManager::GetMouse(void) const
{
	return mouseInput_;
}

bool InputManager::IsClickMouseLeft(void) const
{
	return mouseInput_ == MOUSE_INPUT_LEFT;
}

bool InputManager::IsClickMouseRight(void) const
{
	return mouseInput_ == MOUSE_INPUT_RIGHT;
}

bool InputManager::IsTrgMouseLeft(void) const
{
	return FindMouse(MOUSE_INPUT_LEFT).keyTrgDown;
}

bool InputManager::IsTrgMouseRight(void) const
{
	return FindMouse(MOUSE_INPUT_RIGHT).keyTrgDown;
}

InputManager::InputManager(void)
{
	mouseInput_ = -1;
}

const InputManager::Info& InputManager::Find(int key) const
{

	auto it = keyInfos_.find(key);
	if (it != keyInfos_.end())
	{
		return it->second;
	}

	return infoEmpty_;

}

const InputManager::MouseInfo& InputManager::FindMouse(int key) const
{
	auto it = mouseInfos_.find(key);
	if (it != mouseInfos_.end())
	{
		return it->second;
	}

	return mouseInfoEmpty_;
}

InputManager::JOYPAD_TYPE InputManager::GetJPadType(JOYPAD_NO no)
{
	return static_cast<InputManager::JOYPAD_TYPE>(GetJoypadType(static_cast<int>(no)));
}

DINPUT_JOYSTATE InputManager::GetJPadDInputState(JOYPAD_NO no)
{
	// コントローラ情報
	GetJoypadDirectInputState(static_cast<int>(no), &joyDInState_);
	return joyDInState_;
}

XINPUT_STATE InputManager::GetJPadXInputState(JOYPAD_NO no)
{
	// コントローラ情報
	GetJoypadXInputState(static_cast<int>(no), &joyXInState_);
	return joyXInState_;
}

void InputManager::SetJPadInState(JOYPAD_NO jpNo)
{

	int no = static_cast<int>(jpNo);
	auto stateNew = GetJPadInputState(jpNo);
	auto& stateNow = padInfos_[no];

	int max = static_cast<int>(JOYPAD_BTN::MAX);
	for (int i = 0; i < max; i++)
	{

		stateNow.ButtonsOld[i] = stateNow.ButtonsNew[i];
		stateNow.ButtonsNew[i] = stateNew.ButtonsNew[i];

		stateNow.IsOld[i] = stateNow.IsNew[i];
		//stateNow.IsNew[i] = stateNow.ButtonsNew[i] == 128 || stateNow.ButtonsNew[i] == 255;
		stateNow.IsNew[i] = stateNow.ButtonsNew[i] > 0;

		stateNow.IsTrgDown[i] = stateNow.IsNew[i] && !stateNow.IsOld[i];
		stateNow.IsTrgUp[i] = !stateNow.IsNew[i] && stateNow.IsOld[i];


		stateNow.AKeyLX = stateNew.AKeyLX;
		stateNow.AKeyLY = stateNew.AKeyLY;
		stateNow.AKeyRX = stateNew.AKeyRX;
		stateNow.AKeyRY = stateNew.AKeyRY;

	}

}

InputManager::JOYPAD_IN_STATE InputManager::GetJPadInputState(JOYPAD_NO no)
{

	JOYPAD_IN_STATE ret = JOYPAD_IN_STATE();

	auto type = GetJPadType(no);
	
	switch (type)
	{
	case InputManager::JOYPAD_TYPE::OTHER:
		break;
	case InputManager::JOYPAD_TYPE::XBOX_360:
	{
	}
		break;
	case InputManager::JOYPAD_TYPE::XBOX_ONE:
	{

		auto d = GetJPadDInputState(no);
		auto x = GetJPadXInputState(no);

		int idx;

		//   Y
		// X   B
		//   A

		idx = static_cast<int>(JOYPAD_BTN::TOP);
		ret.ButtonsNew[idx] = d.Buttons[3];// Y

		idx = static_cast<int>(JOYPAD_BTN::LEFT);
		ret.ButtonsNew[idx] = d.Buttons[2];// X

		idx = static_cast<int>(JOYPAD_BTN::RIGHT);
		ret.ButtonsNew[idx] = d.Buttons[1];// B

		idx = static_cast<int>(JOYPAD_BTN::DOWN);
		ret.ButtonsNew[idx] = d.Buttons[0];// A

		idx = static_cast<int>(JOYPAD_BTN::R_TRIGGER);
		ret.ButtonsNew[idx] = x.RightTrigger;// R_TRIGGER

		idx = static_cast<int>(JOYPAD_BTN::L_TRIGGER);
		ret.ButtonsNew[idx] = x.LeftTrigger; // L_TRIGGER

		// 左スティック
		ret.AKeyLX = d.X;
		ret.AKeyLY = d.Y;
		
		// 右スティック
		ret.AKeyRX = d.Rx;
		ret.AKeyRY = d.Ry;

	}
		break;
	case InputManager::JOYPAD_TYPE::DUAL_SHOCK_4:
		break;
	case InputManager::JOYPAD_TYPE::DUAL_SENSE:
	{
		
		auto d = GetJPadDInputState(no);
		int idx;

		//   △
		// □  〇
		//   ×

		idx = static_cast<int>(JOYPAD_BTN::TOP);
		ret.ButtonsNew[idx] = d.Buttons[3];// △

		idx = static_cast<int>(JOYPAD_BTN::LEFT);
		ret.ButtonsNew[idx] = d.Buttons[0];// □

		idx = static_cast<int>(JOYPAD_BTN::RIGHT);
		ret.ButtonsNew[idx] = d.Buttons[2];// 〇

		idx = static_cast<int>(JOYPAD_BTN::DOWN);
		ret.ButtonsNew[idx] = d.Buttons[1];// ×

		// 左スティック
		ret.AKeyLX = d.X;
		ret.AKeyLY = d.Y;
		
		// 右スティック
		ret.AKeyRX = d.Z;
		ret.AKeyRY = d.Rz;

	}
		break;
	case InputManager::JOYPAD_TYPE::SWITCH_JOY_CON_L:
		break;
	case InputManager::JOYPAD_TYPE::SWITCH_JOY_CON_R:
		break;
	case InputManager::JOYPAD_TYPE::SWITCH_PRO_CTRL:
		break;
	case InputManager::JOYPAD_TYPE::MAX:
		break;
	}

	return ret;

}

bool InputManager::IsPadBtnNew(JOYPAD_NO no, JOYPAD_BTN btn) const
{
	return padInfos_[static_cast<int>(no)].IsNew[static_cast<int>(btn)];
}

bool InputManager::IsPadBtnTrgDown(JOYPAD_NO no, JOYPAD_BTN btn) const
{
	return padInfos_[static_cast<int>(no)].IsTrgDown[static_cast<int>(btn)];
}

bool InputManager::IsPadBtnTrgUp(JOYPAD_NO no, JOYPAD_BTN btn) const
{
	return padInfos_[static_cast<int>(no)].IsTrgUp[static_cast<int>(btn)];
}


