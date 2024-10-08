#include "TestScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"



//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
}

//更新
void TestScene::Update()
{
	//「P」が押されていたら
	if (Input::IsKeyDown(DIK_P))
	{
		//TestSceneに切り替える
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}
