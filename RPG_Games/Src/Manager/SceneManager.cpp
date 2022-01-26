#include "SceneManager.h"
#include "../Scene/TitleScene.h"
#include "../Scene/PlayScene.h"

SceneManager::SceneManager()
{
	pScene.reset(SceneCreater<TitleScene>().Create());
}

SceneManager::~SceneManager()
{
	ShareObject::DestroyInstance();
}

Scene* SceneManager::GetScene()
{
	return pScene.get();
}

void SceneManager::Exec()
{
	pScene->Exec();
}

/*
	ƒV[ƒ“‚Ì‘JˆÚðŒ

	Title -> Play
	  Play Button
*/