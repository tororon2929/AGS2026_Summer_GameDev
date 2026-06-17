#include "Kin.h"
#include "../Manager/ResourceManager.h"
#include <DxLib.h>
#include <cmath> // std::abs関数を使用するために追加

Kin::Kin(int x, int y, bool isPlayer)
    : PieceBase(x, y, isPlayer)
{
    // 駒の種類を金に設定（必要に応じてpieceBase.hのPieceTypeにPIECE_KINを追加してください）
    mType = PIECE_KIN;

    // ResourceManagerから金用のリソースをロード（定数名は環境に合わせて調整してください）
    const Resource& res =
        ResourceManager::GetInstance().Load(
            ResourceManager::SRC::Kin
        );

    mModelHandle =
        MV1DuplicateModel(res.handleId_);

    if (mModelHandle == -1)
    {
        printfDx("Kin model load failed\n");
    }
}

Kin::~Kin()
{
    MV1DeleteModel(mModelHandle);
}

bool Kin::CanMove(int x, int y)
{
    int dx = x - mX;
    int dy = y - mY;

    // 移動していない場合は偽
    if (dx == 0 && dy == 0) return false;

    // 縦・横どちらも1マスを超える移動は不可
    if (std::abs(dx) > 1 || std::abs(dy) > 1) return false;

    if (mIsPlayer)
    {
        // -------------------------------------------------
        // プレイヤー側（上方向へ進む / yが減る方向が「前」）
        // -------------------------------------------------
        // 斜め後ろ（左右に1マス、かつ下に1マス進む場合）は移動不可
        if (std::abs(dx) == 1 && dy == 1)
        {
            return false;
        }
    }
    else
    {
        // -------------------------------------------------
        // 敵側（下方向へ進む / yが増える方向が「前」）
        // -------------------------------------------------
        // 斜め後ろ（左右に1マス、かつ上に1マス進む場合）は移動不可
        if (std::abs(dx) == 1 && dy == -1)
        {
            return false;
        }
    }

    // 上記の「斜め後ろ」の制限に引っかからず、1マス以内の移動であれば全て真
    return true;
}

void Kin::Draw()
{
    // スケールの設定
    MV1SetScale(
        mModelHandle,
        VGet(1.0f, 1.0f, 1.0f)
    );

    // =====================================================
    // 回転とオフセットの設定（飛車・角をベースにしています）
    // =====================================================
    VECTOR offset;

    if (mIsPlayer)
    {
        // プレイヤー側：回転なし
        MV1SetRotationXYZ(mModelHandle, VGet(0.0f, 0.0f, 0.0f));

        // プレイヤー専用のオフセット（モデルに合わせて微調整してください）
        offset = VGet(4.5f, 0.0f, 19.0f);
    }
    else
    {
        // 敵側：180度回転
        MV1SetRotationXYZ(mModelHandle, VGet(0.0f, DX_PI_F, 0.0f));

        // 敵専用のオフセット（モデルに合わせて微調整してください）
        offset = VGet(-4.5f, 0.0f, -19.0f);
    }

    MV1SetPosition(
        mModelHandle,
        VAdd(mWorldPos, offset) // ワールド座標に補正値を加算
    );

    MV1DrawModel(mModelHandle);

  //  // デバッグ用：本来の「中心」である mWorldPos に球を表示
  //  DrawSphere3D(mWorldPos, 0.1f, 10, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);
  //     // =========================
  //// 微調整
  //// =========================

  // if (CheckHitKey(KEY_INPUT_UP))
  // {
  //     mWorldPos.z += 0.25f;
  // }

  // if (CheckHitKey(KEY_INPUT_DOWN))
  // {
  //     mWorldPos.z -= 0.25f;
  // }

  // if (CheckHitKey(KEY_INPUT_LEFT))
  // {
  //     mWorldPos.x -= 0.25f;
  // }

  // if (CheckHitKey(KEY_INPUT_RIGHT))
  // {
  //     mWorldPos.x += 0.25f;
  // }

  
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