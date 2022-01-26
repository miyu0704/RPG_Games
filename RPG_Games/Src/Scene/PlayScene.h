#pragma once
#include "Scene.h"
#include "../Object/FadeObject.h"

class PlayScene : public Scene
{
private:
	FadeObject<PlayScene>* fadeObject;

public:
	PlayScene();
	~PlayScene();

	void Exec();
};