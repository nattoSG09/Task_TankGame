#include "Bullet.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

//コンストラクタ
Bullet::Bullet(GameObject* parent)
    :GameObject(parent, "Bullet"), bModel_(-1)
{
}

//デストラクタ
Bullet::~Bullet()
{
}

//初期化
void Bullet::Initialize()
{
    //モデルデータのロード
    bModel_ = Model::Load("Bullet.fbx");
    assert(bModel_ >= 0);

    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.3f);
    AddCollider(collision);
}

//更新
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

//描画
void Bullet::Draw()
{
    Model::SetTransform(bModel_, transform_);
    Model::Draw(bModel_);
}

//開放
void Bullet::Release()
{
}
