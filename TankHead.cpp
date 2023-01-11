#include "TankHead.h"
#include "Bullet.h"
#include "Engine/Model.h"
#include "Engine/Input.h"


//コンストラクタ
TankHead::TankHead(GameObject* parent)
	: GameObject(parent, "TankHead"), hModel_(-1)
{
}

//初期化
void TankHead::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load("TankHead2.fbx");
	assert(hModel_ >= 0);
}

//更新
void TankHead::Update()
{
    //□＝＝＝＝＝＝ TankHead：移動処理 ＝＝＝＝＝＝□
    //「→」キーを押すと右回転
    if (Input::IsKey(DIK_RIGHT))
    {
        transform_.rotate_.y += 2.0f;
    }
    //「←」キーを押すと左回転
    if (Input::IsKey(DIK_LEFT))
    {
        transform_.rotate_.y -= 2.0f;
    }
    //□＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝□

    //「スペース」キーを押すと発射
    if (Input::IsKeyDown(DIK_SPACE))
    {
        XMFLOAT3 CannonTop = Model::GetBonePosition(hModel_, "Top");
        XMFLOAT3 CannonRoot = Model::GetBonePosition(hModel_, "Root");
        XMVECTOR VectorTop = XMLoadFloat3(&CannonTop);
        XMVECTOR VectorRoot = XMLoadFloat3(&CannonRoot);
        XMVECTOR VectorMove = VectorTop - VectorRoot;
        VectorMove *= 0.5f;
        XMFLOAT3 Move;
        XMStoreFloat3(&Move, VectorMove);


        Bullet* pBullet = Instantiate<Bullet>(GetParent()->GetParent());
        pBullet->SetPosition(CannonTop);
        pBullet->SetMove(Move);
    }
}

//描画
void TankHead::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void TankHead::Release()
{
}
