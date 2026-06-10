#pragma once
#include <DxLib.h>

class Stage
{
public:
    Stage();
    ~Stage();

    void Init();
    void Draw();
    void Release();

private:
    int modelId_ = -1; // ステージモデルのID
};

