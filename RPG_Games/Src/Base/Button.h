#pragma once
#include "GameObject.h"

class Button : public GameObject
{
private:

public:
	Button() = default;
	virtual ~Button() = default;

	// �{�^���������s
	virtual void OnRun() abstract;
};