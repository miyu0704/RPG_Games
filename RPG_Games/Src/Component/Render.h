#pragma once
#include "../Base/GameObject.h"
#include "../System/Window.h"

#include <Windows.h>
#include <atlimage.h>

class Render : public Component
{
protected:
	HDC canvasDC;
	const char* InLayer;		// どのレイヤーに属するか

	Vector2*  position;			// ゲームオブジェクトの座標の参照.
	Vector2D* scale;			// 大きさの参照.

	virtual void Render_Exec() abstract;

	void Exec() override
	{
		Render_Exec();
	}

public:
	Render()
	{
		canvasDC = Canvas::GetInstance()->hdc;
	}

	virtual ~Render()
	{
		Layer::GetInstance()->UnRegisterRender(InLayer, this);
	}

	Vector2  localPosition{ 0, 0 };	// レンダーの座標.
	Vector2D localScale{ 1,1 };		// レンダーの大きさ.

	void SetLayer(const char* layerName)
	{
		InLayer = layerName;
		Layer::GetInstance()->RegisterRender(layerName, this);
	}

	void SetObject(GameObject* gameobject)
	{
		position = &gameobject->position;
		scale = &gameobject->scale;
	}
};

