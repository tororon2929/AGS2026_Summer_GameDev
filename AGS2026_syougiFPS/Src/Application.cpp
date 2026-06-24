#include <DxLib.h>
#include "Application.h"
#include "Manager/InputManager.h"
#include "Manager/SceneManager.h"
#include "Manager/ResourceManager.h"

// 静的メンバの実体定義（リンクエラー LNK2001 対策）
Application* Application::instance_ = nullptr;
const std::string Application::PATH_MODEL = "Data/Model/";
const std::string Application::PATH_IMAGE = "Data/Image/";
const std::string Application::PATH_EFFECT = "Data/Effect/";
const std::string Application::PATH_UI = "Data/UI";

Application::Application(void) : isInitFail_(false), isReleaseFail_(false) {}

void Application::CreateInstance(void) {
    if (instance_ == nullptr) instance_ = new Application();
    instance_->Init();
}

Application& Application::GetInstance(void) { return *instance_; }

bool Application::IsInitFail(void) const { return isInitFail_; }
bool Application::IsReleaseFail(void) const { return isReleaseFail_; }

void Application::Init(void) {
    SetWindowText("3DWorld");

    // 1. 2人のPCで共通の「ゲーム内解像度(1920x1080)」をセット
    SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

    // 2. ウインドウの枠（タイトルバーや閉じるボタン）を非表示にする
    SetWindowStyleMode(2);

    // 3. ウインドウモードとして起動しつつ、デスクトップ全体にフィットさせる（擬似フルスクリーン）
    ChangeWindowMode(TRUE);
    SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);

    SetUseDirect3DVersion(DX_DIRECT3D_11);

    if (DxLib_Init() == -1) {
        isInitFail_ = true;
        return;
    }

    // 生成順序：リソースマネージャーを最優先にする
    ResourceManager::CreateInstance();
    InputManager::CreateInstance();
    SceneManager::CreateInstance();

    SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 50.0f, -100.0f), VGet(0.0f, 0.0f, 0.0f));
    SetWriteZBuffer3D(TRUE);
    SetUseZBuffer3D(TRUE);
}

void Application::Run(void) {
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
        InputManager::GetInstance().Update();
        SceneManager::GetInstance().Update();

        ClearDrawScreen();


        SceneManager::GetInstance().Draw();
        ScreenFlip();
    }
}

void Application::Destroy(void) {
    SceneManager::GetInstance().Destroy();
    InputManager::GetInstance().Destroy();
    ResourceManager::GetInstance().Destroy();
    DxLib_End();
    delete instance_;
    instance_ = nullptr;
}