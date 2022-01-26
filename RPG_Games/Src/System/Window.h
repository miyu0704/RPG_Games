#pragma once
#include "../Other/Singleton.h"
#include "Layer.h"

class Window : public Singleton<Window>
{
private:
	HWND hWnd;				// �E�B���h�E�n���h��

	Canvas* canvas;			// �`���ʃN���X
	Layer* layer;			// ���C���[�Ǘ��N���X.

public:
	Window();
	~ Window();

	void Show();
	void DrawOut();

	HWND getHWND();
};
