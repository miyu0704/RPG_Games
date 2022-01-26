#pragma once
#include "../Base/GameObject.h"
#include "../Component/SpriteRender.h"
#include "../System/Window.h"



class Title_Back : public GameObject
{
private:
	SpriteRender* SPRender;


public:
	Title_Back()
	{
		SPRender = AddComponent<SpriteRender>();
		SPRender = GetComponent<SpriteRender>();
		SPRender->SetLayer("Back");
		SPRender->SetObject(this);
		SPRender->ImageLoad("Image/Title.png");

	}
	~Title_Back() {}

	void Exec()
	{
	}
};
