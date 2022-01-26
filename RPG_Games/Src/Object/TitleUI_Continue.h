#pragma once
#include "../Base/Button.h"
#include "../Component/SpriteRender.h"
#include "../Manager/SceneManager.h"

class TitleUI_Continue : public Button
{
private:
	SpriteRender* SPRender;
	SceneManager* sceneManager;

public:
	TitleUI_Continue()
	{
		SPRender = AddComponent<SpriteRender>();

		SPRender->localPosition.x = 700;
		SPRender->localPosition.y = 500;
		SPRender->localScale.x = 1.25;
		SPRender->localScale.y = 1.25;

		SPRender->SetLayer("UI");
		SPRender->SetObject(this);
		SPRender->ImageLoad("Image/UI/Continue.png");

	}

	~TitleUI_Continue() = default;

	void OnRun() override
	{
		// ƒvƒŒƒC‚ð‘±‚«‚©‚ç.
		// sceneManager->SetScene<>();
	}

	void Exec()
	{
	}
};
