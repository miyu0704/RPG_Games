#include "System/Window.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR      lpCmdLine,
	int       nCmdShow
)
{
	MSG msg;				// ウィンドウメッセージ.
	Window::GetInstance();	// ウィンドウのインスタンス生成.

	//メッセージループ（ウィンドウが閉じられるまでループ).
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		// ウィンドウ関数にメッセージを送る.
		DispatchMessage(&msg);
	}
	
	return 0;
}