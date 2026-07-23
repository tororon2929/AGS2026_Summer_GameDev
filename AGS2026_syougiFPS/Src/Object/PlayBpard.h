#pragma once

#include "Ou.h"
#include "../Common/Cell.h"

class CpuPlayer;

class PlayBpard
{
public:

    PlayBpard();
    ~PlayBpard();

    void Initialize();
    void Update();
    void Draw();

    bool MovePiece(int fromX, int fromY, int toX, int toY);

    Cell* GetCell(int x, int y);

    Cell* GetMouseOverCell();

    void ShowMovePoint(PieceBase* piece);

    // 移動経路の途中に他の駒がないかチェックする（あればfalse）
    bool IsPathClear(int fromX, int fromY, int toX, int toY);

private:
    CpuPlayer* m_cpuPlayer = nullptr;
    int mCpuThinkTimer = 0;
    int mPadCursorX = 2; // コントローラー用カーソルの初期X位置 (5マスの真ん中)
    int mPadCursorY = 3; // コントローラー用カーソルの初期Y位置 (7マスの真ん中)
    int mPadOldInput = 0; // 前フレームのボタン状態
    int m_handle;

    // 将棋盤を縦7マス、横5マスに修正 (mCells[y][x] -> yが7、xが5)
    Cell mCells[7][5];

    // =========================
    // Cellサイズ
    // =========================
    int mCellSizeX;
    int mCellSizeY;

    // =========================
    // 微調整用
    // =========================
    int mSelectCellX;
    int mSelectCellY;

    bool mEnterOld;

    Cell* mSelectCell;

    // クリック管理
    bool mMouseOld;

    PieceBase* mSelectPiece;

    bool mPlayerTurn;

    bool mGameEnd;

    int mBattleFromX;
    int mBattleFromY;

    int mBattleToX;
    int mBattleToY;

    int SetScreenPosX;
    int SetScreenPosY;

    int SetScreenPosX2;
    int SetScreenPosY2;

    int SetScreenPosX3;
    int SetScreenPosY3;

    int SetScreenPosX4;
    int SetScreenPosY4;

    int SetScreenPosX5;
    int SetScreenPosY5;

    int SetScreenPosY6;
    int SetScreenPosY7;

    int SetWorldPosY;

    int SetScreenPosZ;
    int SetScreenPosZ2;
    int SetScreenPosZ3;
    int SetScreenPosZ4;
    int SetScreenPosZ5;
    int SetScreenPosZ6;
    int SetScreenPosZ7;

};