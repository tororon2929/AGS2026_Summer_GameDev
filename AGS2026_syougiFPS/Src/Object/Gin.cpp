#include "Gin.h"
#include "../Manager/ResourceManager.h"
#include <DxLib.h>
#include <cmath> // std::abs関数を使用するために追加

Gin::Gin(int x, int y, bool isPlayer)
    : PieceBase(x, y, isPlayer)
{
    // 駒の種類を銀に設定（必要に応じてpieceBase.hのPieceTypeにPIECE_GINを追加してください）
    mType = PIECE_GIN;

    // ResourceManagerから銀用のリソースをロード（定数名は環境に合わせて調整してください）
    const Resource& res =
        ResourceManager::GetInstance().Load(
            ResourceManager::SRC::Gin
        );

    mModelHandle =
        MV1DuplicateModel(res.handleId_);

    if (mModelHandle == -1)
    {
        printfDx("Gin model load failed\n");
    }
}

Gin::~Gin()
{
    MV1DeleteModel(mModelHandle);
}

bool Gin::CanMove(int x, int y)
{
    int dx = x - mX;
    int dy = y - mY;

    // 移動していない場合は偽
    if (dx == 0 && dy == 0) return false;

    // 縦・横どちらも1マスを超える移動は不可
    if (std::abs(dx) > 1 || std::abs(dy) > 1) return false;

    // 1. 斜め4方向のチェック（縦の移動距離と横の移動距離がどちらも1マスのとき）
    if (std::abs(dx) == 1 && std::abs(dy) == 1)
    {
        return true; // 斜めは前後問わずどこでもOK
    }

    // 2. 直線（縦・横）のチェック
    if (mIsPlayer)
    {
        // プレイヤー側：上方向（yが減る方向）のみ真横・後ろは不可
        // つまり、横移動がなく（dx==0）、上に1マス進む（dy==-1）場合だけ許可
        if (dx == 0 && dy == -1)
        {
            return true;
        }
    }
    else
    {
        // 敵側：下方向（yが増える方向）のみ真横・後ろは不可
        // つまり、横移動がなく（dx==0）、下に1マス進む（dy==1）場合だけ許可
        if (dx == 0 && dy == 1)
        {
            return true;
        }
    }

    // 斜めでもなく、許可された前方1マスでもない場合は移動不可（真横や真後ろなど）
    return false;
}

void Gin::Draw()
{
    // スケールの設定
    MV1SetScale(
        mModelHandle,
        VGet(1.0f, 1.0f, 1.0f)
    );

    // =====================================================
    // 回転とオフセットの設定（金や飛車をベースにしています）
    // =====================================================
    VECTOR offset;

    if (mIsPlayer)
    {
        // プレイヤー側：回転なし
        MV1SetRotationXYZ(mModelHandle, VGet(0.0f, 0.0f, 0.0f));

        // プレイヤー専用のオフセット（モデルに合わせて微調整してください）
        offset = VGet(9.0f, 0.0f, 19.0f);
    }
    else
    {
        // 敵側：180度回転
        MV1SetRotationXYZ(mModelHandle, VGet(0.0f, DX_PI_F, 0.0f));

        // 敵専用のオフセット（モデルに合わせて微調整してください）
        offset = VGet(-9.0f, 0.0f, -19.0f);
    }

    MV1SetPosition(
        mModelHandle,
        VAdd(mWorldPos, offset) // ワールド座標に補正値を加算
    );

    MV1DrawModel(mModelHandle);

    //// デバッグ用：本来の「中心」である mWorldPos に球を表示
    //DrawSphere3D(mWorldPos, 0.1f, 10, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);
//       // =========================
//  // 微調整
//  // =========================
//
//   if (CheckHitKey(KEY_INPUT_UP))
//   {
//       mWorldPos.z += 0.25f;
//   }
//
//   if (CheckHitKey(KEY_INPUT_DOWN))
//   {
//       mWorldPos.z -= 0.25f;
//   }
//
//   if (CheckHitKey(KEY_INPUT_LEFT))
//   {
//       mWorldPos.x -= 0.25f;
//   }
//
//   if (CheckHitKey(KEY_INPUT_RIGHT))
//   {
//       mWorldPos.x += 0.25f;
//   }
//
//  
//  // =========================
//// デバッグ表示
//// =========================
//
//   DrawFormatString(
//       1400,
//       20,
//       GetColor(255, 255, 255),
//       "OU POS X: %.2f",
//       mWorldPos.x
//   );
//
//   DrawFormatString(
//       1400,
//       50,
//       GetColor(255, 255, 255),
//       "OU POS Y: %.2f",
//       mWorldPos.y
//   );
//
//   DrawFormatString(
//       1400,
//       80,
//       GetColor(255, 255, 255),
//       "OU POS Z: %.2f",
//       mWorldPos.z
//   );
//
//   DrawFormatString(
//       1400,
//       110,
//       GetColor(255, 255, 255),
//       "BOARD X:%d",
//       mX
//   );
//
//   DrawFormatString(
//       1400,
//       140,
//       GetColor(255, 255, 255),
//       "BOARD Y:%d",
//       mY
//   );
}