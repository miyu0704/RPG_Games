#pragma once
#include "GameObject.h"

class Button : public GameObject
{
private:

public:
	Button() = default;
	virtual ~Button() = default;

	// ボタン処理実行
	virtual void OnRun() abstract;
};