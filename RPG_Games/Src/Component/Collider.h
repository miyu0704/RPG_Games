#pragma once

#include "../Base/GameObject.h"

class Collider : public Component
{
protected:
	GameObject* owner;		// ������
	GameObject* target;		// �����蔻��̃^�[�Q�b�g
	Collider* tCollider;	// �^�[�Q�b�g�̃R���C�_�[	

	bool isHit = false;		// �������Ă��邩�ǂ���

public:
	Collider() = default;
	virtual ~Collider() = default;

	Vector2  rect{ 0, 0 };			// �R���C�_�[�̕�, ����.

	Vector2  localPosition{ 0, 0 };	// �R���C�_�[�̍��W.

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