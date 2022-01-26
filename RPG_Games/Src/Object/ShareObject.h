#pragma once
#include "../Base/GameObject.h"
#include "../Other/Singleton.h"

class ShareObject : public Singleton<ShareObject>
{
private:
	std::unordered_map<const char*, std::unique_ptr<GameObject>> shareObjects;
	std::vector<const char*> keyList;

public:
	ShareObject() = default;
	~ShareObject()
	{
		shareObjects.clear();
	}

	template <class _Object>
	_Object* AddObject()
	{
		const char* type = typeid(_Object).name();
		if (shareObjects.contains(type))
		{
			THROW("The added object can't add");
			return nullptr;
		}

		_Object* obj = new _Object;
		shareObjects.emplace(type, std::unique_ptr<GameObject>(obj));
		keyList.emplace_back(type);
		return obj;
	}

	template <class _Object>
	_Object* FindObject()
	{
		const char* type = typeid(_Object).name();
		return shareObjects.contains(type) ? static_cast<_Object*>(shareObjects[type].get()) : AddObject<_Object>();
	}

	template<class _Object>
	bool HasObject()
	{
		return shareObjects.contains(typeid(_Object).name());
	}

	template <class _Object>
	bool DeleteObject()
	{
		const char* type = typeid(_Object).name();
		if (!shareObjects.contains(type))
		{
			THROW("The not added object can't delete");
			return false;
		}

		for (int num = 0; num < keyList.size(); ++num)
		{
			if (keyList[num] == type) keyList.erase(keyList.begin() + num);
		}

		return shareObjects.erase(type);
	}

	void Exec()
	{
		for (auto& key : keyList)
		{
			if (shareObjects[key]->isActive) shareObjects[key]->Exec();
		}
	}
};