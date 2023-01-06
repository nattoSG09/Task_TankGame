#include "Bullet.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

//�R���X�g���N�^
Bullet::Bullet(GameObject* parent)
    :GameObject(parent, "Bullet"), bModel_(-1)
{
}

//�f�X�g���N�^
Bullet::~Bullet()
{
}

//������
void Bullet::Initialize()
{
    //���f���f�[�^�̃��[�h
    bModel_ = Model::Load("Bullet.fbx");
    assert(bModel_ >= 0);

    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.3f);
    AddCollider(collision);
}

//�X�V
void Bullet::Update()
{
    
    transform_.position_.x += Move_.x;
    transform_.position_.y+= Move_.y;
    transform_.position_.z += Move_.z;

    if (transform_.position_.z > 50.0f)
    {
        KillMe();
    }
}

//�`��
void Bullet::Draw()
{
    Model::SetTransform(bModel_, transform_);
    Model::Draw(bModel_);
}

//�J��
void Bullet::Release()
{
}
