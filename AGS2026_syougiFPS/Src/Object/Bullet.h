#pragma once
#include <DxLib.h>

class Bullet {
public:
    Bullet(VECTOR pos, VECTOR dir);
    void Update();
    void Draw();
    bool IsDead() const { return life_ <= 0; } // Á‚¦‚é‚×‚«‚©”»’è

    VECTOR GetPos() const { return pos_; }
private:
    VECTOR pos_;
    VECTOR dir_;
    int life_ = 120; // 60ƒtƒŒ[ƒ€‚ÅÁ‚¦‚é

    

};

