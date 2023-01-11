#include "TankBody.h"
#include "Ground.h"
#include "TankHead.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"


enum
{
    CAM_TYPE_FIXED, //�Œ�
    CAM_TPS_NO_ROT,//�R�l��(��]�Ȃ�)
    CAM_TYPE_TPS,//�R�l��
    CAM_TYPE_FPS, //��l��
    CAM_TYPE_MAX,
};

//�R���X�g���N�^
TankBody::TankBody(GameObject* parent)
	: GameObject(parent, "TankBody"), hModel_(-1)
{
}

//������
void TankBody::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("TankBody.fbx");
	assert(hModel_ >= 0);
    Instantiate<TankHead>(this);
}

//�X�V
void TankBody::Update()
{
    //�������������� TankBody�F�ړ����� ����������������
    //�uD�v�L�[�������ƉE��]
    if (Input::IsKey(DIK_D))
    {
        transform_.rotate_.y += 2.0f;
    }
    //�uA�v�L�[�������ƍ���]
    if (Input::IsKey(DIK_A))
    {
        transform_.rotate_.y -= 2.0f;
    }

    //��Ԃ̌��ݒn���x�N�g���^�ɕϊ�
    XMVECTOR VectorPos = XMLoadFloat3(&transform_.position_);
    //�P�t���[���̈ړ��x�N�g��
    XMVECTOR VectorMove = { 0.0f,0.0f,0.10f,0.0f };
    //transform_.rotate_.y�x��]������s����쐬
    XMMATRIX RotateMatY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    //�ړ��x�N�g����ό`(��ԂƓ��������ɉ�])
    VectorMove = XMVector3TransformCoord(VectorMove, RotateMatY);

    //�uW�v�L�[�������ƌ����Ă�������ɐi��
    if (Input::IsKey(DIK_W))
    {
        //�����Ă�������ɐi�ޏ���
        //�ړ�
        VectorPos += VectorMove;
        //���ݒn���x�N�g�����炢����transform.position_�ɂ��ǂ�
        XMStoreFloat3(&transform_.position_, VectorPos);
    }

    //�uS�v�L�[�������ƌ����Ă�������̌��ɐi��
    if (Input::IsKey(DIK_S))
    {
        //�����Ă�������ɐi�ޏ���
        //�ړ�
        VectorPos -= VectorMove;
        //���ݒn���x�N�g�����炢����transform.position_�ɂ��ǂ�
        XMStoreFloat3(&transform_.position_, VectorPos);
    }
    //��������������������������������������������������

    //�������������� TankBody�F�J�������� ��������������
    //�uF�v�L�[�������Ǝ��_���X�V����
    if (Input::IsKeyDown(DIK_F))
    {
        if (CamType_ < CAM_TYPE_FPS)CamType_ += 1;
        else CamType_ = CAM_TYPE_FIXED;
    }

    //�œ_�̈ʒu
    XMFLOAT3 CamTarget = { 0,0,0 };
    //��l�̃J�����̈ʒu
    XMFLOAT3 CamPosition = { 0,0,0 };
    //�R�l�̃J�����̈ʒu
    XMVECTOR CamVector = { 0,5,-10,0 };
    CamVector = XMVector3TransformCoord(CamVector, RotateMatY);
    XMVECTOR FPSup = { 0,2,0 };

    //���_���
    switch (CamType_)
    {
    case CAM_TYPE_FIXED://��_�J����(�X�e�[�W�S�̂��f��)
        CamTarget = XMFLOAT3(0, 0, -7);
        CamPosition = XMFLOAT3(0, 45, -30);
        break;
    case CAM_TPS_NO_ROT://3�l�̎��_(��]�Ȃ�)
        CamTarget = transform_.position_;
        CamPosition = transform_.position_;
        CamPosition.y += 5;//tank��荂�����T�����ʒu
        CamPosition.z -= 10;//tank��肚���P�O�����ʒu
        break;
    case CAM_TYPE_TPS://3�l�̎��_(��]����)
        CamTarget = transform_.position_;
        XMStoreFloat3(&CamPosition, VectorPos + CamVector);
        break;
    case CAM_TYPE_FPS://��l�̎��_

        XMStoreFloat3(&CamTarget, VectorPos + VectorMove + FPSup);
        XMStoreFloat3(&CamPosition, VectorPos+FPSup);
        break;
    }
    Camera::SetTarget(CamTarget);
    Camera::SetPosition(CamPosition);
    //��������������������������������������������������
    
   
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
void TankBody::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void TankBody::Release()
{
}
