#pragma once
#include "../Scene/Scene.h"
#include "../Other/Singleton.h"

class SceneManager : public Singleton<SceneManager>
{
private:
	std::unique_ptr<Scene> pScene;

	// シーンの生成クラス.
	template<class _Scene>
	class SceneCreater
	{
	public:
		_Scene* Create() 
		{
			return new _Scene;
		}
	};

public:
	SceneManager();
	~SceneManager();

	template<class _Scene>
	void ChangeScene()
	{
		pScene.reset(SceneCreater<_Scene>().Create());
	}

	Scene* GetScene();

	void Exec();
};