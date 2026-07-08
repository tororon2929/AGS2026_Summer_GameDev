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
	//’nã‚Ì‚‚³
    float floorHeight = 25.0f;
	//“G‚Ì“–‚½‚è”»’è‚Ì”¼Œa
    float radius_ = 2.0f;
    float velocityY_ = 0.0f;

};


