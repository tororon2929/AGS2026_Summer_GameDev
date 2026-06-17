#include "Hisha.h"
#include "../Manager/ResourceManager.h"
#include <DxLib.h>

Hisha::Hisha(int x, int y, bool isPlayer)
    : PieceBase(x, y, isPlayer)
{
    // 駒の種類を飛車に設定 (列挙型名は環境に合わせて調整してください)
    mType = PIECE_HISHA;

    const Resource& res =
        ResourceManager::GetInstance().Load(
            ResourceManager::SRC::Hisha
        );

    mModelHandle =
        MV1DuplicateModel(res.handleId_);

    if (mModelHandle == -1)
    {
        printfDx("Hisha model load failed\n");
    }
}

Hisha::~Hisha()
{
    MV1DeleteModel(mModelHandle);
}

bool Hisha::CanMove(int x, int y)
{
    int dx = x - mX;
    int dy = y - mY;

    // 移動していない場合は偽
    if (dx == 0 && dy == 0) return false;

    // 縦または横の直線移動であれば真 (飛車の動き)
    // ※ 間に他の駒があるかどうかの「飛び越し判定」は盤面管理側で行うのが一般的です
    return (dx == 0 || dy == 0);
}

void Hisha::Draw()
{
    // スケールの設定
    MV1SetScale(
        mModelHandle,
        VGet(1.0f, 1.0f, 1.0f)
    );

    // =====================================================
    // 回転とオフセットの設定
    // =====================================================
    VECTOR offset;

    if (mIsPlayer)
    {
        // プレイヤー側：回転なし
        MV1SetRotationXYZ(mModelHandle, VGet(0.0f, 0.0f, 0.0f));

        // プレイヤー専用のオフセット（モデルに合わせて微調整してください）
        offset = VGet(-13.0f, 0.0f, 14.0f);
    }
    else
    {
        // 敵側：180度回転
        MV1SetRotationXYZ(mModelHandle, VGet(0.0f, DX_PI_F, 0.0f));

        // 敵専用のオフセット（モデルに合わせて微調整してください）
        offset = VGet(13.5f, 0.0f, -14.0f);
    }

    MV1SetPosition(
        mModelHandle,
        VAdd(mWorldPos, offset) // ワールド座標に補正値を加算
    );

    MV1DrawModel(mModelHandle);

    //// デバッグ用：本来の「中心」である mWorldPos に球を表示
    //DrawSphere3D(mWorldPos, 0.1f, 10, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);

   //    // =========================
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

 //   DrawFormatString(
 //       1400,
 //       20,
 //       GetColor(255, 255, 255),
 //       "OU POS X: %.2f",
 //       mWorldPos.x
 //   );

 //   DrawFormatString(
 //       1400,
 //       50,
 //       GetColor(255, 255, 255),
 //       "OU POS Y: %.2f",
 //       mWorldPos.y
 //   );

 //   DrawFormatString(
 //       1400,
 //       80,
 //       GetColor(255, 255, 255),
 //       "OU POS Z: %.2f",
 //       mWorldPos.z
 //   );

 //   DrawFormatString(
 //       1400,
 //       110,
 //       GetColor(255, 255, 255),
 //       "BOARD X:%d",
 //       mX
 //   );

 //   DrawFormatString(
 //       1400,
 //       140,
 //       GetColor(255, 255, 255),
 //       "BOARD Y:%d",
 //       mY
 //   );
}