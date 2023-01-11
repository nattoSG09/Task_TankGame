#include "PlayScene.h"
#include "Ground.h"
#include "TankBody.h"
#include "Enemy.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"





//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<Ground>(this);
	Instantiate<TankBody>(this);

	for (int i = 0; i < 3; i++)
	{
		Instantiate<Enemy>(this);
	}
	
}

//更新
void PlayScene::Update()
{
	//「P」が押されていたら
	if (Input::IsKeyDown(DIK_P))
	{
		//TestSceneに切り替える
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TEST);
	}
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}
