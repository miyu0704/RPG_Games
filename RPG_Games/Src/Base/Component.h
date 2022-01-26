#pragma once

class Component
{
protected:

public:
	Component() = default;
	virtual ~Component() = default;

	bool isActive = true;	// �A�N�e�B�u���

	// �R���|�[�l���g�������s
	virtual void Exec() abstract;
};