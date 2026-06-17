#include <DxLib.h>
#include "../Object/PlayBpard.h"
#include "../Manager/ResourceManager.h"
#include "../Object/Ou.h"
#include "../Common/Cell.h"
#include "../Object/Gyoku.h"
#include "../Manager/SceneManager.h"
#include "../Object/Fu.h"
#include "../Object/Hisha.h"
#include "../Object/Kaku.h"
#include "../Object/Kin.h"
#include "../Object/Gin.h"
#include "../Effect/EffectManager.h"
#include "../Effect/CutInEffect.h"

PlayBpard::PlayBpard()
    : m_handle(-1),
    mCellSizeX(116),
    mCellSizeY(123),
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
    SetScreenPosX(485),
    SetScreenPosY(0),
    SetScreenPosX2(600),
    SetScreenPosY2(120),
    SetScreenPosX3(715),
    SetScreenPosY3(245),
    SetScreenPosX4(830),
    SetScreenPosY4(370),
    SetScreenPosX5(950),
    SetScreenPosY5(495),
    SetScreenPosY6(620),
    SetScreenPosY7(745),
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
    // Cell初期化 (縦7 x 横5)
    // =========================
    for (int y = 0; y < 7; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            mCells[y][x].Init(x, y);
        }
    }

    // =========================
    // Cell画面座標 (変更なし)
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

    // 6行目
    mCells[5][0].SetScreenPos(SetScreenPosX, SetScreenPosY6);
    mCells[5][1].SetScreenPos(SetScreenPosX2, SetScreenPosY6);
    mCells[5][2].SetScreenPos(SetScreenPosX3, SetScreenPosY6);
    mCells[5][3].SetScreenPos(SetScreenPosX4, SetScreenPosY6);
    mCells[5][4].SetScreenPos(SetScreenPosX5, SetScreenPosY6);

    // 7行目
    mCells[6][0].SetScreenPos(SetScreenPosX, SetScreenPosY7);
    mCells[6][1].SetScreenPos(SetScreenPosX2, SetScreenPosY7);
    mCells[6][2].SetScreenPos(SetScreenPosX3, SetScreenPosY7);
    mCells[6][3].SetScreenPos(SetScreenPosX4, SetScreenPosY7);
    mCells[6][4].SetScreenPos(SetScreenPosX5, SetScreenPosY7);

    // =========================
    // Cellの3D座標 (★ご要望通り変更なし)
    // =========================

    // 1行目
    mCells[0][0].SetWorldPos(VGet(-9.0f, SetWorldPosY, 14.0f));
    mCells[0][1].SetWorldPos(VGet(-4.5f, SetWorldPosY, 14.0f));
    mCells[0][2].SetWorldPos(VGet(0.0f, SetWorldPosY, 14.0f));
    mCells[0][3].SetWorldPos(VGet(4.5f, SetWorldPosY, 14.0f));
    mCells[0][4].SetWorldPos(VGet(9.0f, SetWorldPosY, 14.0f));

    // 2行目
    mCells[1][0].SetWorldPos(VGet(-9.0f, SetWorldPosY, 9.25f));
    mCells[1][1].SetWorldPos(VGet(-4.5f, SetWorldPosY, 9.25f));
    mCells[1][2].SetWorldPos(VGet(0.0f, SetWorldPosY, 9.25f));
    mCells[1][3].SetWorldPos(VGet(4.5f, SetWorldPosY, 9.25f));
    mCells[1][4].SetWorldPos(VGet(9.0f, SetWorldPosY, 9.25f));

    // 3行目
    mCells[2][0].SetWorldPos(VGet(-9.0f, SetWorldPosY, 4.5f));
    mCells[2][1].SetWorldPos(VGet(-4.5f, SetWorldPosY, 4.5f));
    mCells[2][2].SetWorldPos(VGet(0.0f, SetWorldPosY, 4.5f));
    mCells[2][3].SetWorldPos(VGet(4.5f, SetWorldPosY, 4.5f));
    mCells[2][4].SetWorldPos(VGet(9.0f, SetWorldPosY, 4.5f));

    // 4行目
    mCells[3][0].SetWorldPos(VGet(-9.0f, SetWorldPosY, 0.0f));
    mCells[3][1].SetWorldPos(VGet(-4.5f, SetWorldPosY, 0.0f));
    mCells[3][2].SetWorldPos(VGet(0.0f, SetWorldPosY, 0.0f));
    mCells[3][3].SetWorldPos(VGet(4.5f, SetWorldPosY, 0.0f));
    mCells[3][4].SetWorldPos(VGet(9.0f, SetWorldPosY, 0.0f));

    // 5行目
    mCells[4][0].SetWorldPos(VGet(-9.0f, SetWorldPosY, -4.5f));
    mCells[4][1].SetWorldPos(VGet(-4.5f, SetWorldPosY, -4.5f));
    mCells[4][2].SetWorldPos(VGet(0.0f, SetWorldPosY, -4.5f));
    mCells[4][3].SetWorldPos(VGet(4.5f, SetWorldPosY, -4.5f));
    mCells[4][4].SetWorldPos(VGet(9.0f, SetWorldPosY, -4.5f));

    // 6行目
    mCells[5][0].SetWorldPos(VGet(-9.0f, SetWorldPosY, -9.25f));
    mCells[5][1].SetWorldPos(VGet(-4.5f, SetWorldPosY, -9.25f));
    mCells[5][2].SetWorldPos(VGet(0.0f, SetWorldPosY, -9.25f));
    mCells[5][3].SetWorldPos(VGet(4.5f, SetWorldPosY, -9.25f));
    mCells[5][4].SetWorldPos(VGet(9.0f, SetWorldPosY, -9.25f));

    // 7行目
    mCells[6][0].SetWorldPos(VGet(-9.0f, SetWorldPosY, -14.0f));
    mCells[6][1].SetWorldPos(VGet(-4.5f, SetWorldPosY, -14.0f));
    mCells[6][2].SetWorldPos(VGet(0.0f, SetWorldPosY, -14.0f));
    mCells[6][3].SetWorldPos(VGet(4.5f, SetWorldPosY, -14.0f));
    mCells[6][4].SetWorldPos(VGet(9.0f, SetWorldPosY, -14.0f));

    // 王の設置 (変更なし)
    Ou* ou = new Ou(2, 6, true);
    ou->SetWorldPos(mCells[6][2].GetWorldPos());
    mCells[6][2].SetPiece(ou);

    // 玉の設置 (変更なし)
    Gyoku* gyoku = new Gyoku(2, 0, false);
    gyoku->SetWorldPos(mCells[0][2].GetWorldPos());
    mCells[0][2].SetPiece(gyoku);

    // プレイヤー歩 (横5列分ループ)
    for (int x = 0; x <= 4; x++)
    {
        Fu* playerFu = new Fu(x, 5, true);
        playerFu->SetWorldPos(mCells[5][x].GetWorldPos());
        mCells[5][x].SetPiece(playerFu);
    }

    // 敵の歩兵 (横5列分ループ)
    for (int x = 0; x <= 4; x++)
    {
        Fu* enemyFu = new Fu(x, 1, false);
        enemyFu->SetWorldPos(mCells[1][x].GetWorldPos());
        mCells[1][x].SetPiece(enemyFu);
    }

    //飛車の設置
    Hisha* hisha = new Hisha(0, 6, true);
    hisha->SetWorldPos(mCells[6][0].GetWorldPos());
    mCells[6][0].SetPiece(hisha);

	//敵の飛車の設置
    Hisha* enemyhisha = new Hisha(0, 0, false);
    enemyhisha->SetWorldPos(mCells[0][0].GetWorldPos());
    mCells[0][0].SetPiece(enemyhisha);

	//角の設置
    Kaku* kaku = new Kaku(4, 6, true);
    kaku->SetWorldPos(mCells[6][4].GetWorldPos());
	mCells[6][4].SetPiece(kaku);

	//敵の角の設置
    Kaku* enemykaku = new Kaku(4, 0, false);
	enemykaku->SetWorldPos(mCells[0][4].GetWorldPos());
    mCells[0][4].SetPiece(enemykaku);

	//金の設置
    Kin* kin = new Kin(3, 6, true);
    kin->SetWorldPos(mCells[6][3].GetWorldPos());
    mCells[6][3].SetPiece(kin);

	//敵の金の設置
    Kin* enemykin = new Kin(3, 0, false);
    enemykin->SetWorldPos(mCells[0][3].GetWorldPos());
	mCells[0][3].SetPiece(enemykin);

	//  銀の設置（プレイヤー側）
    Gin* gin = new Gin(1, 6, true);
    gin->SetWorldPos(mCells[6][1].GetWorldPos());
    mCells[6][1].SetPiece(gin);

	//  銀の設置（敵側）
    Gin* enemygin = new Gin(1, 0, false);
	enemygin->SetWorldPos(mCells[0][1].GetWorldPos());
	mCells[0][1].SetPiece(enemygin);

    const Resource& startRes = ResourceManager::GetInstance().Load(ResourceManager::SRC::Myturn);
    EffectManager::GetInstance().AddEffect(
        std::make_unique<CutInEffect>(startRes.handleId_, 1.5f)
    );
}

void PlayBpard::Update()
{
    if (mGameEnd)
    {
        return;
    }

    //// ==========================================
    //// デバッグ操作（キーボードでマスを選択・数値を微調整）
    //// ==========================================

    //// 1. マス自体の選択変更（SHIFTキーを押しながら矢印キー）
    //if (CheckHitKey(KEY_INPUT_LSHIFT) || CheckHitKey(KEY_INPUT_RSHIFT))
    //{
    //    // 押しっぱなしで高速移動しすぎないよう、簡易的な入力制御（1フレーム前の状態など）を入れるとより快適になりますが、
    //    // 今回はシンプルに、キーが押されたら選択インデックスを更新します。
    //    // ※長押しすると勢いよく動くのでトントンと叩くように押してください。
    //    if (CheckHitKey(KEY_INPUT_RIGHT)) { mSelectCellX = (mSelectCellX + 1) % 5; }
    //    if (CheckHitKey(KEY_INPUT_LEFT)) { mSelectCellX = (mSelectCellX - 1 + 5) % 5; }
    //    if (CheckHitKey(KEY_INPUT_DOWN)) { mSelectCellY = (mSelectCellY + 1) % 7; }
    //    if (CheckHitKey(KEY_INPUT_UP)) { mSelectCellY = (mSelectCellY - 1 + 7) % 7; }

    //    // 選択されたインデックスからポインタを更新
    //    mSelectCell = &mCells[mSelectCellY][mSelectCellX];

    //    // 描画用の選択状態（緑枠）を同期
    //    for (int y = 0; y < 7; y++)
    //    {
    //        for (int x = 0; x < 5; x++)
    //        {
    //            mCells[y][x].SetSelected(false);
    //        }
    //    }
    //    mSelectCell->SetSelected(true);
    //}
    //// 2. マスサイズの変更（Lキーを押しながら矢印キー）
    //else if (CheckHitKey(KEY_INPUT_L))
    //{
    //    if (CheckHitKey(KEY_INPUT_RIGHT)) mCellSizeX++;
    //    if (CheckHitKey(KEY_INPUT_LEFT))  mCellSizeX--;
    //    if (CheckHitKey(KEY_INPUT_DOWN))  mCellSizeY++;
    //    if (CheckHitKey(KEY_INPUT_UP))    mCellSizeY--;
    //}
    //// 3. 現在選択中のマスの画面座標を変更（矢印キーのみ）
    //else if (mSelectCell)
    //{
    //    int currentX = mSelectCell->GetScreenX();
    //    int currentY = mSelectCell->GetScreenY();

    //    if (CheckHitKey(KEY_INPUT_RIGHT)) currentX++;
    //    if (CheckHitKey(KEY_INPUT_LEFT))  currentX--;
    //    if (CheckHitKey(KEY_INPUT_DOWN))  currentY++;
    //    if (CheckHitKey(KEY_INPUT_UP))    currentY--;

    //    mSelectCell->SetScreenPos(currentX, currentY);
    //}
    // ==========================================
    // エフェクトマネージャーの更新 (1秒あたりの経過時間を渡す。1フレーム固定なら 1.0f/60.0f など)
    // ==========================================
    EffectManager::GetInstance().Update(1.0f / 60.0f);

    // カットイン演出中の場合は、以降の操作（マウス入力など）を受け付けない
    if (EffectManager::GetInstance().IsCutInActive())
    {
        // マウスの旧状態だけ同期して、プレイヤーが行動できないようにする
        mMouseOld = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;
        return;
    }
    // ==========================================
    // 通常のマウス選択処理（既存のもの）
    // ==========================================
    bool mouseNow = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;

    if (mouseNow && !mMouseOld)
    {
        Cell* hoverCell = GetMouseOverCell();

        if (hoverCell)
        {
            for (int y = 0; y < 7; y++)
            {
                for (int x = 0; x < 5; x++)
                {
                    mCells[y][x].SetSelected(false);
                }
            }

            PieceBase* piece = hoverCell->GetPiece();

            if (mSelectPiece)
            {
                if (hoverCell->IsMovePoint())
                {
                    bool result = MovePiece(
                        mSelectPiece->GetX(),
                        mSelectPiece->GetY(),
                        hoverCell->GetX(),
                        hoverCell->GetY()
                    );

                    if (result)
                    {
                        // ターンを反転
                        mPlayerTurn = !mPlayerTurn;

                        // 切り替わった「後の」ターンに応じたカットインを表示
                        ResourceManager::SRC srcType = mPlayerTurn ? ResourceManager::SRC::Myturn : ResourceManager::SRC::Enemyturn;
                        const Resource& turnRes = ResourceManager::GetInstance().Load(srcType);

                        // 1.5秒間（Updateの加算速度に合わせて調整してください）表示されるカットインを登録
                        EffectManager::GetInstance().AddEffect(
                            std::make_unique<CutInEffect>(turnRes.handleId_, 1.5f)
                        );
                    }
                    mSelectPiece = nullptr;
                    ShowMovePoint(nullptr);
                }
                else if (piece)
                {
                    if (piece->IsPlayer() == mPlayerTurn)
                    {
                        mSelectPiece = piece;
                        ShowMovePoint(piece);
                    }
                }
            }
            else if (piece)
            {
                if (piece->IsPlayer() == mPlayerTurn)
                {
                    mSelectPiece = piece;
                    ShowMovePoint(piece);
                }
            }

            hoverCell->SetSelected(true);
            mSelectCell = hoverCell;

            // マウスクリック時にインデックスを同期
            mSelectCellX = hoverCell->GetX();
            mSelectCellY = hoverCell->GetY();
        }
    }

    mMouseOld = mouseNow;
}
void PlayBpard::Draw()
{
    if (m_handle != -1)
    {
        MV1SetPosition(m_handle, VGet(0.0f, 0.0f, 0.0f));
        MV1SetScale(m_handle, VGet(1.0f, 1.0f, 1.0f));
        MV1DrawModel(m_handle);
    }

    // グリッド線とCell描画ループを 縦7 x 横5 に修正
    for (int y = 0; y < 7; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            Cell* cell = &mCells[y][x];

            int px = cell->GetScreenX();
            int py = cell->GetScreenY();

            //DrawBox(px, py, px + mCellSizeX, py + mCellSizeY, GetColor(255, 0, 0), FALSE);

            if (cell->IsSelected())
            {
                DrawBox(px, py, px + mCellSizeX, py + mCellSizeY, GetColor(0, 255, 0), FALSE);
            }

            if (cell->IsMovePoint())
            {
                DrawBox(px, py, px + mCellSizeX, py + mCellSizeY, GetColor(0, 0, 255), FALSE);
            }

           /* DrawCircle(px + mCellSizeX / 2, py + mCellSizeY / 2, 5, GetColor(0, 255, 0), TRUE);*/

            if (cell->GetPiece())
            {
                cell->GetPiece()->Draw();
            }

        }
        
    }

    Cell* selectCell = &mCells[mSelectCellY][mSelectCellX];

    DrawBox(
        selectCell->GetScreenX(),
        selectCell->GetScreenY(),
        selectCell->GetScreenX() + mCellSizeX,
        selectCell->GetScreenY() + mCellSizeY,
        GetColor(0, 255, 0),
        FALSE
    );

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
    // ==========================================
    // エフェクト（カットイン）の描画を一番手前で行う
    // ==========================================
    EffectManager::GetInstance().Draw();
}

bool PlayBpard::MovePiece(int fromX, int fromY, int toX, int toY)
{
    Cell* fromCell = &mCells[fromY][fromX];
    Cell* toCell = &mCells[toY][toX];
    PieceBase* piece = fromCell->GetPiece();

    if (!piece) return false;
    if (!piece->CanMove(toX, toY)) return false;

    // ★追加: 移動経路の途中に駒がある場合は移動できない
        if (!IsPathClear(fromX, fromY, toX, toY)) return false;

    PieceBase* target = toCell->GetPiece();

    if (target)
    {
        if (target->IsPlayer() == piece->IsPlayer())
        {
            return false;
        }

        if (target->GetType() == PIECE_OU || target->GetType() == PIECE_GYOKU)
        {
            mGameEnd = true;
            delete target;
            toCell->SetPiece(nullptr);

            SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::RESULT);
        }
        else
        {
            delete target;
            toCell->SetPiece(nullptr);
        }
    }

    toCell->SetPiece(piece);
    fromCell->SetPiece(nullptr);

    piece->SetPos(toX, toY);
    piece->SetWorldPos(toCell->GetWorldPos());

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

    // マウス判定ループを 縦7 x 横5 に修正
    for (int y = 0; y < 7; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            Cell* cell = &mCells[y][x];

            int centerX = cell->GetScreenX() + mCellSizeX / 2;
            int centerY = cell->GetScreenY() + mCellSizeY / 2;

            float dx = (float)(mouseX - centerX);
            float dy = (float)(mouseY - centerY);

            float distance = dx * dx + dy * dy;

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
    // 移動可能判定の全解除ループを 縦7 x 横5 に修正
    for (int y = 0; y < 7; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            mCells[y][x].SetMovePoint(false);
        }
    }

    if (!piece)
    {
        return;
    }

    // 全マス判定ループを 縦7 x 横5 に修正
    for (int y = 0; y < 7; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            if (!piece->CanMove(x, y))
            {
                continue;
            }

            if (x == piece->GetX() && y == piece->GetY())
            {
                continue;
            }
            // ★追加: 駒の動きとしては届くが、途中に遮る駒がある場合はスキップ
            if (!IsPathClear(piece->GetX(), piece->GetY(), x, y))
            {
                continue;
            }
            PieceBase* target = mCells[y][x].GetPiece();

            if (target)
            {
                if (target->IsPlayer() == piece->IsPlayer())
                {
                    continue;
                }
            }

            mCells[y][x].SetMovePoint(true);
        }
    }
}

bool PlayBpard::IsPathClear(int fromX, int fromY, int toX, int toY)
{
    int dx = toX - fromX;
    int dy = toY - fromY;

    // 1ステップあたりの進む方向（-1, 0, 1 のいずれか）を計算
    int stepX = (dx > 0) ? 1 : ((dx < 0) ? -1 : 0);
    int stepY = (dy > 0) ? 1 : ((dy < 0) ? -1 : 0);

    // 現在のチェック対象座標を移動元にセット
    int checkX = fromX + stepX;
    int checkY = fromY + stepY;

    // 移動先の直前のマスまでループで回す
    while (checkX != toX || checkY != toY)
    {
        // 念のための境界チェック
        if (checkX < 0 || checkX >= 5 || checkY < 0 || checkY >= 7) {
            break;
        }

        // 途中のマスに駒が存在していれば、経路が塞がれていると判断
        if (mCells[checkY][checkX].GetPiece() != nullptr)
        {
            return false; // 飛び越し不可
        }

        // 次のマスへ進める
        checkX += stepX;
        checkY += stepY;
    }

    return true; // 途中に駒は無かった
}