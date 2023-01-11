#include "Enemy.h"
#include "Ground.h"
#include "Engine/Model.h"

enum
{
	//曲がるアニメーション
	Bend_Start = 1,
	Bend_End = 60,
	//膨張するアニメーション
	Expansion_Start = 70,
	Expansion_End = 100,
};

//コンストラクタ
Enemy::Enemy(GameObject* parent)
	: GameObject(parent, "Enemy"), hModel_(-1)
{
}

//初期化
void Enemy::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load("Enemy.fbx");
	assert(hModel_ >= 0);

	//アニメーションを動かす
	Model::SetAnimFrame(hModel_, Bend_Start, Bend_End, 1);

	//敵の位置をランダムに生成
	transform_.position_.x = (float)(rand() % 401 - 200) / 10;//rand() %範囲+最小値;
	transform_.position_.z = (float)(rand() % 401 - 200) / 10;

	//あたり判定
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 1, 0), 1.0f);
	AddCollider(collision);
}

//更新
void Enemy::Update()
{
	//□＝＝＝＝＝＝＝ Ground：衝突処理 ＝＝＝＝＝＝＝□
	Ground* pGround = (Ground*)FindObject("Ground"); //ステージオブジェクトを探す
	int GroundModel = pGround->GetModelHandle(); //モデル番号を取得

	RayCastData data;
	data.start = transform_.position_; //レイの発射位置
	data.start.y = 0; //レイの発射位置
	data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
	Model::RayCast(GroundModel, &data); //レイを発射

	if (data.hit == true)
	{
		transform_.position_.y = -data.dist;
	}
	//□＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝□
}

//描画
void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Enemy::Release()
{
}

//何かに当たった
void Enemy::OnCollision(GameObject* pTarget)
{

	//当たったときの処理
	//弾に当たったとき
	if (pTarget->GetObjectName() == "Bullet")
	{
		pTarget->KillMe();
		KillMe();
	}
}
