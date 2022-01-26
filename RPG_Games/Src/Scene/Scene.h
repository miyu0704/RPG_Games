#pragma once
#include "../Object/ShareObject.h"
#include "../System/dSound.h"

class Scene
{
protected:
	// �Q�[���I�u�W�F�N�g�̕ێ�.
	std::unordered_map<const char*, std::unique_ptr<GameObject>> gameObjects;
	std::vector<const char*> keyList;

	// �T�E���h�֘A�̌Ăяo��.
	dSound* dsound = dSound::GetInstance();

	// �V�[�����L�I�u�W�F�N�g�f�[�^
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
		// �V�[�����L�I�u�W�F�N�g�������s.
		shareObject->Exec();

		// �V�[���ʂ̃I�u�W�F�N�g�������s.
		for (auto& key : keyList)
		{
			if (gameObjects[key]->isActive) gameObjects[key]->Exec();
		}
	}
};