#pragma once
#include "Engine/GameObject.h"


//�e�X�g�V�[�����Ǘ�����N���X
class TankBody : public GameObject
{
	int hModel_;    //���f���ԍ�
	int CamType_; //�J�����ԍ�
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TankBody(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};