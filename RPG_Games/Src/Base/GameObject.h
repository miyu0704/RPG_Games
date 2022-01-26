#pragma once
#include "../Base/Component.h"
#include "../Other/Vector2.h"
#include "../Manager/InputManager.h"
#include "../System/Error.h"

#include <unordered_map>
#include <memory>

class GameObject
{
protected:
	// コンポーネントの保持.
	std::unordered_map<const char*, std::vector<std::unique_ptr<Component>>> components;
	std::vector<const char*> keyList;

public:
	GameObject() = default;

	virtual ~GameObject()
	{
		components.clear();
		keyList.shrink_to_fit();
	}

	Vector2  position{ 0, 0 };	// 座標.
	Vector2D scale{ 1,1 };		// 大きさ 0以下になってはいけない.
	bool isActive = true;		// アクティブ状態

	template <class _Component>
	_Component* AddComponent()
	{
		const char* type = typeid(_Component).name();
		if (!components.contains(type))
		{
			keyList.emplace_back(type);
		}

		_Component* comp = new _Component;
		components[type].emplace_back(comp);
		return comp;
	}

	template <class _Component>
	_Component* GetComponent()
	{
		const char* type = typeid(_Component).name();
		if (!components.contains(type))
		{
			THROW("The not added component can't get");
			return nullptr;
		}
		
		return static_cast<_Component*>(components[type][0].get());
	}

	template <class _Component>
	std::vector<std::unique_ptr<Component>>* GetComponents()
	{
		const char* type = typeid(_Component).name();
		if (!components.contains(type))
		{
			THROW("The not added component can't get");
			return nullptr;
		}

		return &components[type];
	}

	// 要件：レンダー以外のコンポーネントで、実行処理があるならば呼ぶこと。
	virtual void Exec() abstract;
};