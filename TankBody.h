#pragma once
#include "Engine/GameObject.h"


//テストシーンを管理するクラス
class TankBody : public GameObject
{
	int hModel_;    //モデル番号
	int CamType_; //カメラ番号
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TankBody(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};