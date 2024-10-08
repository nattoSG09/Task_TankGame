#pragma once
#include "Engine/GameObject.h"

//テストシーンを管理するクラス
class Ground : public GameObject
{
	int hModel_;    //モデル番号
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Ground(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//任意のゲームオブジェクトに「何メートル先でぶつかるか」を求める関数
	int GetModelHandle() { return hModel_; }

};