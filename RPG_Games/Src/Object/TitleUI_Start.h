#pragma once
#include "../Base/Button.h"
#include "../Component/SpriteRender.h"
#include "../Manager/SceneManager.h"
#include "../Scene/PlayScene.h"

#include "../Object/FadeObject.h"

class TitleUI_Start : public Button
{
private:
	SpriteRender* SPRender;

public:
	TitleUI_Start()
	{
		SPRender = AddComponent<SpriteRender>();

		SPRender->localPosition.x = 700;
		SPRender->localPosition.y = 400;
		SPRender->localScale.x = 1.25;
		SPRender->localScale.y = 1.25;

		SPRender->SetLayer("UI");
		SPRender->SetObject(this);
		SPRender->ImageLoad("Image/UI/Start.png");
	}

	~TitleUI_Start() = default;

	void OnRun() override
	{
		ShareObject::GetInstance()->AddObject<FadeObject<PlayScene>>();
	}

	void Exec()
	{
	}
};
