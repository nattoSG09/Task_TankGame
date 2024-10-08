#include "TankHead.h"
#include "Bullet.h"
#include "Engine/Model.h"
#include "Engine/Input.h"


//RXgN^
TankHead::TankHead(GameObject* parent)
	: GameObject(parent, "TankHead"), hModel_(-1)
{
}

//๚ป
void TankHead::Initialize()
{
	//ff[^ฬ[h
	hModel_ = Model::Load("TankHead2.fbx");
	assert(hModel_ >= 0);
}

//XV
void TankHead::Update()
{
    //  TankHeadFฺฎ  
    //uจvL[๐ทฦE๑]
    if (Input::IsKey(DIK_RIGHT))
    {
        transform_.rotate_.y += 2.0f;
    }
    //uฉvL[๐ทฦถ๑]
    if (Input::IsKey(DIK_LEFT))
    {
        transform_.rotate_.y -= 2.0f;
    }
    //  

    //uXy[XvL[๐ทฦญห
    if (Input::IsKeyDown(DIK_SPACE))
    {
        XMFLOAT3 CannonTop = Model::GetBonePosition(hModel_, "Top");
        XMFLOAT3 CannonRoot = Model::GetBonePosition(hModel_, "Root");
        XMVECTOR VectorTop = XMLoadFloat3(&CannonTop);
        XMVECTOR VectorRoot = XMLoadFloat3(&CannonRoot);
        XMVECTOR VectorMove = VectorTop - VectorRoot;
        VectorMove *= 0.4f;
        XMFLOAT3 Move;
        XMStoreFloat3(&Move, VectorMove);


        Bullet* pBullet = Instantiate<Bullet>(GetParent()->GetParent());
        pBullet->SetPosition(CannonTop);
        pBullet->SetMove(Move);
    }
}

//`ๆ
void TankHead::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//J๚
void TankHead::Release()
{
}
