#include "Canvas.h"

void Canvas::MakeBufferDC()
{
	HBITMAP hBmp;
	hBmp = CreateCompatibleBitmap(hdc, WND_W, WND_H);
	hGlobalDC = CreateCompatibleDC(hdc);
	SelectObject(hGlobalDC, hBmp);
	DeleteObject(hBmp);
}
