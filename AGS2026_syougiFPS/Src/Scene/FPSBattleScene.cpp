#include "FPSBattleScene.h"
#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/SoundManager.h"
#include "../Common/Camera.h"
#include "../Utility/AsoUtility.h"
#include "../Object/Stage.h"
#include "../Object/Enemy.h"
#include "../Object/Player.h"
#include "../Application.h"

// =================================================================
// ★ PieceType から ResourceManager::SRC (2D画像) に変換する関数
// =================================================================
ResourceManager::SRC ConvertPieceTypeToImageSrc(PieceType type)
{
    switch (type)
    {
    case PieceType::PIECE_OU:     return ResourceManager::SRC::OuImage;
    case PieceType::PIECE_GYOKU:  return ResourceManager::SRC::GyokuImage;
    case PieceType::PIECE_FU:     return ResourceManager::SRC::FuImage;
    case PieceType::PIECE_HISHA:  return ResourceManager::SRC::HishaImage;
    case PieceType::PIECE_KAKU:   return ResourceManager::SRC::KakuImage;
    case PieceType::PIECE_KIN:    return ResourceManager::SRC::KinImage;
    case PieceType::PIECE_GIN:    return ResourceManager::SRC::GinImage;
    default:                      return ResourceManager::SRC::FuImage;
    }
}

FPSBattleScene::FPSBattleScene()
{
}

FPSBattleScene::~FPSBattleScene()
{
}

void FPSBattleScene::Init()
{
    // カットイン演出初期値
    state_ = State::CutIn;
    cutInTimer_ = 0.0f;
    isDebugStop_ = true; // 最初は一時停止状態で起動

    // 初期表示位置 (画面解像度 1280x720 想定)
    leftImgX_ = 300.0f;
    leftImgY_ = 360.0f;
    leftImgScale_ = 0.7f;

    rightImgX_ = 980.0f;
    rightImgY_ = 360.0f;
    rightImgScale_ = 0.7f;

    vsImgX_ = (float)centerX;
    vsImgY_ = (float)centerY;
    vsImgScale_ = 1.04f;

    // カメラの初期化
    camera_ = new Camera();
    camera_->Init();
    camera_->ChangeMode(CameraMode::FPS);

    // ステージの初期化
    stage_ = new Stage();
    stage_->Init();

    // 敵の初期化
    enemy_ = new Enemy();
    enemy_->Init();

    // プレイヤーの初期化
    player_ = new Player();
    player_->Init();

    lightManager_.setBrightness(1.5f);
    lightManager_.setAmbient(0.8f);
    lightManager_.setDirection(0.0f, -1.0f, 1.0f);
    lightManager_.applyLighting();



    SetGlobalAmbientLight(GetColorF(0.5f, 0.5f, 0.5f, 1.0f));
    SetLightDirection(VGet(0.0f, -1.0f, 1.0f));


    crosshairImg_ = LoadGraph("Data/UI/crosshair.png");

    SoundManager::GetInstance().Init();
    SoundManager::GetInstance().PlayBGM(SoundManager::BGM::fps, true);

    // =================================================================
    // 🖼️ 2D画像リソースの読み込み
    // =================================================================
    PieceType attacker = SceneManager::GetInstance().GetAttackerPiece();
    PieceType defender = SceneManager::GetInstance().GetDefenderPiece();

    ResourceManager::SRC attackerSrc = ConvertPieceTypeToImageSrc(attacker);
    ResourceManager::SRC defenderSrc = ConvertPieceTypeToImageSrc(defender);

    leftImgHandle_ = ResourceManager::GetInstance().Load(attackerSrc).handleId_;
    rightImgHandle_ = ResourceManager::GetInstance().Load(defenderSrc).handleId_;
    vsImgHandle_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::VS).handleId_;
}

void FPSBattleScene::AddBullet(VECTOR pos, VECTOR dir)
{
    bullets_.push_back(new Bullet(pos, dir));
}

void FPSBattleScene::Update()
{
    // =================================================================
    // 🛠️ VSカットイン演出中の更新（デバッグ操作対応）
    // =================================================================
    if (state_ == State::CutIn)
    {
        // SPACEキー：演出の「再生 / 一時停止」切り替え
        if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
        {
            isDebugStop_ = !isDebugStop_;
        }

        // --- デバッグ調整モード ---
        if (isDebugStop_)
        {
            float moveSpeed = 2.0f;
            if (CheckHitKey(KEY_INPUT_LSHIFT)) moveSpeed = 8.0f; // Shiftキーで移動高速化

            // 1. 左の駒の移動 (矢印キー) & 拡大縮小 (Z / X)
            if (CheckHitKey(KEY_INPUT_LEFT))  leftImgX_ -= moveSpeed;
            if (CheckHitKey(KEY_INPUT_RIGHT)) leftImgX_ += moveSpeed;
            if (CheckHitKey(KEY_INPUT_UP))    leftImgY_ -= moveSpeed;
            if (CheckHitKey(KEY_INPUT_DOWN))  leftImgY_ += moveSpeed;
            if (CheckHitKey(KEY_INPUT_Z))     leftImgScale_ = max(0.1f, leftImgScale_ - 0.01f);
            if (CheckHitKey(KEY_INPUT_X))     leftImgScale_ += 0.01f;

            // 2. 右の駒の移動 (W / A / S / D) & 拡大縮小 (C / V)
            if (CheckHitKey(KEY_INPUT_A))     rightImgX_ -= moveSpeed;
            if (CheckHitKey(KEY_INPUT_D))     rightImgX_ += moveSpeed;
            if (CheckHitKey(KEY_INPUT_W))     rightImgY_ -= moveSpeed;
            if (CheckHitKey(KEY_INPUT_S))     rightImgY_ += moveSpeed;
            if (CheckHitKey(KEY_INPUT_C))     rightImgScale_ = max(0.1f, rightImgScale_ - 0.01f);
            if (CheckHitKey(KEY_INPUT_V))     rightImgScale_ += 0.01f;

            // 3. VSロゴの移動 (I / J / K / L) & 拡大縮小 (B / N)
            if (CheckHitKey(KEY_INPUT_J))     vsImgX_ -= moveSpeed;
            if (CheckHitKey(KEY_INPUT_L))     vsImgX_ += moveSpeed;
            if (CheckHitKey(KEY_INPUT_I))     vsImgY_ -= moveSpeed;
            if (CheckHitKey(KEY_INPUT_K))     vsImgY_ += moveSpeed;
            if (CheckHitKey(KEY_INPUT_B))     vsImgScale_ = max(0.1f, vsImgScale_ - 0.01f);
            if (CheckHitKey(KEY_INPUT_N))     vsImgScale_ += 0.01f;

            return; // 調整中 タイマー停止
        }

        // --- 通常再生中 ---
        float deltaTime = 1.0f / 60.0f;
        cutInTimer_ += deltaTime;

        if (cutInTimer_ >= 3.0f)
        {
            state_ = State::Playing; // 3秒経過でバトルスタート
            return;
        }

        return;
    }

    // =================================================================
    // ⚔️ 通常のFPS戦闘の更新処理
    // =================================================================

    // カメラの更新
    if (camera_ != nullptr)
    {
        camera_->Update();
    }

    // エネミーの更新
    if (enemy_ != nullptr && player_ != nullptr)
    {
        enemy_->Update(player_->GetPos());
    }

    // プレイヤーの更新
    if (player_ != nullptr)
    {
        player_->Update(camera_);
    }

    // プレイヤーと敵の当たり判定
    if (enemy_ != nullptr && player_ != nullptr)
    {
        SoundManager::GetInstance().PlaySE(SoundManager::SE::Damage);
        if (!player_->IsInvincible())
        {
            float dist = VSize(VSub(enemy_->GetPos(), player_->GetPos()));
            if (dist < enemy_->GetRadius())
            {
                player_->Damage(20);
            }
        }
    }

    // 弾のタイマーを減らす
    if (shotTimer_ > 0)
    {
        shotTimer_--;
    }

    // 射撃判定
    bool isShoot = false;
    if (shotTimer_ <= 0)
    {
        if (GetMouseInput() & MOUSE_INPUT_LEFT) { isShoot = true; }

        if (InputManager::GetInstance().IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::R_TRIGGER)) {
            isShoot = true;
        }
    }

    if (isShoot)
    {
        SoundManager::GetInstance().PlaySE(SoundManager::SE::Attack);
        if (player_ != nullptr && camera_ != nullptr)
        {
            shotTimer_ = SHOT_INTERVAL;

            VECTOR start = camera_->GetPos();
            VECTOR angles = camera_->GetAngles();

            lookDir.x = cosf(angles.x) * sinf(angles.y);
            lookDir.y = -sinf(angles.x);
            lookDir.z = cosf(angles.x) * cosf(angles.y);

            start = VAdd(start, VScale(lookDir, startpoint));
            bullets_.push_back(new Bullet(start, lookDir));
        }
    }

    // 弾の更新処理
    for (auto it = bullets_.begin(); it != bullets_.end();)
    {
        (*it)->Update();

        bool isHit = false;
        if (enemy_ != nullptr)
        {
            float dist = VSize(VSub((*it)->GetPos(), enemy_->GetPos()));

            if (dist < enemy_->GetRadius())
            {
                SoundManager::GetInstance().PlaySE(SoundManager::SE::Damage);
                isHit = true;
                enemy_->Damage(5);
                enemy_->Damage(2);
                hitCount_++;
            }
        }

        if (isHit || (*it)->IsDead())
        {
            delete* it;
            it = bullets_.erase(it);
        }
        else {
            ++it;
        }
    }

    // 敗北判定
    if (player_ != nullptr && player_->GetHP() <= 0)
    {
        SceneManager::GetInstance().SetGameClear(false);
        SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::RESULT);
        return;
    }

    // 勝利判定
    if (enemy_ != nullptr && enemy_->hp_ <= 0)
    {
        SceneManager::GetInstance().SetGameClear(true);
        SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::RESULT);
        return;
    }

    // Enterで将棋画面へ戻る（テスト用）
    if (CheckHitKey(KEY_INPUT_RETURN))
    {
        SceneManager::GetInstance().ChangeScene(
            SceneManager::SCENE_ID::GAME
        );
    }
}

void FPSBattleScene::Draw()
{
    // =================================================================
    // 🛠️ VSカットイン演出中の描画 & デバッグUI
    // =================================================================
    if (state_ == State::CutIn)
    {
        ClearDrawScreen();

        // 1. VSロゴの描画
        if (vsImgHandle_ != -1)
        {
            DrawRotaGraph((int)vsImgX_, (int)vsImgY_, vsImgScale_, 0.0, vsImgHandle_, TRUE);
        }

        // 2. 左側の駒画像の描画
        if (leftImgHandle_ != -1)
        {
            DrawRotaGraph((int)leftImgX_, (int)leftImgY_, leftImgScale_, 0.0, leftImgHandle_, TRUE);
        }

        // 3. 右側の駒画像の描画
        if (rightImgHandle_ != -1)
        {
            DrawRotaGraph((int)rightImgX_, (int)rightImgY_, rightImgScale_, 0.0, rightImgHandle_, TRUE);
        }

        // 4. デバッグUI情報
        SetFontSize(18);
        unsigned int yellow = GetColor(255, 255, 0);
        unsigned int green = GetColor(0, 255, 0);
        unsigned int white = GetColor(255, 255, 255);

        DrawString(20, 20, "=== CUT-IN REALTIME DEBUGGER ===", yellow);
        DrawString(20, 42, "Press [SPACE] to Play / Pause", white);

        if (isDebugStop_)
        {
            DrawString(20, 75, "[LEFT PIECE]  Move: Arrow Keys | Scale: [Z] Down / [X] Up", white);
            DrawString(20, 95, "[RIGHT PIECE] Move: [W/A/S/D]  | Scale: [C] Down / [V] Up", white);
            DrawString(20, 115, "[VS LOGO]     Move: [I/J/K/L]  | Scale: [B] Down / [N] Up", white);

            DrawString(20, 150, "--- CURRENT PARAMETERS ---", yellow);
            DrawFormatString(20, 172, green, "Left Piece  : X = %.1f, Y = %.1f, Scale = %.2f", leftImgX_, leftImgY_, leftImgScale_);
            DrawFormatString(20, 194, green, "Right Piece : X = %.1f, Y = %.1f, Scale = %.2f", rightImgX_, rightImgY_, rightImgScale_);
            DrawFormatString(20, 216, green, "VS Logo     : X = %.1f, Y = %.1f, Scale = %.2f", vsImgX_, vsImgY_, vsImgScale_);
        }
        else
        {
            DrawFormatString(20, 75, green, "Playing... Timer: %.2f / 3.00", cutInTimer_);
        }

        return;
    }

    // =================================================================
    // ⚔️ 通常のFPS戦闘の描画処理
    // =================================================================

    if (camera_ != nullptr)
    {
        camera_->SetBeforeDraw();
    }

    if (stage_ != nullptr)
    {
        stage_->Draw();
    }

    for (int i = 0; i < 40; i++)
    {
        int alpha = 255 - (i * 6);
        if (alpha < 0) alpha = 0;

        SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);
        float currentY = y + (i * 0.15f) + sinf(time + i * 0.1f) * 1.5f;

        DrawLine3D(VGet(-limitx, currentY, -limitz), VGet(limitx, currentY, -limitz), auraColor);
        DrawLine3D(VGet(limitx, currentY, -limitz), VGet(limitx, currentY, limitz), auraColor);
        DrawLine3D(VGet(limitx, currentY, limitz), VGet(-limitx, currentY, limitz), auraColor);
        DrawLine3D(VGet(-limitx, currentY, limitz), VGet(-limitx, currentY, -limitz), auraColor);
    }

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    if (enemy_ != nullptr)
    {
        enemy_->Draw();
    }

    if (player_ != nullptr)
    {
        player_->Draw();
    }

    for (auto b : bullets_) {
        b->Draw();
    }

    if (player_ != nullptr)
    {
        int hpX = 50;
        int hpY = Application::SCREEN_SIZE_Y - 100;
        unsigned int color = player_->IsInvincible() ? GetColor(255, 165, 0) : GetColor(0, 255, 0);

        DrawFormatString(hpX, hpY, color, "PLAYER HP: %d / 100 %s",
            player_->GetHP(), player_->IsInvincible() ? "[INVINCIBLE]" : "");
    }

    if (crosshairImg_ != -1)
    {
        DrawRotaGraph(centerX, centerY, 1.0, 0.0, crosshairImg_, TRUE);
    }

    DrawFormatString(0, 0, GetColor(255, 255, 255), "Bullet Count: %d", bullets_.size());
    DrawFormatString(0, 50, GetColor(0, 255, 0), "Hit Count: %d", hitCount_);

    if (enemy_ != nullptr)
    {

        DrawFormatString(0, 75, GetColor(255, 0, 0),"ENEMY HP: %d / 500", enemy_->GetHp());

        DrawFormatString(0, 75, GetColor(255, 0, 0), "ENEMY HP: %d / 500", enemy_->hp_);

    }
}

void FPSBattleScene::Release()
{
    if (stage_ != nullptr)
    {
        stage_->Release();
        delete stage_;
        stage_ = nullptr;
    }

    if (enemy_ != nullptr)
    {
        delete enemy_;
        enemy_ = nullptr;
    }

    if (player_ != nullptr)
    {
        delete player_;
        player_ = nullptr;
    }

    if (camera_ != nullptr) {
        camera_->Release();
        delete camera_;
        camera_ = nullptr;
    }

    if (crosshairImg_ != -1)
    {
        DeleteGraph(crosshairImg_);
        crosshairImg_ = -1;
    }

    SoundManager::GetInstance().Release();
}