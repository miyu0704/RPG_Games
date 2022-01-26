#pragma once
#include "../Base/GameObject.h"
#include "../Component/SpriteRender.h"

class PictureBook : public GameObject
{
private:
	SpriteRender* sprite;

public:
	PictureBook();
	~PictureBook();

	void Exec() override;
};