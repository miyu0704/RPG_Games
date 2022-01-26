#pragma once
#include "../Base/GameObject.h"
#include "../Component/TileRender.h"
#include "../Component/TileCollider.h"
#include "../Component/TextRender.h"

class Player : public GameObject
{
private:
	TileRender* tileRender;
	TileCollider* tileCollider;
	TextRender* text;
	InputManager* input;

	int animIndex = 0;
	int animInterval = 0;

	bool isAddIndex = true;

	enum Direction
	{
		DOWN = 0,
		LEFT,
		RIGHT,
		UP,
	} direction;

public:
	Player();
	~Player() = default;

	Vector2 oldPosition{ 0, 0 };

	void Exec();
};
