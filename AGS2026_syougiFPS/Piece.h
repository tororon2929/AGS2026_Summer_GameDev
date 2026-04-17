#pragma once

enum PieceType
{
    EMPTY,
    PAWN,
    KING
};

class Piece
{
public:
    PieceType type;
    bool isPlayer;

    Piece(PieceType t = EMPTY, bool p = true)
        : type(t), isPlayer(p) {
    }
};