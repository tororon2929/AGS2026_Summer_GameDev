#include <DxLib.h>
#include "../Object/PlayBpard.h"
#include "../Manager/ResourceManager.h"
#include "../Object/Ou.h"
#include "../Common/Cell.h"
#include "../Object/Gyoku.h"
#include "../Manager/SceneManager.h"
#include "../Object/Fu.h"
PlayBpard::PlayBpard()
    : m_handle(-1),
    mCellSizeX(159),
    mCellSizeY(172),
    mSelectCellX(0),
    mSelectCellY(0),
    mEnterOld(false),
    mSelectCell(nullptr),
    mMouseOld(false),
    mSelectPiece(nullptr),
    mPlayerTurn(true),
    mGameEnd(false),
    mBattleFromX(-1),
    mBattleFromY(-1),
    mBattleToX(-1),
    mBattleToY(-1),
    SetScreenPosX(373),
	SetScreenPosY(0),
    SetScreenPosX2(535),
    SetScreenPosY2(170),
    SetScreenPosX3(695),
    SetScreenPosY3(345),
    SetScreenPosX4(855),
    SetScreenPosY4(515),
    SetScreenPosX5(1016),
    SetScreenPosY5(690),
    SetWorldPosY(0)
{
}

PlayBpard::~PlayBpard()
{
}

void PlayBpard::Initialize()
{
    const Resource& res =
        ResourceManager::GetInstance().Load(ResourceManager::SRC::PlayBpard);

    m_handle = res.handleId_;

    // =========================
    // Cell初期化
    // =========================
    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            mCells[y][x].Init(x, y);
        }
    }

    // =========================
    // Cell画面座標
    // =========================

    // 1行目
    mCells[0][0].SetScreenPos(SetScreenPosX, SetScreenPosY);
    mCells[0][1].SetScreenPos(SetScreenPosX2, SetScreenPosY);
    mCells[0][2].SetScreenPos(SetScreenPosX3, SetScreenPosY);
    mCells[0][3].SetScreenPos(SetScreenPosX4, SetScreenPosY);
    mCells[0][4].SetScreenPos(SetScreenPosX5, SetScreenPosY);

    // 2行目
    mCells[1][0].SetScreenPos(SetScreenPosX, SetScreenPosY2);
    mCells[1][1].SetScreenPos(SetScreenPosX2, SetScreenPosY2);
    mCells[1][2].SetScreenPos(SetScreenPosX3, SetScreenPosY2);
    mCells[1][3].SetScreenPos(SetScreenPosX4, SetScreenPosY2);
    mCells[1][4].SetScreenPos(SetScreenPosX5, SetScreenPosY2);

    // 3行目
    mCells[2][0].SetScreenPos(SetScreenPosX, SetScreenPosY3);
    mCells[2][1].SetScreenPos(SetScreenPosX2, SetScreenPosY3);
    mCells[2][2].SetScreenPos(SetScreenPosX3, SetScreenPosY3);
    mCells[2][3].SetScreenPos(SetScreenPosX4, SetScreenPosY3);
    mCells[2][4].SetScreenPos(SetScreenPosX5, SetScreenPosY3);

    // 4行目
    mCells[3][0].SetScreenPos(SetScreenPosX, SetScreenPosY4);
    mCells[3][1].SetScreenPos(SetScreenPosX2, SetScreenPosY4);
    mCells[3][2].SetScreenPos(SetScreenPosX3, SetScreenPosY4);
    mCells[3][3].SetScreenPos(SetScreenPosX4, SetScreenPosY4);
    mCells[3][4].SetScreenPos(SetScreenPosX5, SetScreenPosY4);

    // 5行目
    mCells[4][0].SetScreenPos(SetScreenPosX, SetScreenPosY5);
    mCells[4][1].SetScreenPos(SetScreenPosX2, SetScreenPosY5);
    mCells[4][2].SetScreenPos(SetScreenPosX3, SetScreenPosY5);
    mCells[4][3].SetScreenPos(SetScreenPosX4, SetScreenPosY5);
    mCells[4][4].SetScreenPos(SetScreenPosX5, SetScreenPosY5);


   // =========================
  // Cellの3D座標
  // =========================

    mCells[0][0].SetWorldPos(VGet(-9.0f, SetWorldPosY, 9.25f));
    mCells[0][1].SetWorldPos(VGet(-4.5f, SetWorldPosY, 9.25f));
    mCells[0][2].SetWorldPos(VGet(0.0f, SetWorldPosY, 9.25f));
    mCells[0][3].SetWorldPos(VGet(4.5f, SetWorldPosY, 9.25f));
    mCells[0][4].SetWorldPos(VGet(9.0f, SetWorldPosY, 9.25f));

    // 2行目
    mCells[1][0].SetWorldPos(VGet(-9.0f, SetWorldPosY, 4.5f));
    mCells[1][1].SetWorldPos(VGet(-4.5f, SetWorldPosY, 4.5f));
    mCells[1][2].SetWorldPos(VGet(0.0f, SetWorldPosY, 4.5f));
    mCells[1][3].SetWorldPos(VGet(4.5f, SetWorldPosY,4.5f));
    mCells[1][4].SetWorldPos(VGet(9.0f, SetWorldPosY, 4.5f));


    // 3行目
    mCells[2][0].SetWorldPos(VGet(-9.0f, SetWorldPosY, 0.0f));
    mCells[2][1].SetWorldPos(VGet(-4.5f, SetWorldPosY, 0.0f));
    mCells[2][2].SetWorldPos(VGet(0.0f, SetWorldPosY, 0.0f));
    mCells[2][3].SetWorldPos(VGet(4.5f, SetWorldPosY, 0.0f));
    mCells[2][4].SetWorldPos(VGet(9.0f, SetWorldPosY, 0.0f));

    // 4行目
    mCells[3][0].SetWorldPos(VGet(-9.0f, SetWorldPosY, -4.5f));
    mCells[3][1].SetWorldPos(VGet(-4.5f, SetWorldPosY, -4.5f));
    mCells[3][2].SetWorldPos(VGet(0.0f, SetWorldPosY, -4.5f));
    mCells[3][3].SetWorldPos(VGet(4.5f, SetWorldPosY, -4.5f));
    mCells[3][4].SetWorldPos(VGet(9.0f, SetWorldPosY, -4.5f));

    // 5行目
    mCells[4][0].SetWorldPos(VGet(-9.0f, SetWorldPosY, -9.25f));
    mCells[4][1].SetWorldPos(VGet(-4.5f, SetWorldPosY, -9.25f));
    mCells[4][2].SetWorldPos(VGet(0.0f, SetWorldPosY, -9.25f));
    mCells[4][3].SetWorldPos(VGet(4.5f, SetWorldPosY, -9.25f));
    mCells[4][4].SetWorldPos(VGet(9.0f, SetWorldPosY, -9.25f));

    /*for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            float worldX =
                (x - 2) * 20.0f;

            float worldZ =
                (2 - y) * 20.0f;

            mCells[y][x].SetWorldPos(
                VGet(
                    worldX,
                    60.0f,
                    worldZ
                )
            );
        }
    }*/
    //王の設置
    Ou* ou = new Ou(2, 4, true);

    ou->SetWorldPos(
        mCells[4][2].GetWorldPos()
    );

    mCells[4][2].SetPiece(ou);

    //玉の設置
    Gyoku* gyoku = new Gyoku(2, 0, false);

    gyoku->SetWorldPos(
        mCells[0][2].GetWorldPos()
    );

    mCells[0][2].SetPiece(gyoku);

    // プレイヤー歩
    for (int x = 0; x <= 4; x++) // X座標 1, 2, 3 に配置
    {
        Fu* playerFu = new Fu(x, 3, true);
        playerFu->SetWorldPos(mCells[3][x].GetWorldPos());
        mCells[3][x].SetPiece(playerFu);
    }
   

    // 敵の歩兵（3枚に増やす）
     // =========================
    for (int x = 0; x <= 4; x++) // X座標 1, 2, 3 に配置
    {
        Fu* enemyFu = new Fu(x, 1, false);
        enemyFu->SetWorldPos(mCells[1][x].GetWorldPos());
        mCells[1][x].SetPiece(enemyFu);
    }
}

void PlayBpard::Update()
{
    // =========================
    // ゲーム終了
    // =========================

    if (mGameEnd)
    {
        return;
    }
  
    // =========================
    // 左クリック
    // =========================

    bool mouseNow =
        (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;

    if (mouseNow && !mMouseOld)
    {
        Cell* hoverCell =
            GetMouseOverCell();

        if (hoverCell)
        {
            // =========================
            // 全選択解除
            // =========================

            for (int y = 0; y < 5; y++)
            {
                for (int x = 0; x < 5; x++)
                {
                    mCells[y][x].SetSelected(false);
                }
            }

            // =========================
            // クリックマスの駒
            // =========================

            PieceBase* piece =
                hoverCell->GetPiece();

            // =========================
            // 既に駒選択中
            // =========================

            if (mSelectPiece)
            {
                // =========================
                // 移動可能マス
                // =========================

                if (hoverCell->IsMovePoint())
                {
                    bool result =
                        MovePiece(
                            mSelectPiece->GetX(),
                            mSelectPiece->GetY(),
                            hoverCell->GetX(),
                            hoverCell->GetY()
                        );

                    // =========================
                    // 移動成功
                    // =========================

                    if (result)
                    {
                        // ターン交代
                        mPlayerTurn =
                            !mPlayerTurn;
                    }

                    // 選択解除
                    mSelectPiece = nullptr;

                    // 青マス解除
                    ShowMovePoint(nullptr);
                }

                // =========================
                // 選択し直し
                // =========================

                else if (piece)
                {
                    // 自分ターンの駒のみ
                    if (piece->IsPlayer() ==
                        mPlayerTurn)
                    {
                        mSelectPiece = piece;

                        ShowMovePoint(piece);
                    }
                }
            }

            // =========================
            // 新規選択
            // =========================

            else if (piece)
            {
                // 自分ターンのみ
                if (piece->IsPlayer() ==
                    mPlayerTurn)
                {
                    mSelectPiece = piece;

                    ShowMovePoint(piece);
                }
            }

            // =========================
            // Cell選択
            // =========================

            hoverCell->SetSelected(true);

            mSelectCell = hoverCell;
        }
    }
  
    mMouseOld = mouseNow;
}

void PlayBpard::Draw()
{
    // =========================
     // 盤モデル描画
     // =========================
    if (m_handle != -1)
    {
        // 座標を (0.0f, 0.0f, 0.0f) に固定
        MV1SetPosition(m_handle, VGet(0.0f, 0.0f, 0.0f));

        // スケールは必要に応じて調整してください（現在は1倍）
        MV1SetScale(m_handle, VGet(1.0f, 1.0f, 1.0f));

        MV1DrawModel(m_handle);
    }

    // =========================
    // Cell描画
    // =========================
    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            Cell* cell = &mCells[y][x];

            int px = cell->GetScreenX();
            int py = cell->GetScreenY();

            // =========================
            // 通常マス
             // =========================
            DrawBox(
                px,
                py,
                px + mCellSizeX,
                py + mCellSizeY,
                GetColor(255, 0, 0),
                FALSE
            );

            // =========================
            // 選択状態
            // =========================
            if (cell->IsSelected())
            {
                DrawBox(
                    px,
                    py,
                    px + mCellSizeX,
                    py + mCellSizeY,
                    GetColor(0, 255, 0),
                    FALSE
                );
            }

            // =========================
            // 移動可能
            // =========================
            if (cell->IsMovePoint())
            {
                DrawBox(
                    px,
                    py,
                    px + mCellSizeX,
                    py + mCellSizeY,
                    GetColor(0, 0, 255),
                    FALSE
                );
            }

            // 中心点
            DrawCircle(
                px + mCellSizeX / 2,
                py + mCellSizeY / 2,
                5,
                GetColor(0, 255, 0),
                TRUE
            );

            // 駒描画
            if (cell->GetPiece())
            {

                cell->GetPiece()->Draw();

              
            }
        }
    }

    // =========================
    // 選択Cell表示
    // =========================
    Cell* selectCell = &mCells[mSelectCellY][mSelectCellX];

    DrawBox(
        selectCell->GetScreenX(),
        selectCell->GetScreenY(),
        selectCell->GetScreenX() + mCellSizeX,
        selectCell->GetScreenY() + mCellSizeY,
        GetColor(0, 255, 0),
        FALSE
    );

    // =========================
    // デバッグ表示
    // =========================
   /* DrawFormatString(
        20,
        20,
        GetColor(255, 255, 255),
        "Select Cell : [%d][%d]",
        mSelectCellX,
        mSelectCellY
    );

    DrawFormatString(
        20,
        50,
        GetColor(255, 255, 255),
        "Pos : (%d,%d)",
        selectCell->GetScreenX(),
        selectCell->GetScreenY()
    );*/
    Cell* hoverCell = GetMouseOverCell();

    if (hoverCell)
    {
        DrawBox(
            hoverCell->GetScreenX(),
            hoverCell->GetScreenY(),
            hoverCell->GetScreenX() + mCellSizeX,
            hoverCell->GetScreenY() + mCellSizeY,
            GetColor(255, 255, 0),
            FALSE
        );
    }


}

bool PlayBpard::MovePiece(
    int fromX,
    int fromY,
    int toX,
    int toY)
{
    Cell* fromCell =
        &mCells[fromY][fromX];

    Cell* toCell =
        &mCells[toY][toX];

    PieceBase* piece =
        fromCell->GetPiece();

    // =========================
    // 駒無し
    // =========================

    if (!piece)
    {
        return false;
    }

    // =========================
    // 移動可能判定
    // =========================

    if (!piece->CanMove(toX, toY))
    {
        return false;
    }

    // =========================
    // 移動先
    // =========================

    PieceBase* target =
        toCell->GetPiece();

    // =========================
    // 駒がある
    // =========================

    if (target)
    {
        // 味方禁止
        if (target->IsPlayer() ==
            piece->IsPlayer())
        {
            return false;
        }

        // =========================
        // FPS戦闘開始
        // =========================

        mBattleFromX = fromX;
        mBattleFromY = fromY;

        mBattleToX = toX;
        mBattleToY = toY;

        SceneManager::GetInstance().ChangeScene(
            SceneManager::SCENE_ID::FPS_BATTLE
        );

        return true;
    }

        //// =========================
        //// 王撃破
        //// =========================

        //if (target->GetType() ==
        //    PIECE_OU)
        //{
        //    mGameEnd = true;

        //    SceneManager::GetInstance().ChangeScene(
        //        SceneManager::SCENE_ID::RESULT
        //    );
        //}

        // =========================
        // 敵削除
        // =========================

      
    

    // =========================
    // 移動
    // =========================

    toCell->SetPiece(piece);

    fromCell->SetPiece(nullptr);

    // =========================
    // マス更新
    // =========================

    piece->SetPos(toX, toY);

    // =========================
    // ワールド座標更新
    // =========================

    piece->SetWorldPos(
        toCell->GetWorldPos()
    );

    return true;
}

Cell* PlayBpard::GetCell(int x, int y)
{
    return &mCells[y][x];
}
Cell* PlayBpard::GetMouseOverCell()
{
    int mouseX;
    int mouseY;

    GetMousePoint(&mouseX, &mouseY);

    Cell* nearestCell = nullptr;

    float nearestDistance = 999999.0f;

    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            Cell* cell = &mCells[y][x];

            // =========================
            // Cell中心座標
            // =========================
            int centerX =
                cell->GetScreenX() + mCellSizeX / 2;

            int centerY =
                cell->GetScreenY() + mCellSizeY / 2;

            // =========================
            // 距離計算
            // =========================
            float dx = (float)(mouseX - centerX);
            float dy = (float)(mouseY - centerY);

            float distance =
                dx * dx + dy * dy;

            // =========================
            // 最短更新
            // =========================
            if (distance < nearestDistance)
            {
                nearestDistance = distance;
                nearestCell = cell;
            }
        }
    }

    return nearestCell;
}

void PlayBpard::ShowMovePoint(PieceBase* piece)
{
    // =========================
    // 全解除
    // =========================

    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            mCells[y][x].SetMovePoint(false);
        }
    }

    // =========================
    // 駒無し
    // =========================

    if (!piece)
    {
        return;
    }

    // =========================
    // 全マス判定
    // =========================

    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            // 移動不可
            if (!piece->CanMove(x, y))
            {
                continue;
            }

            // 自分自身禁止
            if (x == piece->GetX() &&
                y == piece->GetY())
            {
                continue;
            }

            PieceBase* target =
                mCells[y][x].GetPiece();

            // =========================
            // 味方禁止
            // =========================

            if (target)
            {
                if (target->IsPlayer() ==
                    piece->IsPlayer())
                {
                    continue;
                }
            }

            // =========================
            // 移動可能
            // =========================

            mCells[y][x].SetMovePoint(true);
        }
    }
}