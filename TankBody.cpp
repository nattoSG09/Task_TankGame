#include "TankBody.h"
#include "Ground.h"
#include "TankHead.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"


enum
{
    CAM_TYPE_FIXED, //固定
    CAM_TPS_NO_ROT,//３人称(回転なし)
    CAM_TYPE_TPS,//３人称
    CAM_TYPE_FPS, //一人称
    CAM_TYPE_MAX,
};

//コンストラクタ
TankBody::TankBody(GameObject* parent)
	: GameObject(parent, "TankBody"), hModel_(-1)
{
}

//初期化
void TankBody::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load("TankBody.fbx");
	assert(hModel_ >= 0);
    Instantiate<TankHead>(this);
}

//更新
void TankBody::Update()
{
    //□＝＝＝＝＝＝ TankBody：移動処理 ＝＝＝＝＝＝＝□
    //「D」キーを押すと右回転
    if (Input::IsKey(DIK_D))
    {
        transform_.rotate_.y += 2.0f;
    }
    //「A」キーを押すと左回転
    if (Input::IsKey(DIK_A))
    {
        transform_.rotate_.y -= 2.0f;
    }

    //戦車の現在地をベクトル型に変換
    XMVECTOR VectorPos = XMLoadFloat3(&transform_.position_);
    //１フレームの移動ベクトル
    XMVECTOR VectorMove = { 0.0f,0.0f,0.10f,0.0f };
    //transform_.rotate_.y度回転させる行列を作成
    XMMATRIX RotateMatY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    //移動ベクトルを変形(戦車と同じ向きに回転)
    VectorMove = XMVector3TransformCoord(VectorMove, RotateMatY);

    //「W」キーを押すと向いている方向に進む
    if (Input::IsKey(DIK_W))
    {
        //向いている方向に進む処理
        //移動
        VectorPos += VectorMove;
        //現在地をベクトルからいつものtransform.position_にもどす
        XMStoreFloat3(&transform_.position_, VectorPos);
    }

    //「S」キーを押すと向いている方向の後ろに進む
    if (Input::IsKey(DIK_S))
    {
        //向いている方向に進む処理
        //移動
        VectorPos -= VectorMove;
        //現在地をベクトルからいつものtransform.position_にもどす
        XMStoreFloat3(&transform_.position_, VectorPos);
    }
    //□＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝□

    //□＝＝＝＝＝＝ TankBody：カメラ処理 ＝＝＝＝＝＝□
    //「F」キーを押すと視点を更新する
    if (Input::IsKeyDown(DIK_F))
    {
        if (CamType_ < CAM_TYPE_FPS)CamType_ += 1;
        else CamType_ = CAM_TYPE_FIXED;
    }

    //焦点の位置
    XMFLOAT3 CamTarget = { 0,0,0 };
    //一人称カメラの位置
    XMFLOAT3 CamPosition = { 0,0,0 };
    //３人称カメラの位置
    XMVECTOR CamVector = { 0,5,-10,0 };
    CamVector = XMVector3TransformCoord(CamVector, RotateMatY);
    XMVECTOR FPSup = { 0,2,0 };

    //視点種類
    switch (CamType_)
    {
    case CAM_TYPE_FIXED://定点カメラ(ステージ全体が映る)
        CamTarget = XMFLOAT3(0, 0, -7);
        CamPosition = XMFLOAT3(0, 45, -30);
        break;
    case CAM_TPS_NO_ROT://3人称視点(回転なし)
        CamTarget = transform_.position_;
        CamPosition = transform_.position_;
        CamPosition.y += 5;//tankより高さが５高い位置
        CamPosition.z -= 10;//tankよりｚが１０遠い位置
        break;
    case CAM_TYPE_TPS://3人称視点(回転あり)
        CamTarget = transform_.position_;
        XMStoreFloat3(&CamPosition, VectorPos + CamVector);
        break;
    case CAM_TYPE_FPS://一人称視点

        XMStoreFloat3(&CamTarget, VectorPos + VectorMove + FPSup);
        XMStoreFloat3(&CamPosition, VectorPos+FPSup);
        break;
    }
    Camera::SetTarget(CamTarget);
    Camera::SetPosition(CamPosition);
    //□＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝□
    
   
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
void TankBody::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void TankBody::Release()
{
}
