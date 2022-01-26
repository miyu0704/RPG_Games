#pragma once
#include "../Base/GameObject.h"
#include "../Component/TileRender.h"
#include "../Component/TileCollider.h"
#include "../Component/jsonLoader.h"

#include "Player.h"

class Maps : public GameObject
{
private:
	TileRender* tileRender;
	jsonLoader* jsonloader;

	TileCollider* collider;
	Player* player;

public:
	Maps();
	~Maps() = default;

	void Load(int mapID);
	void Exec();
};