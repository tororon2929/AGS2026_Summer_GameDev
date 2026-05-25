#pragma once

#include "Ou.h"
#include "../Common/Cell.h"

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
    

private:

    int m_handle;

    // 将棋盤
    Cell mCells[5][5];

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
};