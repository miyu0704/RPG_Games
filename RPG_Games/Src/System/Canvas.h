#pragma once
#include "../Other/Singleton.h"
#include "../Other/Decl.h"

#include <Windows.h>

class Canvas : public Singleton<Canvas>
{
private:
	HDC hGlobalDC;		// ダブルバッファリングDC.
	HDC hMemDC = CreateCompatibleDC(NULL);	// 画像描画用DC.

public:
	Canvas() = default;
	~Canvas()
	{
		DeleteDC(hdc);
		DeleteDC(hMemDC);
		DeleteDC(hGlobalDC);
	}

	HDC hdc;			// 描画先DC.

	void MakeBufferDC();
	
	HDC GetBufferDC()
	{
		return hGlobalDC;
	}
};