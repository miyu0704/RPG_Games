#pragma once
#include "../Base/GameObject.h"
#include "../Component/TileRender.h"
#include "../Component/TileCollider.h"

class Enemy : public GameObject
{
protected:
	TileRender* tileRender;

    /*敵ステータス
    *
    * name  名前
    * ID    EnemyID  
    * LV    レベル
    * HP    体力
    * STR   攻撃力
    * DEF   防御力
    * DEX   素早さ
    * GOLD  プレイヤー入手金額
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
