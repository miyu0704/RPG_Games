#pragma once
#include "../Other/Singleton.h"
#include "Layer.h"

class Window : public Singleton<Window>
{
private:
	HWND hWnd;				// ウィンドウハンドル

	Canvas* canvas;			// 描画画面クラス
	Layer* layer;			// レイヤー管理クラス.

public:
	Window();
	~ Window();

	void Show();
	void DrawOut();

	HWND getHWND();
};
