#pragma once
#include "Scene.h"
#include "../Manager/InputManager.h"

class TitleScene : public Scene
{
private:
	InputManager* inputManager;

	// モードセレクト
	enum Mode
	{
		START = 0,
		CONTINUE,
		EXIT
	};

	bool isFading = false;

public:
	TitleScene();
	~TitleScene();

	int mode = START;

	void Exec();
};