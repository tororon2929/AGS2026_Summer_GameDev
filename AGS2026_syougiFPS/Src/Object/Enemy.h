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

private:

    Transform transform_;
};


