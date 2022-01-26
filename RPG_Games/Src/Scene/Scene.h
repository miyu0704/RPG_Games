#pragma once
#include "../Object/ShareObject.h"
#include "../System/dSound.h"

class Scene
{
protected:
	// ゲームオブジェクトの保持.
	std::unordered_map<const char*, std::unique_ptr<GameObject>> gameObjects;
	std::vector<const char*> keyList;

	// サウンド関連の呼び出し.
	dSound* dsound = dSound::GetInstance();

	// シーン共有オブジェクトデータ
	ShareObject* shareObject = ShareObject::GetInstance();

public:
	Scene() = default;

	virtual ~Scene()
	{
		gameObjects.clear();
	}

	template <class _Object>
	_Object* AddObject()
	{
		const char* type = typeid(_Object).name();
		if (gameObjects.contains(type))
		{
			THROW("The added object can't add");
			return nullptr;
		}

		_Object* obj = new _Object;
		gameObjects.emplace(type, std::unique_ptr<GameObject>(obj));
		keyList.emplace_back(type);
		return obj;
	}

	template <class _Object>
	_Object* FindObject()
	{
		const char* type = typeid(_Object).name();
		if (!gameObjects.contains(type))
		{
			THROW("The not added object can't find");
			return nullptr;
		}

		return static_cast<_Object*>(gameObjects[type].get());
	}

	template<class _Object>
	bool HasObject()
	{
		return gameObjects.contains(typeid(_Object).name());
	}

	template <class _Object>
	bool DeleteObject()
	{
		const char* type = typeid(_Object).name();
		if (!gameObjects.contains(type))
		{
			THROW("The not added object can't delete");
			return;
		}

		for (int num = 0; num < keyList.size(); ++num)
		{
			if (keyList[num] == type) keyList.erase(keyList.begin() + num);
		}

		return gameObjects.erase(type);
	}

	virtual void Exec()
	{
		// シーン共有オブジェクト処理実行.
		shareObject->Exec();

		// シーン別のオブジェクト処理実行.
		for (auto& key : keyList)
		{
			if (gameObjects[key]->isActive) gameObjects[key]->Exec();
		}
	}
};