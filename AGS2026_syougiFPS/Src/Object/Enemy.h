#pragma once

#include "../Common/Transform.h"

class Enemy
{
public:
    int hp_ = 100;

    Enemy();
    ~Enemy();

    void Init();
    void Update(VECTOR playerPos);
    void Draw();
	void Release();

    VECTOR GetPos() const { return transform_.pos; }
    float GetRadius() const { return radius_; }
    void Damage(int value);
    bool IsDead() const { return hp_ <= 0; }

    
private:

    Transform transform_;
    bool isDummy_ = false; // ‰¼ƒ‚ƒfƒ‹‚©‚Ç‚¤‚©
    float moveTimer_ = 0.0f;
    float moveSpeed = 0.02f;
    float floorHeight = 20.0f;
    float radius_ = 7.0f;
    float velocityY_ = 0.0f;

};


