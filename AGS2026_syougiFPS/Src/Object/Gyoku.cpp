#include "Gyoku.h"
#include "../Manager/ResourceManager.h"
#include <DxLib.h>

Gyoku::Gyoku(int x, int y, bool isPlayer)
    : PieceBase(x, y, isPlayer)
{
    mType = PIECE_OU;

    const Resource& res =
        ResourceManager::GetInstance().Load(
            ResourceManager::SRC::Gyoku
        );

    mModelHandle = res.handleId_;
}

Gyoku::~Gyoku()
{
}

bool Gyoku::CanMove(int x, int y)
{
    int dx = abs(x - mX);
    int dy = abs(y - mY);

    return (dx <= 1 && dy <= 1);
}

void Gyoku ::Draw()
{
    // サイズ
    MV1SetScale(
        mModelHandle,
        VGet(1.0f, 1.0f, 1.0f)
    );

    // 回転
    
        MV1SetRotationXYZ(
            mModelHandle,
            VGet(0.0f, DX_PI_F, 0.0f)
        );
    
  

    // =====================================================
   // モデル自体のズレを補正するためのオフセット
   // ここに数値を入れて、モデルが (0,0,0) の真上に来るように調整します
   // =====================================================
    VECTOR offset = VGet(0.0f, 0.0f, -18.75f); // ← ここに数値を入れる

    // 例：もしモデルが右に1.0ずれているなら offset.x = -1.0f; とする

    MV1SetPosition(
        mModelHandle,
        VAdd(mWorldPos, offset) // ワールド座標に補正値を加算
    );

    MV1DrawModel(mModelHandle);
    //  // =========================
    // // 微調整
    // // =========================

    //  if (CheckHitKey(KEY_INPUT_UP))
    //  {
    //      mWorldPos.z += 0.25f;
    //  }

    //  if (CheckHitKey(KEY_INPUT_DOWN))
    //  {
    //      mWorldPos.z -= 0.25f;
    //  }

    //  if (CheckHitKey(KEY_INPUT_LEFT))
    //  {
    //      mWorldPos.x -= 0.25f;
    //  }

    //  if (CheckHitKey(KEY_INPUT_RIGHT))
    //  {
    //      mWorldPos.x += 0.25f;
    //  }


    //  // =========================
    //// デバッグ表示
    //// =========================

    //  DrawFormatString(
    //      1400,
    //      20,
    //      GetColor(255, 255, 255),
    //      "OU POS X: %.2f",
    //      mWorldPos.x
    //  );

    //  DrawFormatString(
    //      1400,
    //      50,
    //      GetColor(255, 255, 255),
    //      "OU POS Y: %.2f",
    //      mWorldPos.y
    //  );

    //  DrawFormatString(
    //      1400,
    //      80,
    //      GetColor(255, 255, 255),
    //      "OU POS Z: %.2f",
    //      mWorldPos.z
    //  );

    //  DrawFormatString(
    //      1400,
    //      110,
    //      GetColor(255, 255, 255),
    //      "BOARD X:%d",
    //      mX
    //  );

    //  DrawFormatString(
    //      1400,
    //      140,
    //      GetColor(255, 255, 255),
    //      "BOARD Y:%d",
    //      mY
    //  );

  /*DrawSphere3D(
        mWorldPos,
        5.0f,
        16,
        GetColor(255, 0, 0),
        GetColor(255, 0, 0),
        TRUE
    );*/
}