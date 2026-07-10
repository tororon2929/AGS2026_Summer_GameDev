#pragma once
#include <unordered_map>
#include <string>

class SoundManager
{
public:
	// 音声の種類を列挙型で定義（今後SEや他のBGMをここに追加していけます）
	enum class BGM
	{
		Title,
		 Game, // 今後追加可能
		 fps,
		 sisi
	};

	enum class SE
	{
		Select,
		Confirm,
		Shot1,
		Attack,
		Jamp,
		Damage,
	
		// Click, // 今後追加可能
	};

	// シングルトンのインスタンス取得
	static SoundManager& GetInstance()
	{
		static SoundManager instance;
		return instance;
	}

	// 初期化・解放処理
	void Init();
	void Release();

	// BGM関連の操作
	void PlayBGM(BGM bgm, bool loop = true);
	void StopBGM();
	void SetBGMVolume(int volume); // 0 ～ 255

	// SE関連の操作
	void PlaySE(SE se);
	void SetSEVolume(int volume);  // 0 ～ 255

private:
	SoundManager() = default;
	~SoundManager() = default;

	// コピーと代入を禁止
	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;

	// ハンドル管理用のマップ
	std::unordered_map<BGM, int> bgmHandles_;
	std::unordered_map<SE, int> seHandles_;

	BGM currentBgm_ = BGM::Title;
	bool isBgmPlaying_ = false;
};