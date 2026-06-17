#include "Kaku.h"
#include "../Manager/ResourceManager.h"
#include <DxLib.h>
#include <cmath> // abs関数（絶対値計算）を使用するために追加

Kaku::Kaku(int x, int y, bool isPlayer)
    : PieceBase(x, y, isPlayer)
{
    // 駒の種類を角に設定（もしPieceTypeにPIECE_KAKUがない場合はpieceBase.hに追加してください）
    mType = PIECE_KAKU;

    // ResourceManagerから角用のリソースをロード（環境に合わせてSRC::Kaku等の定数は調整してください）
    const Resource& res =
        ResourceManager::GetInstance().Load(
            ResourceManager::SRC::Kaku
        );

    mModelHandle =
        MV1DuplicateModel(res.handleId_);

    if (mModelHandle == -1)
    {
        printfDx("Kaku model load failed\n");
    }
}

Kaku::~Kaku()
{
    MV1DeleteModel(mModelHandle);
}

bool Kaku::CanMove(int x, int y)
{
    int dx = x - mX;
    int dy = y - mY;

    // 移動していない場合は偽
    if (dx == 0 && dy == 0) return false;

    // 横方向の移動距離と縦方向の移動距離の「絶対値」が等しければ斜め移動
    // （例: 右に2、下に2進む場合は |2| == |-2| で真となる）
    return (std::abs(dx) == std::abs(dy));
}

void Kaku::Draw()
{
    // スケールの設定
    MV1SetScale(
        mModelHandle,
        VGet(1.0f, 1.0f, 1.0f)
    );

    // =====================================================
    // 回転とオフセットの設定（飛車をベースにしています）
    // =====================================================
    VECTOR offset;

    if (mIsPlayer)
    {
        // プレイヤー側：回転なし
        MV1SetRotationXYZ(mModelHandle, VGet(0.0f, 0.0f, 0.0f));

        // プレイヤー専用のオフセット（モデルの基準点に合わせて微調整してください）
        offset = VGet(13.0f, 0.0f, 14.0f);
    }
    else
    {
        // 敵側：180度回転
        MV1SetRotationXYZ(mModelHandle, VGet(0.0f, DX_PI_F, 0.0f));

        // 敵専用のオフセット（モデルの基準点に合わせて微調整してください）
        offset = VGet(-13.5f, 0.0f, -14.0f);
    }

    MV1SetPosition(
        mModelHandle,
        VAdd(mWorldPos, offset) // ワールド座標に補正値を加算
    );

    MV1DrawModel(mModelHandle);

    //// デバッグ用：本来の「中心」である mWorldPos に球を表示
    //DrawSphere3D(mWorldPos, 0.1f, 10, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);

 //       =========================
 //  微調整
 //  =========================

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

 // 
 //  =========================
 //デバッグ表示
 //=========================

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
}