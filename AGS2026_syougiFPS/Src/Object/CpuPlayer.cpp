#include "CpuPlayer.h"
#include "../Object/PlayBpard.h"
#include "../Common/Cell.h"
#include "../Object/PieceBase.h" // 駒の基本クラス
#include <DxLib.h>
#include <climits> 

// 駒の価値を判定して点数を返すヘルパー関数
int GetPieceValue(PieceBase* piece) {
    if (!piece) return 0;

    // 駒の種類（PieceType）を取得
    PieceType type = piece->GetType();

    // 種類に応じて価値（点数）を割り振る
    switch (type) {
    case PIECE_OU:        // 王将
    case PIECE_GYOKU:     // 玉将
        return 10000;     // 絶対に取られたくない（取りたい）ので最高値

    case PIECE_HISHA:     // 飛車
        return 1000;      // 最強の攻撃駒なので高得点

    case PIECE_KAKU:      // 角行
        return 900;       // 飛車に次いで強力

    case PIECE_KIN:       // 金将
    case PIECE_GIN:       // 銀将
        return 500;       // 守りや小回りの利く駒

    case PIECE_FU:        // 歩兵
        return 100;       // 基本の駒

    case PIECE_NONE:
    default:
        return 0;
    }
}

CpuPlayer::CpuPlayer(Level level) : m_level(level) {}
CpuPlayer::~CpuPlayer() {}

// 全ての合法手を洗い出す
std::vector<MoveCommand> CpuPlayer::GetAllValidMoves(PlayBpard* board) {
    std::vector<MoveCommand> validMoves;

    for (int y = 0; y < 7; ++y) {
        for (int x = 0; x < 5; ++x) {
            Cell* cell = board->GetCell(x, y);
            if (!cell) continue;

            PieceBase* piece = cell->GetPiece();
            // 駒が存在し、それが「CPUの駒（後手番）」の場合
            if (piece && !piece->IsPlayer()) {

                // その駒が移動できる全座標(7x5)をチェック
                for (int ty = 0; ty < 7; ++ty) {
                    for (int tx = 0; tx < 5; ++tx) {
                        if (x == tx && y == ty) continue;

                        // 駒のルール上届くか、途中に障害物がないか
                        if (piece->CanMove(tx, ty) && board->IsPathClear(x, y, tx, ty)) {
                            Cell* targetCell = board->GetCell(tx, ty);
                            if (targetCell) {
                                PieceBase* targetPiece = targetCell->GetPiece();
                                // 移動先に自分の駒（CPUの駒）がいるならスキップ
                                if (targetPiece && !targetPiece->IsPlayer()) {
                                    continue;
                                }
                            }

                            // 合法手として追加
                            MoveCommand cmd;
                            cmd.fromX = x;
                            cmd.fromY = y;
                            cmd.toX = tx;
                            cmd.toY = ty;
                            validMoves.push_back(cmd);
                        }
                    }
                }
            }
        }
    }
    return validMoves;
}

// 思考ルーチン
MoveCommand CpuPlayer::Think(PlayBpard* board) {
    std::vector<MoveCommand> validMoves = GetAllValidMoves(board);

    // 動かせる手がない（詰み状態）なら空のコマンドを返す
    if (validMoves.empty()) {
        return MoveCommand();
    }

    // 難易度に応じて分岐
    switch (m_level) {
    case Level::Easy: {
        // 【Easy】ランダムに1手選ぶ
        int randomIndex = GetRand(static_cast<int>(validMoves.size()) - 1);
        return validMoves[randomIndex];
    }

    case Level::Normal: {
        // 【Normal】「駒が取れるなら、一番価値の高い駒を取る」ロジック
        MoveCommand bestMove = validMoves[0];
        int maxCapturedValue = -1;
        std::vector<MoveCommand> bestMovesGroup;

        for (const auto& move : validMoves) {
            Cell* targetCell = board->GetCell(move.toX, move.toY);
            if (targetCell) {
                PieceBase* targetPiece = targetCell->GetPiece();
                if (targetPiece && targetPiece->IsPlayer()) {
                    int val = GetPieceValue(targetPiece);

                    if (val > maxCapturedValue) {
                        maxCapturedValue = val;
                        bestMovesGroup.clear();
                        bestMovesGroup.push_back(move);
                    }
                    else if (val == maxCapturedValue) {
                        bestMovesGroup.push_back(move);
                    }
                }
            }
        }

        if (maxCapturedValue != -1 && !bestMovesGroup.empty()) {
            int randomIndex = GetRand(static_cast<int>(bestMovesGroup.size()) - 1);
            return bestMovesGroup[randomIndex];
        }

        int randomIndex = GetRand(static_cast<int>(validMoves.size()) - 1);
        return validMoves[randomIndex];
    }

    case Level::Hard: {
        // 【Hard】ミニマックス法（実質2手読み評価）
        int bestScore = INT_MIN;
        std::vector<MoveCommand> bestMovesGroup;

        // CPUの自分の駒情報を取得しておく（価値計算に利用）
        Cell* myFromCell = nullptr;
        PieceBase* myMovingPiece = nullptr;

        for (const auto& move : validMoves) {
            int currentScore = 0;

            myFromCell = board->GetCell(move.fromX, move.fromY);
            if (!myFromCell) continue;
            myMovingPiece = myFromCell->GetPiece();
            if (!myMovingPiece) continue;

            // 1. 相手の駒を奪える場合のプラス評価
            Cell* targetCell = board->GetCell(move.toX, move.toY);
            if (targetCell) {
                PieceBase* targetPiece = targetCell->GetPiece();
                if (targetPiece && targetPiece->IsPlayer()) {
                    PieceType targetType = targetPiece->GetType();
                    if (targetType == PIECE_OU || targetType == PIECE_GYOKU) {
                        currentScore += 999999; // 王・玉を取れるなら勝利確定なので超最優先
                    }
                    else {
                        currentScore += GetPieceValue(targetPiece) * 100; // 駒得の価値を大幅プラス
                    }
                }
            }

            // 2. 位置（前進）による微小な評価（攻める気持ちを持たせる）
            currentScore += move.toY * 2;

            // 3. 【ミニマックス（2手読み）】移動した後にプレイヤーから反撃を受けるリスクを予測
            int maxRiskScore = 0;

            // 盤面全体を走査して、次のプレイヤーのターンで何が起こるかシミュレーション
            for (int py = 0; py < 7; ++py) {
                for (int px = 0; px < 5; ++px) {
                    Cell* pCell = board->GetCell(px, py);
                    if (!pCell) continue;

                    PieceBase* pPiece = pCell->GetPiece();
                    // プレイヤーの駒を見つけた場合
                    if (pPiece && pPiece->IsPlayer()) {

                        // そのプレイヤーの駒が、CPUが「移動しようとしている未来のマス(move.toX, move.toY)」に攻撃できるか？
                        if (pPiece->CanMove(move.toX, move.toY) && board->IsPathClear(px, py, move.toX, move.toY)) {
                            // もしプレイヤーに取られてしまうなら、移動させる予定の自分の駒の価値がリスク（損失）になる
                            int risk = GetPieceValue(myMovingPiece) * 100;
                            if (risk > maxRiskScore) {
                                maxRiskScore = risk; // 最も痛い損失を記録
                            }
                        }
                    }
                }
            }

            // スコアから予測される最大リスクを引き算する（ミニマックスの核心部分）
            currentScore -= maxRiskScore;

            // 一番スコアの高い手をリストアップ
            if (currentScore > bestScore) {
                bestScore = currentScore;
                bestMovesGroup.clear();
                bestMovesGroup.push_back(move);
            }
            else if (currentScore == bestScore) {
                bestMovesGroup.push_back(move);
            }
        }

        // 最高評価の手の中からランダムに選択（同じ手ばかりになるのを防止）
        if (!bestMovesGroup.empty()) {
            int randomIndex = GetRand(static_cast<int>(bestMovesGroup.size()) - 1);
            return bestMovesGroup[randomIndex];
        }

        return validMoves[0];
    }
    }

    return validMoves[0];
}