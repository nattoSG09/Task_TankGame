#pragma once
#include "Engine/GameObject.h"
#include <math.h>

class Bullet :public GameObject
{
    int bModel_;
    XMFLOAT3 Move_;

public:
    //�R���X�g���N�^
    Bullet(GameObject* parent);

    //�f�X�g���N�^
    ~Bullet();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void SetMove(XMFLOAT3 move) { Move_ = move; }

};

