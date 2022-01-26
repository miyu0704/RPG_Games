#include "PlayScene.h"
#include "../Object/FadeObject.h"
#include "../Object/Maps.h"
#include "../Object/Player.h"

PlayScene::PlayScene()
{
	// オブジェクトの追加.
	fadeObject = shareObject->FindObject<FadeObject<PlayScene>>();
	shareObject->AddObject<Player>();
	Maps* maps = AddObject<Maps>();

	maps->Load(0);
}

PlayScene::~PlayScene()
{
}

void PlayScene::Exec()
{
	if (fadeObject)
	{
		if (!fadeObject->isActive)
		{
			shareObject->DeleteObject<FadeObject<PlayScene>>();
			fadeObject = nullptr;
		}
	}
	else
	{

	}

	return Scene::Exec();
}
