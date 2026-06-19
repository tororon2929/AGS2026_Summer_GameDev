#pragma once

#include "../Common/Transform.h"

class Enemy
{
public:

    Enemy();
    ~Enemy();

    void Init();
    void Update(VECTOR playerPos);
    void Draw();
	void Release();

    VECTOR GetPos() const { return transform_.pos; }

    
private:

    Transform transform_;
    bool isDummy_ = true; // ‰¼ƒ‚ƒfƒ‹‚©‚Ç‚¤‚©
    float moveTimer_ = 0.0f;
    float moveSpeed = 0.03f;
    float floorHeight = 20.0f;
    
};


