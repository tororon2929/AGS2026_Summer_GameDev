#include "SceneManager.h"

SceneManager::SceneManager(SceneBase* initialScene)
    : mCurrent(initialScene) {
}

SceneManager::~SceneManager() {
    delete mCurrent;
    delete mNext;
}

void SceneManager::Update() {
    if (!mCurrent) return;

    mFade.Update();

    // ── フェード中でなければ現シーンを通常更新 ──────────────
    if (!mFade.IsFading()) {
        mCurrent->Update();

        // シーンが次へ行きたいか確認
        SceneBase* next = mCurrent->NextScene();
        if (next) {
            mNext = next;           // 切替先を保存
            mFade.StartFadeOut();   // フェードアウト開始
        }
    }

    // ── 真っ暗になった瞬間にシーンを切り替える ───────────────
    if (mFade.IsBlack()) {
        delete mCurrent;
        mCurrent = mNext;
        mNext = nullptr;
        mFade.StartFadeIn();        // フェードイン開始
    }
}

void SceneManager::Draw() {
    if (mCurrent) mCurrent->Draw();
    mFade.Draw();   // シーン描画の上に重ねる
}