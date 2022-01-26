#pragma once
#include "../Base/GameObject.h"
#include "../Component/SpriteRender.h"
#include "../Manager/SceneManager.h"

template<typename _Enum, _Enum first, _Enum end, int distance = 100>
class Select_icon : public GameObject
{
private:
	SpriteRender* SPRender;
	SceneManager* sceneManager;
	InputManager* input;

	int sel = first;

public:
	Select_icon()
	{
		SPRender = AddComponent<SpriteRender>();

		SPRender->SetLayer("UI");
		SPRender->SetObject(this);
		SPRender->ImageLoad("Image/UI/Select_icon.png");

		input = InputManager::GetInstance();
	}
	~Select_icon() = default;

	_Enum GetSelect() { return static_cast<_Enum>(sel); }

	void Exec()
	{
		if (input->GetKeyDown(KEY_DOWN) && sel != end)
		{
			++sel;
			position.y += distance;
		}
		else if (input->GetKeyDown(KEY_UP) && sel != first)
		{
			--sel;
			position.y -= distance;
		}
	}
};