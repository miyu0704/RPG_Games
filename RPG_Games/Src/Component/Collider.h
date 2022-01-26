#pragma once

#include "../Base/GameObject.h"

class Collider : public Component
{
protected:
	GameObject* owner;		// 持ち主
	GameObject* target;		// 当たり判定のターゲット
	Collider* tCollider;	// ターゲットのコライダー	

	bool isHit = false;		// 当たっているかどうか

public:
	Collider() = default;
	virtual ~Collider() = default;

	Vector2  rect{ 0, 0 };			// コライダーの幅, 高さ.

	Vector2  localPosition{ 0, 0 };	// コライダーの座標.

	void SetObject(GameObject* _owner)
	{
		owner = _owner;
	}

	template<class _targetCollider>
	void SetTarget(GameObject* _target)
	{
		target = _target;
		tCollider = target->GetComponent<_targetCollider>();
	}

	bool GetHit() { return isHit; }
};