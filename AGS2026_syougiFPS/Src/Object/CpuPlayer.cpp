#include "CpuPlayer.h"
#include "../Object/PlayBpard.h"
#include "../Common/Cell.h"
#include "../Object/PieceBase.h" // 駒の基本クラス（環境に合わせてパスを変更してください）
#include <DxLib.h>

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
    case Level::Normal:
        // TODO: 今後「駒が取れるなら取る」ようなロジックを書く
        return validMoves[0];

    case Level::Hard:
        // TODO: 今後「評価関数やミニマックス法」などの強いロジックを書く
        return validMoves[0];
    }

    return validMoves[0];
}