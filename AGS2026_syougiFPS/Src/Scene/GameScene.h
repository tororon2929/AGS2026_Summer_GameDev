#pragma once
#include "SceneBase.h"

class Grid;
class PlayBpard; // 前方宣言を追加
class LightManager; // 前方宣言
//class Ou; // 前方宣言を追加

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
    int PlayTime = 0;
    Grid* grid_;
    PlayBpard* playBoard_; // 盤面オブジェクトを追加
    LightManager* lightManager_; // 追加
	//Ou* ou_; // 王オブジェクトを追加

};