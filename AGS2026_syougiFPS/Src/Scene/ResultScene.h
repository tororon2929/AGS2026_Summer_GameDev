#pragma once
#include "SceneBase.h"

class ResultScene : public SceneBase
{
public:

    ResultScene();
    ~ResultScene();

    void Init() override;
    void Update() override;
    void Draw() override;
    void Release() override;

private:
    int WinImage;
    int LoseImage;
    int logoX_;
    int logoY_;
    double logoScale_;

};