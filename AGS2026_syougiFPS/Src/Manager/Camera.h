#pragma once
#include <DxLib.h>

class Camera
{

public:

	// コンストラクタ
	Camera(void);

	// デストラクタ
	~Camera(void);

	// 初期化
	void Init(void);

	// 更新
	void Update(void);

	// 描画前のカメラ設定
	void SetBeforeDraw(void);

	// デバッグ用描画
	void DrawDebug(void);


	// 解放
	void Release(void);

	// 座標の取得
	const VECTOR& GetPos(void) const;

	// 角度の取得
	const VECTOR& GetAngles(void) const;

private:

	// カメラの位置
	VECTOR pos_;

	// カメラの角度
	VECTOR angles_;

};
