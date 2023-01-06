#include "PlayScene.h"
#include "Ground.h"
#include "TankBody.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"





//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//������
void PlayScene::Initialize()
{
	Instantiate<Ground>(this);
	Instantiate<TankBody>(this);
}

//�X�V
void PlayScene::Update()
{
	//�uP�v��������Ă�����
	if (Input::IsKeyDown(DIK_P))
	{
		//TestScene�ɐ؂�ւ���
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TEST);
	}
}

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}
