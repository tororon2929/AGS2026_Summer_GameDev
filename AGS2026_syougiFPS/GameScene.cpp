#include "GameScene.h"
#include "GameOverScene.h"
#include "DxLib.h"

GameScene::GameScene()
{
    mBoard.Init();
}

void GameScene::Update()
{
    // カーソル移動
    mCursor.Update();

    // スペースでゲームオーバー（今までの処理）
    bool nowPress = (CheckHitKey(KEY_INPUT_SPACE) != 0);
    if (nowPress && !mWasPressed) {
        mGoNext = true;
    }
    mWasPressed = nowPress;

    // =========================
    // Zキーで駒操作
    // =========================
    static bool zPrev = false;
    bool zNow = CheckHitKey(KEY_INPUT_Z);

    if (zNow && !zPrev)
    {
        int x = mCursor.x;
        int y = mCursor.y;

        if (!mSelected)
        {
            // 選択
            if (mBoard.board[y][x].type != EMPTY)
            {
                mSelected = true;
                selX = x;
                selY = y;
            }
        }
        else
        {
            // 移動（仮）
            mBoard.board[y][x] = mBoard.board[selY][selX];
            mBoard.board[selY][selX] = Piece();

            mSelected = false;
        }
    }

    zPrev = zNow;
}

void GameScene::Draw()
{
    mBoard.Draw();
    mCursor.Draw();

    DrawString(0, 0, "=== GAME ===", GetColor(100, 255, 100));
    DrawString(0, 460, "Z: Select / Move", GetColor(255, 255, 255));
    DrawString(0, 430, "SPACE: GameOver", GetColor(200, 200, 200));
}

SceneBase* GameScene::NextScene()
{
    if (mGoNext) return new GameOverScene();
    return nullptr;
}