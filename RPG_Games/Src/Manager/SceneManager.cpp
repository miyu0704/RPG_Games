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
	�V�[���̑J�ڏ���

	Title -> Play
	  Play Button
*/