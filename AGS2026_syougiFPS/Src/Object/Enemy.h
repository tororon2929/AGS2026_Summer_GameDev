#pragma once

#include "../Common/Transform.h"

class Enemy
{
public:

    Enemy();
    ~Enemy();

    void Init();
    void Update();
    void Draw();
	void Release();

    VECTOR GetPos() const { return transform_.pos; }
private:

    Transform transform_;
    bool isDummy_ = true; // ‰¼ƒ‚ƒfƒ‹‚©‚Ç‚¤‚©
    
};


