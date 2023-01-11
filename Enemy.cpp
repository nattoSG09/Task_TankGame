#include "Enemy.h"
#include "Ground.h"
#include "Engine/Model.h"

enum
{
	//�Ȃ���A�j���[�V����
	Bend_Start = 1,
	Bend_End = 60,
	//�c������A�j���[�V����
	Expansion_Start = 70,
	Expansion_End = 100,
};

//�R���X�g���N�^
Enemy::Enemy(GameObject* parent)
	: GameObject(parent, "Enemy"), hModel_(-1)
{
}

//������
void Enemy::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("Enemy.fbx");
	assert(hModel_ >= 0);

	//�A�j���[�V�����𓮂���
	Model::SetAnimFrame(hModel_, Bend_Start, Bend_End, 1);

	//�G�̈ʒu�������_���ɐ���
	transform_.position_.x = (float)(rand() % 401 - 200) / 10;//rand() %�͈�+�ŏ��l;
	transform_.position_.z = (float)(rand() % 401 - 200) / 10;

	//�����蔻��
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 1, 0), 1.0f);
	AddCollider(collision);
}

//�X�V
void Enemy::Update()
{
	//���������������� Ground�F�Փˏ��� ����������������
	Ground* pGround = (Ground*)FindObject("Ground"); //�X�e�[�W�I�u�W�F�N�g��T��
	int GroundModel = pGround->GetModelHandle(); //���f���ԍ����擾

	RayCastData data;
	data.start = transform_.position_; //���C�̔��ˈʒu
	data.start.y = 0; //���C�̔��ˈʒu
	data.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
	Model::RayCast(GroundModel, &data); //���C�𔭎�

	if (data.hit == true)
	{
		transform_.position_.y = -data.dist;
	}
	//��������������������������������������������������
}

//�`��
void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Enemy::Release()
{
}

//�����ɓ�������
void Enemy::OnCollision(GameObject* pTarget)
{

	//���������Ƃ��̏���
	//�e�ɓ��������Ƃ�
	if (pTarget->GetObjectName() == "Bullet")
	{
		pTarget->KillMe();
		KillMe();
	}
}
