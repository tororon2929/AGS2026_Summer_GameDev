#pragma once
#include <vector>
#include "../Common/MoveCommand.h"

class PlayBpard; // 前方宣言

class CpuPlayer {
public:
    // 難易度の定義
    enum class Level {
        Easy,
        Normal,
        Hard
    };

    CpuPlayer(Level level);
    ~CpuPlayer();

    // CPUの思考を実行し、決定した手を返す関数
    MoveCommand Think(PlayBpard* board);

private:
    Level m_level; // 現在の難易度

    // 今の盤面でCPUが動かせるすべての手をリストアップする
    std::vector<MoveCommand> GetAllValidMoves(PlayBpard* board);
};