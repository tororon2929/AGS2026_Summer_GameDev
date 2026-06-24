#include "Fu.h"
#include "../Manager/ResourceManager.h"
#include <DxLib.h>

Fu::Fu(int x, int y, bool isPlayer)
    : PieceBase(x, y, isPlayer)
{
    mType = PIECE_FU;

    const Resource& res =
        ResourceManager::GetInstance().Load(
            ResourceManager::SRC::Fu
        );

    mModelHandle =
        MV1DuplicateModel(res.handleId_);

    if (mModelHandle == -1)
    {
        printfDx("Fu model load failed\n");
    }
}

Fu::~Fu()
{
    MV1DeleteModel(mModelHandle);
}

bool Fu::CanMove(int x, int y)
{
    int dx = x - mX;
    int dy = y - mY;

    // =========================
    // プレイヤー側
    // =========================

    if (mIsPlayer)
    {
        return (dx == 0 && dy == -1);
    }

    // =========================
    // 敵側
    // =========================

    return (dx == 0 && dy == 1);
}

void Fu::Draw()
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

        // プレイヤー専用のオフセット
        offset = VGet(17.5f, 0.0f, 9.25f);
    }
    else
    {
        // 敵側：180度回転
        MV1SetRotationXYZ(mModelHandle, VGet(0.0f, DX_PI_F, 0.0f));

        // 敵専用のオフセット（ここで微調整してください）
        // 回転させたことで、軸の向きが変わっている場合があるため個別に設定します
        offset = VGet(-17.5f, 0.0f, -9.25f);
    } 
    MV1SetPosition(
        mModelHandle,
        VAdd(mWorldPos, offset) // ワールド座標に補正値を加算
    );

    MV1DrawModel(mModelHandle);

    //// デバッグ用：本来の「中心」である mWorldPos に球を表示
    //DrawSphere3D(mWorldPos, 0.1f, 10, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);

 //   // =========================
 //  // 微調整
 //  // =========================

 //   if (CheckHitKey(KEY_INPUT_UP))
 //   {
 //       mWorldPos.z += 0.25f;
 //   }

 //   if (CheckHitKey(KEY_INPUT_DOWN))
 //   {
 //       mWorldPos.z -= 0.25f;
 //   }

 //   if (CheckHitKey(KEY_INPUT_LEFT))
 //   {
 //       mWorldPos.x -= 0.25f;
 //   }

 //   if (CheckHitKey(KEY_INPUT_RIGHT))
 //   {
 //       mWorldPos.x += 0.25f;
 //   }

 //  
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
    //// X軸 (赤), Y軸 (緑), Z軸 (青) を描画
    //DrawLine3D(VGet(-100, 0, 0), VGet(100, 0, 0), GetColor(255, 0, 0)); // X軸
    //DrawLine3D(VGet(0, -100, 0), VGet(0, 100, 0), GetColor(0, 255, 0)); // Y軸
    //DrawLine3D(VGet(0, 0, -100), VGet(0, 0, 100), GetColor(0, 0, 255)); // Z軸
}