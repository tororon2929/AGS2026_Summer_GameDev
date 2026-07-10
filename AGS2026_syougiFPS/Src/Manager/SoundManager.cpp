#include "SoundManager.h"
#include <DxLib.h>

void SoundManager::Init()
{
	// 既存のハンドルがあれば一度クリア
	Release();

	// ========================================================
	// ★ 音声ファイルの読み込み（パスは環境に合わせて調整してください）
	// ========================================================
	bgmHandles_[BGM::Title] = LoadSoundMem("Data/Effect/BGM/Title.mp3");
	bgmHandles_[BGM::Game] = LoadSoundMem("Data/Effect/BGM/wate.mp3");
	bgmHandles_[BGM::sisi] = LoadSoundMem("Data/Effect/BGM/sisiodosi.mp3");
	bgmHandles_[BGM::fps] = LoadSoundMem("Data/Effect/BGM/BatteleBGM.mp3");

	// SEの読み込み例
	 seHandles_[SE::Select] = LoadSoundMem("Data/Effect/SE/Select.mp3");
	 seHandles_[SE::Shot1] = LoadSoundMem("Data/Effect/SE/Shot1.mp3");
	 seHandles_[SE::Attack] = LoadSoundMem("Data/Effect/SE/Attack.mp3");
	 seHandles_[SE::Jamp] = LoadSoundMem("Data/Effect/SE/Jamp.mp3");
	 seHandles_[SE::Damage] = LoadSoundMem("Data/Effect/SE/Damage.mp3");

	// seHandles_[SE::Confirm] = LoadSoundMem("Resource/Sound/confirm.wav");
}

void SoundManager::Release()
{
	// すべてのBGMハンドルを削除
	for (auto& pair : bgmHandles_)
	{
		if (pair.second != -1)
		{
			DeleteSoundMem(pair.second);
		}
	}
	bgmHandles_.clear();

	// すべてのSEハンドルを削除
	for (auto& pair : seHandles_)
	{
		if (pair.second != -1)
		{
			DeleteSoundMem(pair.second);
		}
	}
	seHandles_.clear();
	isBgmPlaying_ = false;
}

void SoundManager::PlayBGM(BGM bgm, bool loop)
{
	// 再生対象のハンドルがあるか確認
	if (bgmHandles_.find(bgm) == bgmHandles_.end() || bgmHandles_[bgm] == -1) return;

	// 既に同じBGMが流れているなら何もしない
	if (isBgmPlaying_ && currentBgm_ == bgm) return;

	// 別のBGMが流れている場合は止める
	if (isBgmPlaying_)
	{
		StopBGM();
	}

	int playType = loop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK;
	PlaySoundMem(bgmHandles_[bgm], playType, TRUE);

	currentBgm_ = bgm;
	isBgmPlaying_ = true;
}

void SoundManager::StopBGM()
{
	if (!isBgmPlaying_) return;

	if (bgmHandles_.find(currentBgm_) != bgmHandles_.end() && bgmHandles_[currentBgm_] != -1)
	{
		StopSoundMem(bgmHandles_[currentBgm_]);
	}
	isBgmPlaying_ = false;
}

void SoundManager::SetBGMVolume(int volume)
{
	for (auto& pair : bgmHandles_)
	{
		if (pair.second != -1)
		{
			ChangeVolumeSoundMem(volume, pair.second);
		}
	}
}

void SoundManager::PlaySE(SE se)
{
	if (seHandles_.find(se) == seHandles_.end() || seHandles_[se] == -1) return;

	// SEは重ねて再生できるようにDX_PLAYTYPE_BACK、TopPositionをTRUEに
	PlaySoundMem(seHandles_[se], DX_PLAYTYPE_BACK, TRUE);
}

void SoundManager::SetSEVolume(int volume)
{
	for (auto& pair : seHandles_)
	{
		if (pair.second != -1)
		{
			ChangeVolumeSoundMem(volume, pair.second);
		}
	}
}