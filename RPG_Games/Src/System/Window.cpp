#include "Window.h"
#include "Error.h"
#include "../Manager/GameManager.h"

DWORD WINAPI GameLauncher(LPVOID* data)
{
	GameManager::GetInstance()->Exec();
	return true;
}

// ウィンドウ関数
LRESULT CALLBACK WindowProc(
	HWND hWnd,       // ウィンドウハンドル
	UINT uMsg,       // メッセージ（キーが押された等）
	WPARAM wParam,   // メッセージに対応した情報
	LPARAM lParam)   // メッセージに対応した情報
{
	HDC             hdc;    // デバイスコンテキスト（以下DCと省略）
	PAINTSTRUCT     ps;     // 描画構造体
	HBITMAP hBMP;			// ビットマップハンドル

	Canvas* canvas = Canvas::GetInstance();

	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, 0);

	// スレッド管理用
	static HANDLE th;
	DWORD result;

	// メッセージ(された動作)別の処理
	switch (uMsg)
	{
	case WM_CREATE:	// ウインドウが生成されたとき
		hdc = GetDC(hWnd);										// hdcを取得.

		canvas->hdc = CreateCompatibleDC(hdc);					// HDCをコピー.
		hBMP = CreateCompatibleBitmap(hdc, WND_W, WND_H);		// BMPハンドルを作成.
		SelectObject(canvas->hdc, hBMP);						// BMPハンドルを割り当て.
		DeleteObject(hBMP);										// BMPを削除.

		ReleaseDC(hWnd, hdc);									// hdcを解放

		// ダブルバッファの作成
		canvas->MakeBufferDC();

		// ゲームスレッドの作成
		th = CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(GameLauncher), NULL, NULL, NULL);

		return 0;

	case WM_KEYDOWN:	//キーが押されたとき
		return 0;

	case WM_PAINT:	// 表示されるとき(最初の生成とウインドウが表示されるとき)

		// 表示開始.
		hdc = BeginPaint(hWnd, &ps);

		// 表示内容.
		BitBlt(hdc, 0, 0, WND_W, WND_H, canvas->GetBufferDC(), 0, 0, SRCCOPY);

		// 表示終了.
		EndPaint(hWnd, &ps);

		return 0;

	case WM_CLOSE:
		GameManager::GetInstance()->isExit = true;
		while (1) 
		{
				// スレッドが終わったかチェック
				GetExitCodeThread(th, &result);

				// 終わったらハンドルを閉じる
				if (STILL_ACTIVE != result) 
				{
					CloseHandle(th);
					break;
				}
		}
		DestroyWindow(hWnd);
		return 0;

	case WM_DESTROY:	// ウインドウが閉じられるとき
		PostQuitMessage(0);									// アプリケーションの終了
		Gdiplus::GdiplusShutdown(gdiplusToken);				// GDI+の終了処理
		GameManager::GetInstance()->Terminate();			// ゲームの終了
		return DefWindowProc(hWnd, uMsg, wParam, lParam);	// mainに返す情報
	}

	// mainに返す情報
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Window::Window()
{
	WNDCLASS wc;				// ウィンドクラス構造体

	DWORD	ProcessAffinityMask;// CPUを指定
	HANDLE	hProcess;			// プロセスハンドル
	DWORD	errnum;				// 関数復帰値
	RECT	rect;				// 矩形構造体
	DWORD dwStyle;				// ウィンドウスタイル

	// 自身のプロセスハンドルを取得
	hProcess = GetCurrentProcess();

	// 自身を動作させるCPUを指定する
	ProcessAffinityMask = 1;		//CPU 0を使う（２進数で指定）
	if (!SetProcessAffinityMask(hProcess, ProcessAffinityMask)) {
		errnum = GetLastError();	//エラー情報を取得
		return;
	}

	// ウィンドウ情報の設定
	wc.style = CS_HREDRAW | CS_VREDRAW;		// 再描画『REDRAW』
	wc.lpfnWndProc = WindowProc;		    // ウィンドウ関数名
	wc.cbClsExtra = 0;						// 使わない
	wc.cbWndExtra = 0;						// 使わない
	wc.hInstance = NULL;					// インスタンス番号（使用しない）
	wc.hIcon = NULL;					    // アイコン(デフォルト)
	wc.hCursor = NULL;						// カーソル（デフォルト）
	wc.hbrBackground =
		(HBRUSH)COLOR_BACKGROUND + 1;		// 背景色
	wc.lpszMenuName = NULL;					// メニュー名（無し）
	wc.lpszClassName = APP_NAME;		    // アプリケーション名

	// ウィンドウクラスのwindowsに登録
	if (RegisterClass(&wc) == false)
	{
		// 失敗した時のエラーメッセージ
		ERRMSG("ウィンドウクラスの登録失敗", "エラーメッセージ");
		return;
	}

	// 既存のプロット領域に与えられたサイズの矩形を描く
	rect.top = 0;		//上
	rect.left = 0;		//左
	rect.right = WND_W;	//右
	rect.bottom = WND_H;//下

	
	dwStyle = WS_OVERLAPPEDWINDOW;	// ウィンドウ種別

	// AdjustWindowRect((in)画像サイズが入った矩形構造体(out), dwStyle(ウィンドウスタイル), NULL(メニューを持つかどうか))
	if (!AdjustWindowRect(&rect, dwStyle, NULL))
	{
		// 失敗した時のエラーメッセージ
		ERRMSG("ウィンドウ領域の調整に失敗", "エラーメッセージ");
		return;
	}
	

	//ウインドウ作成
	hWnd = CreateWindow(
		APP_NAME,				// アプリケーション名
		TITLE_NAME,				// ウィンドウタイトル
		dwStyle,				// 普通のウィンドウ
		120, 45,				// 表示する位置のxy座標
		rect.right - rect.left,
		rect.bottom - rect.top,	// ウィンドウの幅、高さ
		NULL,                   // 親ウィンドウのハードル
		NULL,                   // メニューの設定（使用しない）
		NULL,					// インスタンス番号（使用しない）
		NULL);                  // 使用しない

	if (hWnd == NULL) {
		ERRMSG("ウィンドウの作成失敗", "エラーメッセージ");
		return;
	}

	// キャンバスの実体取得.
	canvas = Canvas::GetInstance();

	// レイヤーの実体取得.
	layer = Layer::GetInstance();
}

Window::~Window()
{
	DeleteObject(hWnd);
}

void Window::Show()
{
	ShowWindow(hWnd, SW_SHOW);
}

void Window::DrawOut()
{
	// レイヤーの実行.
	layer->Exec();

	// バッファに送信.
	BitBlt(
		canvas->GetBufferDC(),
		0, 0,
		WND_W, WND_H,
		canvas->hdc,
		0, 0,
		SRCCOPY
	);

	// WM_PAINTを呼び出す.
	InvalidateRect(hWnd, NULL, FALSE);
}

HWND Window::getHWND()
{
	return hWnd;
}
