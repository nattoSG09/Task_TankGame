#pragma once
#include "Engine/GameObject.h"
#include <math.h>

class Bullet :public GameObject
{
    int bModel_;
    XMFLOAT3 Move_;

public:
    //コンストラクタ
    Bullet(GameObject* parent);

    //デストラクタ
    ~Bullet();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void SetMove(XMFLOAT3 move) { Move_ = move; }

};

