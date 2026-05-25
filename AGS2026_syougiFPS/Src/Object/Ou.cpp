#include "Ou.h"
#include "../Manager/ResourceManager.h"
#include <DxLib.h>

Ou::Ou(int x, int y, bool isPlayer)
    : PieceBase(x, y, isPlayer)
{
    mType = PIECE_OU;

    const Resource& res =
        ResourceManager::GetInstance().Load(
            ResourceManager::SRC::Ou
        );

    mModelHandle = res.handleId_;
}
Ou::~Ou()
{
    

}

bool Ou::CanMove(int x, int y)
{
    int dx = abs(x - mX);
    int dy = abs(y - mY);

    return (dx <= 1 && dy <= 1);
}

void Ou::Draw()
{
    // サイズ
    MV1SetScale(
        mModelHandle,
        VGet(8.0f, 8.0f, 8.0f)
    );

    MV1SetRotationXYZ(
        mModelHandle,
        VGet(0.0f, 0.0f, 0.0f)
    );
    // 座標
    MV1SetPosition(
        mModelHandle,
        mWorldPos
    );

    // 描画
    MV1DrawModel(mModelHandle);


}