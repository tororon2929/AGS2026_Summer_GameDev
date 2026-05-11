#pragma once
#include "SceneBase.h"

class Grid;
class PlayBpard; // 前方宣言を追加

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
    PlayBpard* playBoard_; // 盤面オブジェクトを追加
};