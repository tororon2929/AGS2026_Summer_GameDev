#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Object/PlayBpard.h"
#include "../Manager/ResourceManager.h"
#include "../Object/Ou.h"
#include "../Common/Cell.h"
#include "../Object/Gyoku.h"
#include "../Object/Fu.h"
#include "../Object/Hisha.h"
#include "../Object/Kaku.h"
#include "../Object/Kin.h"
#include "../Object/Gin.h"
#include "../Effect/EffectManager.h"
#include "../Effect/CutInEffect.h"
#include"../Manager/InputManager.h"
#include "CpuPlayer.h"
#include "../Manager/SoundManager.h"

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
    SetWorldPosY(0),
    SetScreenPosZ(14.0f),
    SetScreenPosZ2(9.25f),
    SetScreenPosZ3(4.5f),
    SetScreenPosZ4(0.0f),
    SetScreenPosZ5(-4.5f),
    SetScreenPosZ6(-9.25f),
    SetScreenPosZ7(-14.0f)
{
}

PlayBpard::~PlayBpard()
{
    delete m_cpuPlayer;
}

void PlayBpard::Initialize()
{
    const Resource& res =
        ResourceManager::GetInstance().Load(ResourceManager::SRC::PlayBpard);

    m_handle = res.handleId_;
    // ========================================================
     // ★難易度の分岐処理（必ず関数の内側に記述します）
     // ========================================================
    int selectedLevel = SceneManager::GetInstance().GetCpuLevel();
    CpuPlayer::Level cpuLevel = CpuPlayer::Level::Easy;

    if (selectedLevel == 1)
    {
        cpuLevel = CpuPlayer::Level::Normal;
    }
    else if (selectedLevel == 2)
    {
        cpuLevel = CpuPlayer::Level::Hard;
    }

    // 選択された難易度でAIを生成
    m_cpuPlayer = new CpuPlayer(cpuLevel);
    mCpuThinkTimer = 0;

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
    mCells[0][0].SetWorldPos(VGet(-9.0f, SetWorldPosY, SetScreenPosZ));
    mCells[0][1].SetWorldPos(VGet(-4.5f, SetWorldPosY, SetScreenPosZ));
    mCells[0][2].SetWorldPos(VGet(0.0f, SetWorldPosY, SetScreenPosZ));
    mCells[0][3].SetWorldPos(VGet(4.5f, SetWorldPosY, SetScreenPosZ));
    mCells[0][4].SetWorldPos(VGet(9.0f, SetWorldPosY, SetScreenPosZ));

    // 2行目
    mCells[1][0].SetWorldPos(VGet(-9.0f, SetWorldPosY, SetScreenPosZ2));
    mCells[1][1].SetWorldPos(VGet(-4.5f, SetWorldPosY, SetScreenPosZ2));
    mCells[1][2].SetWorldPos(VGet(0.0f, SetWorldPosY, SetScreenPosZ2));
    mCells[1][3].SetWorldPos(VGet(4.5f, SetWorldPosY, SetScreenPosZ2));
    mCells[1][4].SetWorldPos(VGet(9.0f, SetWorldPosY, SetScreenPosZ2));

    // 3行目
    mCells[2][0].SetWorldPos(VGet(-9.0f, SetWorldPosY, SetScreenPosZ3));
    mCells[2][1].SetWorldPos(VGet(-4.5f, SetWorldPosY, SetScreenPosZ3));
    mCells[2][2].SetWorldPos(VGet(0.0f, SetWorldPosY, SetScreenPosZ3));
    mCells[2][3].SetWorldPos(VGet(4.5f, SetWorldPosY, SetScreenPosZ3));
    mCells[2][4].SetWorldPos(VGet(9.0f, SetWorldPosY, SetScreenPosZ3));

    // 4行目
    mCells[3][0].SetWorldPos(VGet(-9.0f, SetWorldPosY, SetScreenPosZ4));
    mCells[3][1].SetWorldPos(VGet(-4.5f, SetWorldPosY, SetScreenPosZ4));
    mCells[3][2].SetWorldPos(VGet(0.0f, SetWorldPosY, SetScreenPosZ4));
    mCells[3][3].SetWorldPos(VGet(4.5f, SetWorldPosY, SetScreenPosZ4));
    mCells[3][4].SetWorldPos(VGet(9.0f, SetWorldPosY, SetScreenPosZ4));

    // 5行目
    mCells[4][0].SetWorldPos(VGet(-9.0f, SetWorldPosY, SetScreenPosZ5));
    mCells[4][1].SetWorldPos(VGet(-4.5f, SetWorldPosY, SetScreenPosZ5));
    mCells[4][2].SetWorldPos(VGet(0.0f, SetWorldPosY, SetScreenPosZ5));
    mCells[4][3].SetWorldPos(VGet(4.5f, SetWorldPosY, SetScreenPosZ5));
    mCells[4][4].SetWorldPos(VGet(9.0f, SetWorldPosY, SetScreenPosZ5));

    // 6行目
    mCells[5][0].SetWorldPos(VGet(-9.0f, SetWorldPosY, SetScreenPosZ6));
    mCells[5][1].SetWorldPos(VGet(-4.5f, SetWorldPosY, SetScreenPosZ6));
    mCells[5][2].SetWorldPos(VGet(0.0f, SetWorldPosY, SetScreenPosZ6));
    mCells[5][3].SetWorldPos(VGet(4.5f, SetWorldPosY, SetScreenPosZ6));
    mCells[5][4].SetWorldPos(VGet(9.0f, SetWorldPosY, SetScreenPosZ6));

    // 7行目
    mCells[6][0].SetWorldPos(VGet(-9.0f, SetWorldPosY, SetScreenPosZ7));
    mCells[6][1].SetWorldPos(VGet(-4.5f, SetWorldPosY, SetScreenPosZ7));
    mCells[6][2].SetWorldPos(VGet(0.0f, SetWorldPosY, SetScreenPosZ7));
    mCells[6][3].SetWorldPos(VGet(4.5f, SetWorldPosY, SetScreenPosZ7));
    mCells[6][4].SetWorldPos(VGet(9.0f, SetWorldPosY, SetScreenPosZ7));

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
    Kin* enemykin = new Kin(1, 0, false);
    enemykin->SetWorldPos(mCells[0][1].GetWorldPos());
	mCells[0][1].SetPiece(enemykin);

	//  銀の設置（プレイヤー側）
    Gin* gin = new Gin(1, 6, true);
    gin->SetWorldPos(mCells[6][1].GetWorldPos());
    mCells[6][1].SetPiece(gin);

	//  銀の設置（敵側）
    Gin* enemygin = new Gin(3, 0, false);
	enemygin->SetWorldPos(mCells[0][3].GetWorldPos());
	mCells[0][3].SetPiece(enemygin);

    const Resource& startRes = ResourceManager::GetInstance().Load(ResourceManager::SRC::Myturn);
    EffectManager::GetInstance().AddEffect(
        std::make_unique<CutInEffect>(startRes.handleId_, 1.5f)
    );

    SoundManager::GetInstance().Init();
    

}

void PlayBpard::Update()
{
    if (mGameEnd) return;

    if (mPlayerTurn) {
        // --------------------------------------------
        // 現在実装されている「人間のマウス・パッド操作」の処理
        // --------------------------------------------
        InputManager& inp = InputManager::GetInstance();
        // -------------------------------------------------------------
        // 1. 各種入力状態の取得 (コントローラー & マウス)
        // -------------------------------------------------------------
        int padInput = GetJoypadInputState(DX_INPUT_PAD1);
        int padTrg = padInput & ~mPadOldInput;
        mPadOldInput = padInput; // 状態を保存

        // マウスの左クリック状態を取得
        int mouseInput = GetMouseInput();
        bool mouseClickTrg = (mouseInput & MOUSE_INPUT_LEFT) && !mMouseOld;
        mMouseOld = (mouseInput & MOUSE_INPUT_LEFT); // 状態を保存

        // キーボードの矢印キーの単発押し判定 (デバッグ用)
        static bool keyUpOld = false, keyDownOld = false, keyLeftOld = false, keyRightOld = false;
        bool keyUp = CheckHitKey(KEY_INPUT_UP);
        bool keyDown = CheckHitKey(KEY_INPUT_DOWN);
        bool keyLeft = CheckHitKey(KEY_INPUT_LEFT);
        bool keyRight = CheckHitKey(KEY_INPUT_RIGHT);

        // -------------------------------------------------------------
        // 2. 枠（カーソル）の移動処理
        // -------------------------------------------------------------
        // コントローラーの十字キー/スティック、またはキーボードの矢印キーで枠だけを動かす
        if ((padTrg & PAD_INPUT_UP) || (keyUp && !keyUpOld)) { mPadCursorY = (mPadCursorY > 0) ? mPadCursorY - 1 : 0; }
        if ((padTrg & PAD_INPUT_DOWN) || (keyDown && !keyDownOld)) { mPadCursorY = (mPadCursorY < 6) ? mPadCursorY + 1 : 6; }
        if ((padTrg & PAD_INPUT_LEFT) || (keyLeft && !keyLeftOld)) { mPadCursorX = (mPadCursorX > 0) ? mPadCursorX - 1 : 0; }
        if ((padTrg & PAD_INPUT_RIGHT) || (keyRight && !keyRightOld)) { mPadCursorX = (mPadCursorX < 4) ? mPadCursorX + 1 : 4; }

        keyUpOld = keyUp; keyDownOld = keyDown; keyLeftOld = keyLeft; keyRightOld = keyRight;

        // マウスがどこかのマスの上に乗っている場合は、枠をマウス位置に同期する
        Cell* hoverCell = GetMouseOverCell();
        if (hoverCell)
        {
            for (int y = 0; y < 7; y++)
            {
                for (int x = 0; x < 5; x++)
                {
                    if (&mCells[y][x] == hoverCell)
                    {
                        mPadCursorX = x;
                        mPadCursorY = y;
                    }
                }
            }
        }

        // -------------------------------------------------------------
        // 3. 決定アクション（Aボタン または マウス左クリックされた瞬間）
        // -------------------------------------------------------------
        // 💡 ここがポイント：枠がどこにあろうと、Aボタンか左クリックを押さない限り以下の選択処理は走らない
        bool isSelectAction = (padTrg & PAD_INPUT_1) || mouseClickTrg;

        if (isSelectAction)
        {
            // 現在、緑枠（カーソル）が合っているマスを対象にする
            Cell* targetCell = &mCells[mPadCursorY][mPadCursorX];

            if (mSelectPiece == nullptr)
            {
                // 【フェーズ1: 自分の駒を選択する】
                PieceBase* piece = targetCell->GetPiece();
                if (piece && piece->IsPlayer() == mPlayerTurn)
                {
                    mSelectPiece = piece;
                    ShowMovePoint(mSelectPiece); // 移動可能マスを青くハイライト
                }

            }
            else
            {
                // 【フェーズ2: すでに駒を選んでいる状態で、移動先を選ぶ】
                if (targetCell->IsMovePoint())
                {
                    int fromX = mSelectPiece->GetX();
                    int fromY = mSelectPiece->GetY();

                    // 駒を移動させる
                    if (MovePiece(fromX, fromY, mPadCursorX, mPadCursorY))
                    {
                        SoundManager::GetInstance().PlaySE(SoundManager::SE::Shot1);
                        mSelectPiece = nullptr;
                        // 青いハイライトを消す
                        for (int y = 0; y < 7; y++) {
                            for (int x = 0; x < 5; x++) mCells[y][x].SetMovePoint(false);
                        }
                        mPlayerTurn = !mPlayerTurn; // ターン交代
                    }
                }
                else
                {
                    // 移動先ではない場所でボタンが押された場合
                    PieceBase* piece = targetCell->GetPiece();
                    if (piece && piece->IsPlayer() == mPlayerTurn)
                    {
                        // 別の自分の駒だったら、その駒を選び直す
                        mSelectPiece = piece;
                        for (int y = 0; y < 7; y++) {
                            for (int x = 0; x < 5; x++) mCells[y][x].SetMovePoint(false);
                        }
                        ShowMovePoint(mSelectPiece);
                    }
                    else
                    {
                        // 空白マスなどなら選択をキャンセルする
                        mSelectPiece = nullptr;
                        for (int y = 0; y < 7; y++) {
                            for (int x = 0; x < 5; x++) mCells[y][x].SetMovePoint(false);
                        }
                    }
                }
            }
        }
        // プレイヤーのターン中は、念のためCPUタイマーを0にリセットしておく
        mCpuThinkTimer = 0;
    }

    else {
        // --------------------------------------------
         // CPUのターン（タイマーによるウェイト処理）
         // --------------------------------------------
        mCpuThinkTimer++;

        // 60フレーム（約1秒）経過したら、CPUが手を実行する
        // ※「少し早めがいい」場合は 30 や 40 に調整してください
        if (mCpuThinkTimer >= 60)
        {
            if (m_cpuPlayer)
            {
                SoundManager::GetInstance().PlaySE(SoundManager::SE::Shot1);
                MoveCommand cmd = m_cpuPlayer->Think(this);
                
                // 有効な手が返ってきたら実行
                if (cmd.fromX != -1)
                {
                    if (MovePiece(cmd.fromX, cmd.fromY, cmd.toX, cmd.toY))
                    {
                        mPlayerTurn = true;    // 移動成功したらプレイヤーのターンに戻す
                        mCpuThinkTimer = 0;    // タイマーをリセット

                    }
                }
            }
        }
    }

    
}
	
void PlayBpard::Draw()
{
    if (m_handle != -1)
    {
        MV1SetPosition(m_handle, VGet(0.0f, 0.0f, 0.0f));
        MV1SetScale(m_handle, VGet(1.0f, 1.0f, 1.0f));
        MV1DrawModel(m_handle);
    }
    // 現在のターンに応じたリソースを取得
    ResourceManager::SRC turnSrc = mPlayerTurn ? ResourceManager::SRC::Myturn : ResourceManager::SRC::Enemyturn;
    const Resource& turnRes = ResourceManager::GetInstance().Load(turnSrc);

    if (turnRes.handleId_ != -1)
    {
        // 画面左上 (X=20, Y=20) に少し小さめ(0.5倍など)で表示する場合
        // ※等倍で良ければ DrawGraph(20, 20, turnRes.handleId_, TRUE); でもOKです
        DrawRotaGraph(180, 60, 0.25, 0.0, turnRes.handleId_, TRUE);
    }
    // 各マスの描画処理
    Cell* hoverCell = GetMouseOverCell();

    for (int y = 0; y < 7; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            Cell* cell = &mCells[y][x];
            int px = cell->GetScreenX();
            int py = cell->GetScreenY();

            // -------------------------------------------------------------
            // 1. 現在クリックして選択中のマスがあれば「赤色」で太く描画
            // -------------------------------------------------------------
            if (mSelectPiece && mSelectPiece->GetX() == x && mSelectPiece->GetY() == y)
            {
                // 線の太さを大きくするため、少しずらして二重・三重枠にする、または外枠を広げて描画
                for (int i = 0; i < 3; i++) // 💡3段階重ねて太枠にする
                {
                    DrawBox(px + i, py + i, px + mCellSizeX - i, py + mCellSizeY - i, GetColor(255, 0, 0), FALSE);
                }
            }
            // -------------------------------------------------------------
            // 2. 移動可能なマスは「青色」のまま（こちらも枠を太く変更）
            // -------------------------------------------------------------
            else if (cell->IsMovePoint())
            {
                for (int i = 0; i < 3; i++) // 💡3段階重ねて太枠にする
                {
                    DrawBox(px + i, py + i, px + mCellSizeX - i, py + mCellSizeY - i, GetColor(0, 0, 255), FALSE);
                }
            }

            // マスの中心にある緑の球体は一時非表示のまま
            // DrawCircle(px + mCellSizeX / 2, py + mCellSizeY / 2, 5, GetColor(0, 255, 0), TRUE);

            if (cell->GetPiece())
            {
                cell->GetPiece()->Draw();
            }
        }
    }

    // -------------------------------------------------------------
    // 3. マウスが乗っている（ホバー）マスを「緑色」で太く描画
    // -------------------------------------------------------------
    if (hoverCell)
    {
        int hx = hoverCell->GetScreenX();
        int hy = hoverCell->GetScreenY();

        for (int i = 0; i < 3; i++) // 💡3段階重ねて太枠にする
        {
            DrawBox(hx + i, hy + i, hx + mCellSizeX - i, hy + mCellSizeY - i, GetColor(0, 255, 0), FALSE);
        }
    }

    // エフェクト（カットインなど）の一番手前描画
    EffectManager::GetInstance().Draw();
}

bool PlayBpard::MovePiece(int fromX, int fromY, int toX, int toY)
{
    Cell* fromCell = &mCells[fromY][fromX]; 
        Cell* toCell = &mCells[toY][toX];
        PieceBase* piece = fromCell->GetPiece(); 

        if (!piece) return false; 
            if (!piece->CanMove(toX, toY)) return false; 

                // 移動経路の途中に駒がある場合は移動できない[cite: 23]
                if (!IsPathClear(fromX, fromY, toX, toY)) return false; 

                    PieceBase* target = toCell->GetPiece(); 

                    if (target)
                    {
                        // 1. 味方の駒なら移動不可[cite: 23]
                        if (target->IsPlayer() == piece->IsPlayer())
                        {
                            return false; 
                        }

                        // 2. 将棋盤の更新を一時ストップ（バトルに行くため）[cite: 23]
                        mGameEnd = true; 

                            // 3. 【追加】どの駒同士が戦うかをSceneManagerに保存！
                            SceneManager::GetInstance().SetBattleInfo(
                                piece->GetType(),       // 動かした駒（攻撃側）
                                target->GetType(),      // そこにいた駒（守備側）
                                piece->IsPlayer()       // プレイヤーが仕掛けたバトルなら true
                            );

                        // 4. 移動先の駒をメモリから消去[cite: 23]
                        delete target;
                            toCell->SetPiece(nullptr); 

                            // 5. FPSバトルシーンへ遷移[cite: 23]
                            SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::FPS_BATTLE);
                    }

    // ※ここは相手の駒が「いなかった」場合の通常の移動処理です
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