#include "TitleScene.h"
#include "../Object/Title_Back.h"
#include "../Object/TitleUI_Start.h"
#include "../Object/TitleUI_Continue.h"
#include "../Object/TitleUI_Exit.h"
#include "../Object/Select_icon.h"

#include "../Object/Player.h"

TitleScene::TitleScene()
{
	GameObject* temp;

	// プレイヤーオブジェクトの削除
	if (shareObject->HasObject<Player>()) shareObject->DeleteObject<Player>();

	// タイトルシーンのオブジェクト追加
	AddObject<Title_Back>();
	AddObject<TitleUI_Start>();
	AddObject<TitleUI_Continue>();
	AddObject<TitleUI_Exit>();

	// 選択アイコン
	temp = AddObject<Select_icon<Mode, Mode::START, Mode::EXIT>>();
	temp->position.x = 625;
	temp->position.y = 400;
	temp->scale.x = 1.25;
	temp->scale.y = 1.25;

	inputManager = InputManager::GetInstance();

	dsound->AddBGM("Sound/BGM/Title.mp3", "Title_BGM");
	dsound->setBGM("Title_BGM");
	dsound->SetVolume(1000);
}

TitleScene::~TitleScene()
{
	
}

void TitleScene::Exec()
{
	if (isFading) return Scene::Exec();

	dsound->Loop();
	if (inputManager->GetKeyDown(KEY_SPACE))
	{

		switch (FindObject<Select_icon<Mode, Mode::START, Mode::EXIT>>()->GetSelect())
		{
		case START:
 			FindObject<TitleUI_Start>()->OnRun();
			isFading = true;
			break;
 
		case CONTINUE:
			break;

		case EXIT:
			FindObject<TitleUI_Exit>()->OnRun();
			break;
		}
	}
	return Scene::Exec();
}