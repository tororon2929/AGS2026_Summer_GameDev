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
    // ƒTƒCƒY
    MV1SetScale(
        mModelHandle,
        VGet(8.0f, 8.0f, 8.0f)
    );

    // ‰ñ“]
    if (mIsPlayer)
    {
        MV1SetRotationXYZ(
            mModelHandle,
            VGet(0.0f, DX_PI_F, 0.0f)
        );
    }
    else
    {
        MV1SetRotationXYZ(
            mModelHandle,
            VGet(0.0f, 0.0f, 0.0f)
        );
    }

    // À•W
    MV1SetPosition(
        mModelHandle,
        mWorldPos
    );

    // •`‰æ
    MV1DrawModel(mModelHandle);

    DrawSphere3D(
        mWorldPos,
        5.0f,
        16,
        GetColor(255, 0, 0),
        GetColor(255, 0, 0),
        TRUE
    );
}