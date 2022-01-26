#pragma once
#include "../Other/Singleton.h"
#include "../Other/Decl.h"

#include <Windows.h>

class Canvas : public Singleton<Canvas>
{
private:
	HDC hGlobalDC;		// �_�u���o�b�t�@�����ODC.
	HDC hMemDC = CreateCompatibleDC(NULL);	// �摜�`��pDC.

public:
	Canvas() = default;
	~Canvas()
	{
		DeleteDC(hdc);
		DeleteDC(hMemDC);
		DeleteDC(hGlobalDC);
	}

	HDC hdc;			// �`���DC.

	void MakeBufferDC();
	
	HDC GetBufferDC()
	{
		return hGlobalDC;
	}
};