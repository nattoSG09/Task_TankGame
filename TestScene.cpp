#include "TestScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"



//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
}

//�X�V
void TestScene::Update()
{
	//�uP�v��������Ă�����
	if (Input::IsKeyDown(DIK_P))
	{
		//TestScene�ɐ؂�ւ���
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}
