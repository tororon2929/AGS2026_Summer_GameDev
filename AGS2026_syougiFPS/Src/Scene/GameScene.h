#pragma once
#include "SceneBase.h"

class Grid;

class GameScene : public SceneBase
{
public:
    GameScene(void);
    ~GameScene(void) override;
    void Init(void)    override;
    void Update(void)  override;
    void Draw(void)    override;
    void Release(void) override;

private:
    Grid* grid_;
};