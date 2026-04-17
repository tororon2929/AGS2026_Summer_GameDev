#include <DxLib.h>
#include "SceneManager.h"
#include "TitleScene.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    SetWindowText("Scene Sample");
    SetGraphMode(640, 480, 32);
    ChangeWindowMode(TRUE);

    if (DxLib_Init() == -1) return -1;
    SetDrawScreen(DX_SCREEN_BACK);

    SceneManager manager(new TitleScene());

    while (ProcessMessage() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE)) {
        ClearDrawScreen();
        manager.Update();
        manager.Draw();
        ScreenFlip();
    }

    DxLib_End();
    return 0;
}