#pragma once
#include "../Base/GameObject.h"
#include "../System/Window.h"

#include <Windows.h>
#include <atlimage.h>

class Render : public Component
{
protected:
	HDC canvasDC;
	const char* InLayer;		// �ǂ̃��C���[�ɑ����邩

	Vector2*  position;			// �Q�[���I�u�W�F�N�g�̍��W�̎Q��.
	Vector2D* scale;			// �傫���̎Q��.

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

	Vector2  localPosition{ 0, 0 };	// �����_�[�̍��W.
	Vector2D localScale{ 1,1 };		// �����_�[�̑傫��.

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

