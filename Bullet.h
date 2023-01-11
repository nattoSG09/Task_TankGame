#pragma once
#include "Engine/GameObject.h"
#include <math.h>

class Bullet :public GameObject
{
    int bModel_;
    XMFLOAT3 Move_;
    const float INITIAL_VELOCITY = -100.0f;//�����x -100.0m/s
    const float GRAVITY = 9.8f;//�d��

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

