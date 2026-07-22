#pragma once
#include <DxLib.h>
#include <vector>
#include "SceneBase.h"
#include "../Object/Enemy.h"
#include "../Object/Bullet.h"
#include "../Application.h"
#include "../Manager/LightManager.h"
#include "../Object/PieceBase.h" 

class Enemy;
class Player;
class Camera;
class Stage;
class Bullet;

class FPSBattleScene : public SceneBase
{
public:
    FPSBattleScene();
    ~FPSBattleScene();

    void Init() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    int hitCount_ = 0;

    // 弾を追加する関数
    void AddBullet(VECTOR pos, VECTOR dir);

private:
    Enemy* enemy_ = nullptr;
    Player* player_ = nullptr;
    Camera* camera_ = nullptr;
    Stage* stage_ = nullptr;
    LightManager lightManager_;

    VECTOR lookDir;
    std::vector<Bullet*> bullets_;

    float limitx = 25.0f;
    float limitz = 25.0f;
    float y = 25.0f;
    float time = GetNowCount() / 300.0f;

	//�e�����˂����ʒu
    float startpoint = 1.0f;
    



    int crosshairImg_ = -1;
    int centerX = Application::SCREEN_SIZE_X / 2;
    int centerY = Application::SCREEN_SIZE_Y / 2;
    int shotTimer_ = 0;

	// �e�̔��ˊԊu�i�t���[�����j
	const int SHOT_INTERVAL = 30; // 15�t���[��

    const int SHOT_INTERVAL = 15; // 15フレーム

    unsigned int auraColor = GetColor(255, 0, 0);

    // =================================================================
    // ⚔️ 2Dカットイン演出 & デバッグ用変数
    // =================================================================
    enum class State
    {
        CutIn,      // VSカットイン演出中
        Playing,    // 通常のFPSバトル中
    };
    State state_ = State::CutIn;

    float cutInTimer_ = 0.0f;

    // 2D画像用ハンドル
    int leftImgHandle_ = -1;   // 攻撃側の駒画像
    int rightImgHandle_ = -1;  // 防御側の駒画像
    int vsImgHandle_ = -1;     // VSロゴ画像

    // デバッグ状態管理
    bool isDebugStop_ = true;  // 最初は一時停止状態で調整可能

    // 調整用パラメータ（座標 & 拡大率）
    float leftImgX_ = 300.0f;
    float leftImgY_ = 360.0f;
    float leftImgScale_ = 0.7f;

    float rightImgX_ = 980.0f;
    float rightImgY_ = 360.0f;
    float rightImgScale_ = 1.0f;

    float vsImgX_ = 640.0f;
    float vsImgY_ = 360.0f;
    float vsImgScale_ = 1.0f;
};