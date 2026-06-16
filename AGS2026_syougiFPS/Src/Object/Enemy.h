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

private:

    Transform transform_;
    bool isDummy_ = true; // ‰¼ƒ‚ƒfƒ‹‚©‚Ç‚¤‚©
};


