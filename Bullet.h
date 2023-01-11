#pragma once
#include "Engine/GameObject.h"
#include <math.h>

class Bullet :public GameObject
{
    int bModel_;
    XMFLOAT3 Move_;
    const float INITIAL_VELOCITY = -100.0f;//初速度 -100.0m/s
    const float GRAVITY = 9.8f;//重力

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

