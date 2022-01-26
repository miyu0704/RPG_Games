#pragma once
#include "GameObject.h"

class Button : public GameObject
{
private:

public:
	Button() = default;
	virtual ~Button() = default;

	// ƒ{ƒ^ƒ“ˆ—Às
	virtual void OnRun() abstract;
};