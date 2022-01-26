#pragma once

#include "Collider.h"

class TileCollider : public Collider
{
private:

public:
	TileCollider() = default;
	~TileCollider() = default;

	void Exec() override
	{
		isHit = false;

		int xCheck = (owner->position.x + localPosition.x) - (target->position.x + tCollider->localPosition.x);
		int yCheck = (owner->position.y + localPosition.y) - (target->position.y + tCollider->localPosition.y);

		if (-rect.x * owner->scale.x < xCheck && xCheck < target->scale.x * tCollider->rect.x && -rect.y * owner->scale.y < yCheck && yCheck < target->scale.y * tCollider->rect.y) isHit = true;
	}
}; 