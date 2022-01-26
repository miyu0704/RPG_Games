#pragma once
#include "../Base/GameObject.h"
#include "../Component/TileRender.h"
#include "../Component/TileCollider.h"

class Enemy : public GameObject
{
protected:
	TileRender* tileRender;

    /*�G�X�e�[�^�X
    *
    * name  ���O
    * ID    EnemyID  
    * LV    ���x��
    * HP    �̗�
    * STR   �U����
    * DEF   �h���
    * DEX   �f����
    * GOLD  �v���C���[������z
    */
    struct  ENEMY_STS
    {
        char name[32];
        int ID;
        int LV;
        int EXP;
        int HP;
        int STR;
        int DEF;
        int DEX;
        int GOLD;
    };

public:
	Enemy();
	~Enemy();

};
