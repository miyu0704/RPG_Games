#pragma once
#include "../Base/Button.h"
#include "../Component/SpriteRender.h"
#include "../Component/TileRender.h"
#include "../Manager/SceneManager.h"
#include "../Manager/GameManager.h"

class TitleUI_Exit : public Button
{
private:
	SpriteRender* SPRender;
	SceneManager* sceneManager;
	
public:
	TitleUI_Exit()
	{
		SPRender = AddComponent<SpriteRender>();

		SPRender->localPosition.x = 700;
		SPRender->localPosition.y = 600;
		SPRender->localScale.x = 1.25;
		SPRender->localScale.y = 1.25;

		SPRender->SetLayer("UI");
		SPRender->SetObject(this);
		SPRender->ImageLoad("Image/UI/GameExit.png");

	}

	~TitleUI_Exit() = default;

	void OnRun() override
	{
		// ウィンドウを閉じる -> isExitがtrueになる
		PostMessage(Window::GetInstance()->getHWND(), WM_CLOSE, NULL, NULL);
	}

	void Exec()
	{
	}
};