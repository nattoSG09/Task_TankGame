#include "Enemy.h"
#include "Ground.h"
#include "Engine/Model.h"

enum
{
	//ÈªéAj[V
	Bend_Start = 1,
	Bend_End = 60,
	//c£·éAj[V
	Expansion_Start = 70,
	Expansion_End = 100,
};

//RXgN^
Enemy::Enemy(GameObject* parent)
	: GameObject(parent, "Enemy"), hModel_(-1)
{
}

//ú»
void Enemy::Initialize()
{
	//ff[^Ì[h
	hModel_ = Model::Load("Enemy.fbx");
	assert(hModel_ >= 0);

	//Aj[Vð®©·
	Model::SetAnimFrame(hModel_, Bend_Start, Bend_End, 1);

	//GÌÊuð_É¶¬
	transform_.position_.x = (float)(rand() % 401 - 200) / 10;//rand() %ÍÍ+Å¬l;
	transform_.position_.z = (float)(rand() % 401 - 200) / 10;
}

//XV
void Enemy::Update()
{
	//  GroundFÕË  
	Ground* pGround = (Ground*)FindObject("Ground"); //Xe[WIuWFNgðT·
	int GroundModel = pGround->GetModelHandle(); //fÔðæ¾

	RayCastData data;
	data.start = transform_.position_; //CÌ­ËÊu
	data.start.y = 0; //CÌ­ËÊu
	data.dir = XMFLOAT3(0, -1, 0);       //CÌûü
	Model::RayCast(GroundModel, &data); //Cð­Ë

	if (data.hit == true)
	{
		transform_.position_.y = -data.dist;
	}
	//  
}

//`æ
void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//Jú
void Enemy::Release()
{
}
